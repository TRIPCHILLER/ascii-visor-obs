#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(__APPLE__)
#import <Cocoa/Cocoa.h>
#include <util/platform.h>
#define Sleep os_sleep_ms
#else
#include <obs-nix-platform.h>
#include <X11/Xlib.h>
#include <util/platform.h>
#define Sleep os_sleep_ms
#endif
#include <obs-module.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const uint32_t width=640,height=360;
static gs_texture_t *pattern;
static const char *input_name(void *unused){(void)unused;return "Composite test source";}
static void *input_create(obs_data_t *settings,obs_source_t *source){(void)settings;return source;}
static void input_destroy(void *unused){(void)unused;}
static uint32_t input_width(void *unused){(void)unused;return width;}
static uint32_t input_height(void *unused){(void)unused;return height;}
static void input_render(void *unused,gs_effect_t *effect){
 (void)unused;(void)effect;gs_effect_t *base=obs_get_base_effect(OBS_EFFECT_DEFAULT);
 gs_effect_set_texture(gs_effect_get_param_by_name(base,"image"),pattern);
 while(gs_effect_loop(base,"Draw"))gs_draw_sprite(pattern,0,width,height);
}
static struct obs_source_info input={.id="composite_test_input",.type=OBS_SOURCE_TYPE_INPUT,
 .output_flags=OBS_SOURCE_VIDEO|OBS_SOURCE_CUSTOM_DRAW,.get_name=input_name,.create=input_create,.destroy=input_destroy,
 .get_width=input_width,.get_height=input_height,.video_render=input_render};
