#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <obs-module.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "palettes.h"
#include "support-config.h"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("ascii-visor", "en-US")
OBS_MODULE_AUTHOR("TRIPCHILLER")

/* Only live graphics rendering is ported. See research/REPORT.md. */
static const char *sets[] = {
 "@%#*+=-:. ", "01²346⁷𝟴⁸9+. ,",
 "Ａ 𝗠  E ᶠ ᵖ ⁱ t  x  ᶻ . , y W . ",
 "а Б в Г д Е ж З и Й к Л м Н о П р С т У ф Х ц Ч ш Щ ъ Ы ь Э ю Я .  : ",
 "　カタサシスセソラリルレロワヲンツッーー・。、。「」ァィゥェォッャュョヴヶ＝…", ". · ▪ ■ ", "····•○◦ ", "█▓▒░"
};
static const char *labels[] = {"CL4SS1C", "NUMB3RS", "L4T1N", "КИРИJIJIИЦ4", "カタカナ", "P1X3L", "D0TS", "BL0CKS"};
struct glyph { WCHAR text[3]; double density; int order; };
struct visor {
 obs_source_t *source;
 gs_effect_t *effect;
 gs_texrender_t *grid;
 gs_texrender_t *output;
 gs_texture_t *atlas;
 int columns, count, charset_id, fps;
 uint64_t next_frame;
 uint32_t output_w,output_h;
 float zoom, center_x,center_y;
 float aspect, contrast, gamma, black, white;
 bool invert, mirror, transparent;
 struct vec4 fg, bg;
 char charset[2048];
};
static WCHAR font_paths[2][MAX_PATH];

static void color(struct vec4 *v, uint32_t c) {
 v->x=(c&255)/255.f; v->y=((c>>8)&255)/255.f;
 v->z=((c>>16)&255)/255.f; v->w=1.f;
}
static int compare_glyph(const void *a, const void *b) {
 const struct glyph *x=a,*y=b;
 return x->density<y->density ? -1 : x->density>y->density ? 1 : x->order-y->order;
}
/* Same density sort and ten evenly spaced picks as rebuildRenderCharset10.
   GDI rasterization replaces Canvas; the original fonts are private to this process. */
