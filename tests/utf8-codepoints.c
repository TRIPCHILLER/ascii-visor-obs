#include "../src/utf8-codepoints.h"
#include <stdio.h>
#include <string.h>
#define CHECK(x) do {if(!(x)){fprintf(stderr,"FAIL line %d\n",__LINE__);return 1;}}while(0)
int main(void){
 uint32_t out[128];
 CHECK(visor_codepoints("AA B\nB",out,128)==3);
 CHECK(out[0]=='A'&&out[1]==' '&&out[2]=='B');
 CHECK(visor_codepoints("\xd0\x96\xe3\x82\xab\xf0\x9d\x9f\xb4",out,128)==3);
 CHECK(out[0]==0x416&&out[1]==0x30ab&&out[2]==0x1d7f4);
 CHECK(visor_codepoints("\xc0\x80",out,128)==-1);
 CHECK(visor_codepoints("\xed\xa0\x80",out,128)==-1);
 CHECK(visor_codepoints("\xf4\x90\x80\x80",out,128)==-1);
 CHECK(visor_codepoints("\xe2\x82",out,128)==-1);
 CHECK(visor_codepoints("abcdef",out,3)==3);
 CHECK(visor_codepoints("",out,128)==0);
 puts("UTF-8 scalar parsing: PASS");return 0;
}
