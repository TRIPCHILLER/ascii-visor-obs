#include <windows.h>
#include <stdio.h>
int WINAPI WinMain(HINSTANCE a,HINSTANCE b,LPSTR c,int d){
 (void)a;(void)b;(void)c;(void)d;
 HANDLE token=NULL;TOKEN_ELEVATION elevation={0};DWORD size=0;
 if(!OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&token))return 1;
 BOOL ok=GetTokenInformation(token,TokenElevation,&elevation,sizeof(elevation),&size);CloseHandle(token);if(!ok)return 2;
 wchar_t path[MAX_PATH];GetModuleFileNameW(NULL,path,MAX_PATH);wchar_t *slash=wcsrchr(path,L'\\');if(!slash)return 3;
 wcscpy(slash+1,L"launch-permissions.json");FILE *file=_wfopen(path,L"w");if(!file)return 4;
 fprintf(file,"{\"elevated\":%s,\"pid\":%lu}",elevation.TokenIsElevated?"true":"false",GetCurrentProcessId());fclose(file);return 0;
}