static gs_texture_t *make_atlas(const char *utf8, int *count, float *aspect,bool cjk) {
 WCHAR text[1024];
 if(!MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,utf8,-1,text,1024)) return NULL;
 struct glyph glyphs[128]; int n=0;
 for(int i=0;text[i] && n<128;i++) {
  WCHAR a=text[i],b=0;
  if(a>=0xd800 && a<=0xdbff && text[i+1]>=0xdc00 && text[i+1]<=0xdfff) b=text[++i];
  if(a<32) continue;
  bool duplicate=false;
  for(int j=0;j<n;j++) if(glyphs[j].text[0]==a && glyphs[j].text[1]==b) duplicate=true;
  if(!duplicate) {glyphs[n]=(struct glyph){{a,b,0},0,n};n++;}
 }
 if(!n) {glyphs[n++]=(struct glyph){{L' ',0,0},0,0};}
 HDC dc=CreateCompatibleDC(NULL);
 HFONT font=CreateFontW(-32,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
  OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH,
  cjk?L"Noto Sans Mono CJK JP":L"Better VCR");
 if(!dc || !font) {if(dc) DeleteDC(dc);if(font) DeleteObject(font);return NULL;}
 HGDIOBJ oldfont=SelectObject(dc,font);
 TEXTMETRICW tm; GetTextMetricsW(dc,&tm);
 SIZE size; GetTextExtentPoint32W(dc,cjk?L"カ":L"M",1,&size);
 /* Original measurePre uses CSS line-height:1, so one row is one em. */
 int cw=size.cx, ch=32;
 if(cw<1 || cw>64 || ch<1 || ch>96) {SelectObject(dc,oldfont);DeleteObject(font);DeleteDC(dc);return NULL;}
 int bw=640,bh=96;
 BITMAPINFO bi={0};bi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
 bi.bmiHeader.biWidth=bw;bi.bmiHeader.biHeight=-bh;
 bi.bmiHeader.biPlanes=1;bi.bmiHeader.biBitCount=32;bi.bmiHeader.biCompression=BI_RGB;
 uint8_t *bits=NULL; HBITMAP bitmap=CreateDIBSection(dc,&bi,DIB_RGB_COLORS,(void**)&bits,NULL,0);
 if(!bitmap) {SelectObject(dc,oldfont);DeleteObject(font);DeleteDC(dc);return NULL;}
 HGDIOBJ oldbitmap=SelectObject(dc,bitmap);SetTextColor(dc,RGB(255,255,255));SetBkMode(dc,TRANSPARENT);
 for(int i=0;i<n;i++) {
  memset(bits,0,bw*bh*4);TextOutW(dc,0,0,glyphs[i].text,lstrlenW(glyphs[i].text));GdiFlush();
  double d=0;for(int y=0;y<32;y++)for(int x=0;x<32;x++) d+=bits[(y*bw+x)*4];
  glyphs[i].density=d/(32.*32.);
 }
 qsort(glyphs,n,sizeof(*glyphs),compare_glyph);
 int k=n<10?n:10;
 memset(bits,0,bw*bh*4);
 for(int i=0;i<k;i++) {int idx=n<=10?i:(int)floor(i*(n-1)/9.+.5);
  RECT clip={i*cw,0,(i+1)*cw,ch};
  ExtTextOutW(dc,i*cw,0,ETO_CLIPPED,&clip,glyphs[idx].text,lstrlenW(glyphs[idx].text),NULL);}
 GdiFlush();
 uint8_t *rgba=bmalloc(k*cw*ch*4);
 for(int y=0;y<ch;y++)for(int x=0;x<k*cw;x++) {
  uint8_t d=bits[(y*bw+x)*4];int j=(y*k*cw+x)*4;
  rgba[j]=rgba[j+1]=rgba[j+2]=d;rgba[j+3]=255;
 }
 const uint8_t *data=rgba;gs_texture_t *atlas=gs_texture_create(k*cw,ch,GS_RGBA,1,&data,0);
 bfree(rgba);SelectObject(dc,oldbitmap);DeleteObject(bitmap);
 SelectObject(dc,oldfont);DeleteObject(font);DeleteDC(dc);
 *count=k;*aspect=(float)cw/ch;return atlas;
}
/* Exact 8x8 tiles from upstream PIXEL2_SIZES and DOTS2_MASKS. */
static gs_texture_t *make_shape_atlas(bool dots) {
 uint8_t pixels[32*8*4]={0};
 for(int level=0;level<4;level++)for(int y=0;y<8;y++)for(int x=0;x<8;x++){
  int size=level*2,off=(8-size)/2;
  bool on=level && x>=off && x<off+size && y>=off && y<off+size;
  if(dots && level>=2 && ((x==off||x==off+size-1)&&(y==off||y==off+size-1)))on=false;
  int idx=(y*32+level*8+x)*4;pixels[idx]=pixels[idx+1]=pixels[idx+2]=on?255:0;pixels[idx+3]=255;
 }
 const uint8_t *p=pixels;return gs_texture_create(32,8,GS_RGBA,1,&p,0);
}
static const char *get_name(void *unused) {(void)unused;return "ASCII ⛶ VISOR";}
static void defaults(obs_data_t *s) {
 obs_data_set_default_int(s,"charset",0);obs_data_set_default_string(s,"custom","@%#*+=-:. ");
 obs_data_set_default_int(s,"columns",100);
 obs_data_set_default_double(s,"contrast",2.);obs_data_set_default_double(s,"gamma",.9);
 obs_data_set_default_double(s,"black",.06);obs_data_set_default_double(s,"white",.98);
 obs_data_set_default_int(s,"fg",0xffc78a);obs_data_set_default_int(s,"bg",0);
 obs_data_set_default_int(s,"palette",-1);obs_data_set_default_string(s,"preset_name",obs_module_text("DefaultPresetName"));
 obs_data_set_default_int(s,"fps",0);obs_data_set_default_double(s,"zoom",1.);
 obs_data_set_default_double(s,"center_x",.5);obs_data_set_default_double(s,"center_y",.5);
 obs_data_set_default_string(s,"_visor_info",obs_module_text("AuthorInfo"));
}
static void update(void *data,obs_data_t *s) {
 obs_data_set_string(s,"_visor_info",obs_module_text("AuthorInfo"));
 struct visor *v=data;int set=(int)obs_data_get_int(s,"charset");
 const char *str=set>=0 && set<8?sets[set]:obs_data_get_string(s,"custom");
 obs_enter_graphics();
 if(strcmp(v->charset,str) || !v->atlas || v->charset_id!=set) {
  int count=0;float aspect=1;gs_texture_t *a;
  if(set==9 || set==10){a=make_shape_atlas(set==10);count=4;aspect=1;}
  else a=make_atlas(str,&count,&aspect,set==4);
  if(a) {gs_texture_destroy(v->atlas);v->atlas=a;v->count=count;v->aspect=aspect;
   snprintf(v->charset,sizeof(v->charset),"%s",str);v->charset_id=set;}
  else blog(LOG_ERROR,"[ASCII VISOR] Cannot build glyph atlas");
 }
 v->columns=(int)obs_data_get_int(s,"columns");if(v->columns<30)v->columns=30;if(v->columns>150)v->columns=150;
 obs_data_set_int(s,"columns",v->columns);
 v->contrast=(float)obs_data_get_double(s,"contrast");v->gamma=fmaxf(.1f,(float)obs_data_get_double(s,"gamma"));
 v->black=(float)obs_data_get_double(s,"black");v->white=fmaxf(v->black+.001f,(float)obs_data_get_double(s,"white"));
 v->invert=obs_data_get_bool(s,"invert");v->mirror=obs_data_get_bool(s,"mirror");
 v->transparent=obs_data_get_bool(s,"transparent");color(&v->fg,(uint32_t)obs_data_get_int(s,"fg"));
 color(&v->bg,(uint32_t)obs_data_get_int(s,"bg"));
 v->fps=(int)obs_data_get_int(s,"fps");if(v->fps<0)v->fps=0;if(v->fps>60)v->fps=60;
 v->zoom=fmaxf(.1f,(float)obs_data_get_double(s,"zoom"));
 v->center_x=(float)obs_data_get_double(s,"center_x");v->center_y=(float)obs_data_get_double(s,"center_y");
 v->next_frame=0;obs_leave_graphics();
}
static void destroy(void *data) {
 struct visor *v=data;obs_enter_graphics();gs_texture_destroy(v->atlas);
 gs_effect_destroy(v->effect);gs_texrender_destroy(v->grid);gs_texrender_destroy(v->output);obs_leave_graphics();bfree(v);
}
static void *create(obs_data_t *s,obs_source_t *source) {
 struct visor *v=bzalloc(sizeof(*v));v->source=source;
 char *path=obs_module_file("visor.effect");char *err=NULL;
 obs_enter_graphics();v->effect=gs_effect_create_from_file(path,&err);v->grid=gs_texrender_create(GS_RGBA,GS_ZS_NONE);
 v->output=gs_texrender_create(GS_RGBA,GS_ZS_NONE);obs_leave_graphics();
 bfree(path);if(err){blog(LOG_ERROR,"[ASCII VISOR] Shader: %s",err);bfree(err);}
 if(!v->effect || !v->grid || !v->output) {destroy(v);return NULL;}
 update(v,s);if(!v->atlas){destroy(v);return NULL;}return v;
}
static void fill_palettes(obs_properties_t *p,obs_data_t *s){
 obs_property_t *list=obs_properties_get(p,"palette");obs_property_list_clear(list);
 obs_property_list_add_int(list,obs_module_text("CustomColors"),-1);
 for(int i=0;i<20;i++)obs_property_list_add_int(list,presets[i].name,i);
 obs_data_array_t *a=obs_data_get_array(s,"user_presets");
 for(size_t i=0;i<obs_data_array_count(a);i++){
  obs_data_t *item=obs_data_array_item(a,i);obs_property_list_add_int(list,obs_data_get_string(item,"name"),200+i);obs_data_release(item);
 }
 obs_property_set_enabled(obs_properties_get(p,"save_preset"),obs_data_array_count(a)<20);
 int selected=(int)obs_data_get_int(s,"palette")-200;
 obs_property_set_enabled(obs_properties_get(p,"delete_preset"),selected>=0 && (size_t)selected<obs_data_array_count(a));
 obs_data_array_release(a);
}
static bool palette_changed(obs_properties_t *p,obs_property_t *prop,obs_data_t *s){
 (void)prop;int i=(int)obs_data_get_int(s,"palette");
 if(i>=0 && i<20){obs_data_set_int(s,"fg",presets[i].fg);obs_data_set_int(s,"bg",presets[i].bg);}
 else if(i>=200){obs_data_array_t *a=obs_data_get_array(s,"user_presets");obs_data_t *item=obs_data_array_item(a,i-200);
  if(item){obs_data_set_int(s,"fg",obs_data_get_int(item,"fg"));obs_data_set_int(s,"bg",obs_data_get_int(item,"bg"));}
  obs_data_release(item);obs_data_array_release(a);}
 obs_property_set_enabled(obs_properties_get(p,"delete_preset"),i>=200);return true;
}
static bool color_changed(obs_properties_t *p,obs_property_t *prop,obs_data_t *s){
 (void)prop;int id=(int)obs_data_get_int(s,"palette");uint32_t fg=(uint32_t)obs_data_get_int(s,"fg"),bg=(uint32_t)obs_data_get_int(s,"bg");
 bool same=id>=0 && id<20 && fg==presets[id].fg && bg==presets[id].bg;
 if(id>=200){obs_data_array_t *a=obs_data_get_array(s,"user_presets");obs_data_t *item=obs_data_array_item(a,id-200);
  same=item && fg==(uint32_t)obs_data_get_int(item,"fg") && bg==(uint32_t)obs_data_get_int(item,"bg");obs_data_release(item);obs_data_array_release(a);}
 if(id!=-1 && !same){obs_data_set_int(s,"palette",-1);obs_property_set_enabled(obs_properties_get(p,"delete_preset"),false);return true;}
 return false;
}
static bool charset_changed(obs_properties_t *p,obs_property_t *prop,obs_data_t *s){
 (void)prop;int i=(int)obs_data_get_int(s,"charset");
 obs_property_set_visible(obs_properties_get(p,"custom"),i==8);
 if(i==4 && obs_data_get_int(s,"_last_profile_charset")!=4){obs_data_set_double(s,"black",.10);obs_data_set_double(s,"white",.92);}
 obs_data_set_int(s,"_last_profile_charset",i);return true;
}
static bool save_preset(obs_properties_t *p,obs_property_t *prop,void *data){
 (void)prop;struct visor *v=data;if(!v)return false;obs_data_t *s=obs_source_get_settings(v->source);
 obs_data_array_t *a=obs_data_get_array(s,"user_presets");if(!a)a=obs_data_array_create();
 size_t n=obs_data_array_count(a);
 if(n<20){obs_data_t *item=obs_data_create();const char *name=obs_data_get_string(s,"preset_name");
  obs_data_set_string(item,"name",*name?name:obs_module_text("DefaultPresetName"));obs_data_set_int(item,"fg",obs_data_get_int(s,"fg"));obs_data_set_int(item,"bg",obs_data_get_int(s,"bg"));
  obs_data_array_push_back(a,item);obs_data_release(item);obs_data_set_array(s,"user_presets",a);obs_data_set_int(s,"palette",200+n);
  obs_source_update(v->source,s);fill_palettes(p,s);}
 obs_data_array_release(a);obs_data_release(s);return true;
}
static bool delete_preset(obs_properties_t *p,obs_property_t *prop,void *data){
 (void)prop;struct visor *v=data;if(!v)return false;obs_data_t *s=obs_source_get_settings(v->source);
 int idx=(int)obs_data_get_int(s,"palette")-200;obs_data_array_t *a=obs_data_get_array(s,"user_presets");
 if(idx>=0 && (size_t)idx<obs_data_array_count(a)){obs_data_array_erase(a,idx);obs_data_set_array(s,"user_presets",a);
  obs_data_set_int(s,"palette",-1);obs_source_update(v->source,s);fill_palettes(p,s);}
 obs_data_array_release(a);obs_data_release(s);return true;
}
static bool support_author(obs_properties_t *p,obs_property_t *prop,void *data){
 (void)p;(void)prop;(void)data;
 if(strncmp(VISOR_SUPPORT_URL,"https://",8)!=0)return false;
 WCHAR url[2048];if(!MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,VISOR_SUPPORT_URL,-1,url,2048))return false;
 HINSTANCE result=ShellExecuteW(NULL,L"open",url,NULL,NULL,SW_SHOWNORMAL);
 if((INT_PTR)result>32)blog(LOG_INFO,"[ASCII VISOR] Support page opened: %s",VISOR_SUPPORT_URL);
 else blog(LOG_WARNING,"[ASCII VISOR] Could not open support page (%lld)",(long long)(INT_PTR)result);
 return false;
}
static obs_properties_t *properties(void *data) {
 struct visor *v=data;obs_properties_t *root=obs_properties_create(),*p=obs_properties_create();
 obs_properties_add_group(root,"image_group",obs_module_text("ImageGroup"),OBS_GROUP_NORMAL,p);
 obs_property_t *list=obs_properties_add_list(p,"charset",obs_module_text("Charset"),OBS_COMBO_TYPE_LIST,OBS_COMBO_FORMAT_INT);
 for(int i=0;i<8;i++)obs_property_list_add_int(list,labels[i],i);
 obs_property_list_add_int(list,obs_module_text("CustomCharset"),8);
 obs_property_list_add_int(list,"SQU4R3S / P1X3L2",9);obs_property_list_add_int(list,"D0TS / D0TS2",10);
 obs_property_set_modified_callback(list,charset_changed);
 obs_properties_add_text(p,"custom",obs_module_text("CustomCharacters"),OBS_TEXT_DEFAULT);
 obs_properties_add_int_slider(p,"columns",obs_module_text("Columns"),30,150,1);
 obs_properties_add_float_slider(p,"contrast",obs_module_text("Contrast"),.1,4.,.01);
 obs_properties_add_float_slider(p,"gamma",obs_module_text("Gamma"),.1,3.,.01);
 obs_properties_add_float_slider(p,"black",obs_module_text("BlackPoint"),0.,.99,.01);
 obs_properties_add_float_slider(p,"white",obs_module_text("WhitePoint"),.01,1.,.01);
 obs_properties_add_bool(p,"invert",obs_module_text("Invert"));obs_properties_add_bool(p,"mirror",obs_module_text("Mirror"));
 p=obs_properties_create();obs_properties_add_group(root,"style_group",obs_module_text("StyleGroup"),OBS_GROUP_NORMAL,p);
 list=obs_properties_add_list(p,"palette",obs_module_text("Palette"),OBS_COMBO_TYPE_LIST,OBS_COMBO_FORMAT_INT);
 obs_property_set_modified_callback(list,palette_changed);
 obs_property_set_modified_callback(obs_properties_add_color(p,"fg",obs_module_text("Foreground")),color_changed);
 obs_property_set_modified_callback(obs_properties_add_color(p,"bg",obs_module_text("Background")),color_changed);
 obs_properties_add_text(p,"preset_name",obs_module_text("PresetName"),OBS_TEXT_DEFAULT);
 obs_properties_add_button2(p,"save_preset",obs_module_text("SavePreset"),save_preset,v);
 obs_properties_add_button2(p,"delete_preset",obs_module_text("DeletePreset"),delete_preset,v);
 obs_properties_add_bool(p,"transparent",obs_module_text("Transparent"));
 p=obs_properties_create();obs_properties_add_group(root,"motion_group",obs_module_text("MotionGroup"),OBS_GROUP_NORMAL,p);
 obs_properties_add_int_slider(p,"fps",obs_module_text("FPS"),0,60,1);
 obs_properties_add_float_slider(p,"zoom",obs_module_text("Zoom"),.1,8.,.01);
 obs_properties_add_float_slider(p,"center_x",obs_module_text("CenterX"),0.,1.,.001);
 obs_properties_add_float_slider(p,"center_y",obs_module_text("CenterY"),0.,1.,.001);
 p=obs_properties_create();obs_properties_add_group(root,"about_group",obs_module_text("AboutGroup"),OBS_GROUP_NORMAL,p);
 obs_properties_add_text(p,"_visor_info","",OBS_TEXT_INFO);
 obs_property_t *support=obs_properties_add_button2(p,"support_author",obs_module_text("SupportAuthor"),support_author,NULL);
 obs_property_set_long_description(support,obs_module_text("SupportHint"));
 obs_property_set_visible(support,strncmp(VISOR_SUPPORT_URL,"https://",8)==0);
 obs_data_t *s=v?obs_source_get_settings(v->source):obs_data_create();fill_palettes(root,s);
 obs_property_set_visible(obs_properties_get(root,"custom"),obs_data_get_int(s,"charset")==8);obs_data_release(s);return root;
}
static void set_float(gs_effect_t *e,const char *name,float x) {gs_effect_set_float(gs_effect_get_param_by_name(e,name),x);}
static void present(struct visor *v,uint32_t w,uint32_t h){
 gs_texture_t *texture=gs_texrender_get_texture(v->output);if(!texture)return;
 gs_effect_t *e=obs_get_base_effect(OBS_EFFECT_DEFAULT);gs_effect_set_texture(gs_effect_get_param_by_name(e,"image"),texture);
 while(gs_effect_loop(e,"Draw"))gs_draw_sprite(texture,0,w,h);
}
static void render(void *data,gs_effect_t *unused) {
 (void)unused;struct visor *v=data;obs_source_t *target=obs_filter_get_target(v->source);
 uint32_t w=target?obs_source_get_base_width(target):0,h=target?obs_source_get_base_height(target):0;
 if(!w || !h || !v->atlas) {obs_source_skip_video_filter(v->source);return;}
 uint64_t now=obs_get_video_frame_time();
 if(v->fps && v->next_frame && now<v->next_frame && w==v->output_w && h==v->output_h){present(v,w,h);return;}
 int rows=(int)floor(v->columns*((float)h/w)*v->aspect+.5f);if(rows<1)rows=1;if(rows>1000)rows=1000;
 struct vec2 grid;vec2_set(&grid,(float)v->columns,(float)rows);
 gs_effect_set_vec2(gs_effect_get_param_by_name(v->effect,"grid_size"),&grid);
 set_float(v->effect,"mirror",v->mirror?1.f:0.f);
 if(!obs_source_process_filter_begin(v->source,GS_RGBA,OBS_NO_DIRECT_RENDERING))return;
 gs_texrender_reset(v->grid);
 if(!gs_texrender_begin(v->grid,v->columns,rows)) {obs_source_skip_video_filter(v->source);return;}
 struct vec4 clear={0};gs_clear(GS_CLEAR_COLOR,&clear,0,0);gs_ortho(0,(float)v->columns,0,(float)rows,-100,100);
 gs_blend_state_push();gs_blend_function(GS_BLEND_ONE,GS_BLEND_ZERO);
 obs_source_process_filter_tech_end(v->source,v->effect,v->columns,rows,"Downsample");
 gs_texrender_end(v->grid);
 gs_texrender_reset(v->output);
 if(!gs_texrender_begin(v->output,w,h)){gs_blend_state_pop();return;}
 gs_ortho(0,(float)w,0,(float)h,-100,100);
 gs_effect_set_vec2(gs_effect_get_param_by_name(v->effect,"grid_size"),&grid);
 gs_effect_set_texture(gs_effect_get_param_by_name(v->effect,"image"),gs_texrender_get_texture(v->grid));
 gs_effect_set_texture(gs_effect_get_param_by_name(v->effect,"atlas"),v->atlas);
 set_float(v->effect,"glyph_count",(float)v->count);set_float(v->effect,"contrast",v->contrast);
 set_float(v->effect,"gamma",v->gamma);set_float(v->effect,"black_point",v->black);set_float(v->effect,"white_point",v->white);
 set_float(v->effect,"invert",v->invert?1.f:0.f);set_float(v->effect,"transparent",v->transparent?1.f:0.f);
 set_float(v->effect,"zoom",v->zoom);struct vec2 center;vec2_set(&center,v->center_x,v->center_y);
 gs_effect_set_vec2(gs_effect_get_param_by_name(v->effect,"center"),&center);
 gs_effect_set_vec4(gs_effect_get_param_by_name(v->effect,"foreground"),&v->fg);
 gs_effect_set_vec4(gs_effect_get_param_by_name(v->effect,"background"),&v->bg);
 while(gs_effect_loop(v->effect,"Draw"))gs_draw_sprite(NULL,0,w,h);
 gs_texrender_end(v->output);v->output_w=w;v->output_h=h;
 v->next_frame=v->fps?now+1000000000ULL/v->fps:0;
 present(v,w,h);
 gs_blend_state_pop();
}
static struct obs_source_info info={.id="ascii_visor_filter",.type=OBS_SOURCE_TYPE_FILTER,.output_flags=OBS_SOURCE_VIDEO,
 .get_name=get_name,.create=create,.destroy=destroy,.update=update,.get_defaults=defaults,.get_properties=properties,.video_render=render};
bool obs_module_load(void) {
 const char *names[]={"fonts/BetterVCR.ttf","fonts/NotoSansMonoCJKjp-Regular.otf"};
 for(int i=0;i<2;i++){char *p=obs_module_file(names[i]);if(p){MultiByteToWideChar(CP_UTF8,0,p,-1,font_paths[i],MAX_PATH);
  if(!AddFontResourceExW(font_paths[i],FR_PRIVATE,NULL))blog(LOG_WARNING,"[ASCII VISOR] Cannot load private font %s",p);bfree(p);}}
 obs_register_source(&info);blog(LOG_INFO,"[ASCII VISOR] Native live GPU filter 0.2.6 registered");return true;
}
void obs_module_unload(void) {for(int i=0;i<2;i++)if(font_paths[i][0])RemoveFontResourceExW(font_paths[i],FR_PRIVATE,NULL);}
const char *obs_module_name(void){return "ASCII VISOR — OBS EDITION";}
const char *obs_module_description(void){return obs_module_text("Description");}