static void set_pattern(bool gradient){
 uint8_t *pixels=malloc(width*height*4);
 for(uint32_t y=0;y<height;y++)for(uint32_t x=0;x<width;x++){
  uint8_t *p=pixels+(y*width+x)*4;
  p[0]=p[1]=p[2]=gradient?(uint8_t)(x*255/(width-1)):0;p[3]=255;
 }
 if(pattern)gs_texture_destroy(pattern);const uint8_t *data=pixels;
 pattern=gs_texture_create(width,height,GS_RGBA,1,&data,0);free(pixels);
}
static int capture(obs_source_t *source,const char *file,bool transparent,bool blank,int background){
 gs_texrender_t *target=gs_texrender_create(GS_RGBA,GS_ZS_NONE);
 gs_stagesurf_t *stage=gs_stagesurface_create(width,height,GS_RGBA);
 struct vec4 color;vec4_set(&color,background?0.12f:0.85f,background?0.55f:0.15f,background?0.9f:0.08f,1.f);
 gs_texrender_begin(target,width,height);gs_clear(GS_CLEAR_COLOR,&color,0,0);
 gs_ortho(0,(float)width,0,(float)height,-100,100);
 /* Match the blend state used by a normal OBS scene. The former test instead
    forced ONE/ZERO over a clear texture and only counted alpha values. */
 gs_blend_state_push();gs_blend_function(GS_BLEND_ONE,GS_BLEND_INVSRCALPHA);
 obs_source_video_render(source);gs_blend_state_pop();gs_texrender_end(target);
 gs_stage_texture(stage,gs_texrender_get_texture(target));
 uint8_t *pixels;uint32_t stride;int failures=0;
 if(gs_stagesurface_map(stage,&pixels,&stride)){
  unsigned long long preserved=0,black=0,visible=0,opaque=0;
  int expected[3]={(int)lround(color.x*255),(int)lround(color.y*255),(int)lround(color.z*255)};
  FILE *f=fopen(file,"wb");fprintf(f,"P6\n%u %u\n255\n",width,height);
  for(uint32_t y=0;y<height;y++)for(uint32_t x=0;x<width;x++){
   uint8_t *p=pixels+y*stride+x*4;fwrite(p,1,3,f);
   bool same=abs(p[0]-expected[0])<=1&&abs(p[1]-expected[1])<=1&&abs(p[2]-expected[2])<=1;
   if(same)preserved++;else visible++;
   if(!p[0]&&!p[1]&&!p[2])black++;if(p[3]==255)opaque++;
  }
  fclose(f);gs_stagesurface_unmap(stage);
  bool ok=transparent?(blank?preserved==width*height:preserved>width*height/4&&visible>100):black==width*height;
  ok=ok&&opaque==width*height;
  printf("COMPOSITE %s preserved=%llu black=%llu opaque=%llu %s\n",file,preserved,black,opaque,ok?"PASS":"FAIL");
  failures+=!ok;
 }else failures++;
 gs_stagesurface_destroy(stage);gs_texrender_destroy(target);return failures;
}
int main(int argc,char **argv){
 if(argc<4){fprintf(stderr,"Usage: scene-transparency <plugin-root> <output-prefix> <OBS-root>\n");return 2;}
#ifdef _WIN32
 char obsbin[2048],obsdata[2048],graphics[2048];wchar_t obsbin_w[2048];
 snprintf(obsbin,sizeof(obsbin),"%s/bin/64bit",argv[3]);
 snprintf(obsdata,sizeof(obsdata),"%s/data/libobs/",argv[3]);
 snprintf(graphics,sizeof(graphics),"%s/bin/64bit/libobs-d3d11.dll",argv[3]);
 MultiByteToWideChar(CP_UTF8,0,obsbin,-1,obsbin_w,2048);
 SetErrorMode(SEM_NOGPFAULTERRORBOX);SetDllDirectoryW(obsbin_w);
#elif defined(__APPLE__)
 [NSApplication sharedApplication];
 char obsdata[2048],graphics[2048];
 snprintf(obsdata,sizeof(obsdata),"%s",getenv("VISOR_TEST_OBSDATA"));
 snprintf(graphics,sizeof(graphics),"%s",getenv("VISOR_TEST_GRAPHICS"));
#else
 const char *obsdata="/usr/share/obs/libobs/",*graphics="libobs-opengl";
 obs_set_nix_platform(OBS_NIX_PLATFORM_X11_EGL);
 Display *display=XOpenDisplay(NULL);if(!display)return 8;
 obs_set_nix_platform_display(display);
#endif
 if(!obs_startup("en-US",NULL,NULL))return 3;
 obs_add_data_path(obsdata);
 struct obs_video_info vi={0};vi.graphics_module=graphics;
 vi.fps_num=30;vi.fps_den=1;vi.base_width=vi.output_width=width;vi.base_height=vi.output_height=height;
 vi.output_format=VIDEO_FORMAT_RGBA;vi.colorspace=VIDEO_CS_709;vi.range=VIDEO_RANGE_FULL;vi.scale_type=OBS_SCALE_BILINEAR;
 if(obs_reset_video(&vi)!=OBS_VIDEO_SUCCESS)return 4;
 char dll[2048],data[2048];
#ifdef _WIN32
 snprintf(dll,sizeof(dll),"%s/build/ascii-visor.dll",argv[1]);
#elif defined(__APPLE__)
 snprintf(dll,sizeof(dll),"%s/build_macos/RelWithDebInfo/ascii-visor.plugin/Contents/MacOS/ascii-visor",argv[1]);
#else
 snprintf(dll,sizeof(dll),"%s/build_x86_64/ascii-visor.so",argv[1]);
#endif
snprintf(data,sizeof(data),"%s/data",argv[1]);
 obs_module_t *module=NULL;if(obs_open_module(&module,dll,data)||!obs_init_module(module))return 5;
 obs_register_source(&input);obs_source_t *source=obs_source_create_private("composite_test_input","Input",NULL);
 obs_data_t *settings=obs_data_create();obs_data_set_int(settings,"columns",80);
 obs_data_set_double(settings,"contrast",1.);obs_data_set_double(settings,"gamma",1.);
 obs_data_set_double(settings,"black",0.);obs_data_set_double(settings,"white",1.);
 obs_data_set_int(settings,"palette",-1);obs_data_set_int(settings,"fg",0xffc78a);obs_data_set_int(settings,"bg",0);
 obs_source_t *filter=obs_source_create_private("ascii_visor_filter","VISOR",settings);if(!source||!filter)return 6;
 obs_source_filter_add(source,filter);int failures=0;char path[2048];
 obs_properties_t *props=obs_source_properties(filter);obs_property_t *charsets=obs_properties_get(props,"charset");
 failures+=obs_property_list_item_count(charsets)!=9;
 for(size_t i=0;i<obs_property_list_item_count(charsets);i++){
  int id=(int)obs_property_list_item_int(charsets,i);failures+=id==5||id==6||id>10;
 }
 failures+=strcmp(obs_property_list_item_name(charsets,6),"Custom input")!=0;
 failures+=strcmp(obs_property_description(obs_properties_get(props,"custom")),"Enter your own character set (up to 128 unique characters)")!=0;
 obs_properties_destroy(props);

 obs_enter_graphics();set_pattern(false);obs_leave_graphics();
 obs_data_set_bool(settings,"transparent",false);obs_source_update(filter,settings);Sleep(100);
 obs_enter_graphics();snprintf(path,sizeof(path),"%s-opaque.ppm",argv[2]);failures+=capture(source,path,false,true,0);obs_leave_graphics();
 obs_data_set_bool(settings,"transparent",true);obs_source_update(filter,settings);Sleep(100);
 obs_enter_graphics();snprintf(path,sizeof(path),"%s-blank.ppm",argv[2]);failures+=capture(source,path,true,true,0);set_pattern(true);obs_leave_graphics();
 int sets[]={0,1,2,3,4,7,8,9,10,5,6};
 for(int i=0;i<11;i++){
  obs_data_set_int(settings,"charset",sets[i]);obs_source_update(filter,settings);Sleep(100);
  if(sets[i]==5||sets[i]==6){obs_data_t *saved=obs_source_get_settings(filter);failures+=obs_data_get_int(saved,"charset")!=(sets[i]==5?9:10);obs_data_release(saved);}
  obs_enter_graphics();snprintf(path,sizeof(path),"%s-set-%d.ppm",argv[2],sets[i]);failures+=capture(source,path,true,false,0);obs_leave_graphics();
 }
 obs_data_set_int(settings,"fps",1);obs_data_set_int(settings,"charset",0);obs_source_update(filter,settings);Sleep(100);
 obs_enter_graphics();snprintf(path,sizeof(path),"%s-cache-first.ppm",argv[2]);failures+=capture(source,path,true,false,0);
 snprintf(path,sizeof(path),"%s-cache-held.ppm",argv[2]);failures+=capture(source,path,true,false,1);obs_leave_graphics();
 obs_source_filter_remove(source,filter);obs_source_release(filter);obs_source_release(source);obs_data_release(settings);
 obs_enter_graphics();gs_texture_destroy(pattern);obs_leave_graphics();obs_shutdown();
 printf("RESULT failures=%d\n",failures);return failures?7:0;
}
