#pragma once
#include <stdint.h>
#include <stddef.h>
/* Strict UTF-8, scalar values only. Deduplicate without losing source order. */
static int visor_codepoints(const char *text,uint32_t *out,int capacity) {
 const unsigned char *p=(const unsigned char *)text;int count=0;
 while(*p){
  uint32_t cp=*p++;int following=0;uint32_t minimum=0;
  if(cp>=0xc2 && cp<=0xdf){cp&=0x1f;following=1;minimum=0x80;}
  else if(cp>=0xe0 && cp<=0xef){cp&=0x0f;following=2;minimum=0x800;}
  else if(cp>=0xf0 && cp<=0xf4){cp&=7;following=3;minimum=0x10000;}
  else if(cp>=0x80)return -1;
  for(int i=0;i<following;i++){if((*p&0xc0)!=0x80)return -1;cp=(cp<<6)|(*p++&0x3f);}
  if(cp<minimum || cp>0x10ffff || (cp>=0xd800 && cp<=0xdfff))return -1;
  if(cp<32)continue;
  int duplicate=0;for(int i=0;i<count;i++)if(out[i]==cp)duplicate=1;
  if(!duplicate && count<capacity)out[count++]=cp;
 }
 return count;
}
