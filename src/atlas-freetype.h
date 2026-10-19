/* Portable atlas backend. Included only on Unix; Windows retains its GDI path.
 * Fonts are opened privately, never installed into the operating system. */
#include <ft2build.h>
#include FT_FREETYPE_H
#include "utf8-codepoints.h"

struct portable_glyph {
 uint32_t codepoint;
 unsigned char pixels[32*64];
 double density;
 int order;
};
static int compare_portable_glyph(const void *a,const void *b) {
 const struct portable_glyph *x=a,*y=b;
 return x->density<y->density?-1:x->density>y->density?1:x->order-y->order;
}
static gs_texture_t *make_atlas(const char *utf8,int *count,float *aspect,bool cjk) {
 FT_Library library=NULL;FT_Face faces[2]={NULL,NULL};
 struct portable_glyph *glyphs=NULL;uint8_t *rgba=NULL;gs_texture_t *atlas=NULL;
 const char *names[]={"fonts/BetterVCR.ttf","fonts/NotoSansMonoCJKjp-Regular.otf"};
 if(FT_Init_FreeType(&library))return NULL;
 for(int i=0;i<2;i++){
  char *path=obs_module_file(names[i]);
  FT_Error error=path?FT_New_Face(library,path,0,&faces[i]):1;
  bfree(path);
  if(error || FT_Set_Pixel_Sizes(faces[i],0,32))goto cleanup;
 }
 uint32_t codes[128];int n=visor_codepoints(utf8,codes,128);
 if(n<0)goto cleanup;
 if(!n){codes[0]=' ';n=1;}
 FT_Face primary=faces[cjk?1:0];
 if(FT_Load_Char(primary,cjk?0x30ab:'M',FT_LOAD_DEFAULT))goto cleanup;
 int cw=(int)((primary->glyph->advance.x+32)/64);
 int baseline=(int)((primary->size->metrics.ascender+32)/64);
 if(cw<1 || cw>64)goto cleanup;
 if(baseline>32)baseline=32;
 glyphs=bzalloc((size_t)n*sizeof(*glyphs));
 for(int i=0;i<n;i++){
  glyphs[i].codepoint=codes[i];glyphs[i].order=i;
  FT_Face face=primary;
  if(!FT_Get_Char_Index(face,codes[i]))face=faces[cjk?0:1];
  if(!FT_Get_Char_Index(face,codes[i]) && codes[i]!=' ')
   blog(LOG_WARNING,"[ASCII VISOR] Missing font glyph U+%04X",(unsigned)codes[i]);
  if(FT_Load_Char(face,codes[i],FT_LOAD_RENDER|FT_LOAD_TARGET_NORMAL))goto cleanup;
  FT_Bitmap *bm=&face->glyph->bitmap;
  for(unsigned y=0;y<bm->rows;y++)for(unsigned x=0;x<bm->width;x++){
   int dx=face->glyph->bitmap_left+(int)x,dy=baseline-face->glyph->bitmap_top+(int)y;
   if(dx<0 || dx>=cw || dy<0 || dy>=32)continue;
   const unsigned char *row=bm->buffer+(bm->pitch>=0?(int)y:(int)(bm->rows-1-y))*abs(bm->pitch);
   unsigned char value=bm->pixel_mode==FT_PIXEL_MODE_MONO?((row[x/8]&(0x80>>(x%8)))?255:0):row[x];
   glyphs[i].pixels[dy*64+dx]=value;
  }
  /* Keep the same 32 x 32 density measurement and stable tie order as GDI. */
  for(int y=0;y<32;y++)for(int x=0;x<32;x++)glyphs[i].density+=glyphs[i].pixels[y*64+x];
 }
 qsort(glyphs,(size_t)n,sizeof(*glyphs),compare_portable_glyph);
 int k=n<10?n:10,width=k*cw;
 rgba=bzalloc((size_t)width*32*4);
 for(int i=0;i<k;i++){
  int idx=n<=10?i:(int)floor(i*(n-1)/9.+.5);
  for(int y=0;y<32;y++)for(int x=0;x<cw;x++){
   size_t pos=((size_t)y*width+i*cw+x)*4;
   rgba[pos]=rgba[pos+1]=rgba[pos+2]=glyphs[idx].pixels[y*64+x];rgba[pos+3]=255;
  }
 }
 const uint8_t *pixels=rgba;atlas=gs_texture_create(width,32,GS_RGBA,1,&pixels,0);
 if(atlas){*count=k;*aspect=(float)cw/32;}
cleanup:
 bfree(rgba);bfree(glyphs);
 for(int i=0;i<2;i++)if(faces[i])FT_Done_Face(faces[i]);
 FT_Done_FreeType(library);return atlas;
}
