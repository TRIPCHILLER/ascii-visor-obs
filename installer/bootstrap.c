#ifndef UNICODE
#define UNICODE
#endif
#define _UNICODE
#include <windows.h>
#include <stdio.h>

static BOOL extract_resource(int id,const wchar_t *path) {
 HRSRC resource=FindResourceW(NULL,MAKEINTRESOURCEW(id),RT_RCDATA);
 if(!resource)return FALSE;
 HGLOBAL memory=LoadResource(NULL,resource);
 DWORD length=SizeofResource(NULL,resource),written=0;
 HANDLE file=CreateFileW(path,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
 if(file==INVALID_HANDLE_VALUE)return FALSE;
 BOOL result=WriteFile(file,LockResource(memory),length,&written,NULL);
 CloseHandle(file);return result && written==length;
}
int WINAPI wWinMain(HINSTANCE instance,HINSTANCE previous,LPWSTR command,int show) {
 (void)instance;(void)previous;(void)command;(void)show;
 wchar_t temp[MAX_PATH],folder[MAX_PATH],script[MAX_PATH],engine[MAX_PATH],bundle[MAX_PATH],system[MAX_PATH],exe[MAX_PATH],line[2048];
 if(!GetTempPathW(MAX_PATH,temp)||!GetTempFileNameW(temp,L"AVS",0,folder))return 1;
 DeleteFileW(folder);
 if(!CreateDirectoryW(folder,NULL))return 1;
 swprintf(script,MAX_PATH,L"%ls\\setup.ps1",folder);
 swprintf(engine,MAX_PATH,L"%ls\\install-engine.ps1",folder);
 swprintf(bundle,MAX_PATH,L"%ls\\payload.zip",folder);
 if(!extract_resource(101,script)||!extract_resource(102,engine)||!extract_resource(103,bundle)) {
  MessageBoxW(NULL,L"Cannot extract the installer files.",L"ASCII VISOR",MB_ICONERROR);return 2;
 }
 GetSystemDirectoryW(system,MAX_PATH);
 swprintf(exe,MAX_PATH,L"%ls\\WindowsPowerShell\\v1.0\\powershell.exe",system);
 swprintf(line,2048,L"\"%ls\" -NoProfile -STA -ExecutionPolicy Bypass -WindowStyle Hidden -File \"%ls\" -Bundle \"%ls\"",exe,script,bundle);
 STARTUPINFOW startup={0};startup.cb=sizeof(startup);startup.dwFlags=STARTF_USESHOWWINDOW;startup.wShowWindow=SW_HIDE;
 PROCESS_INFORMATION process={0};
 if(!CreateProcessW(exe,line,NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,folder,&startup,&process)) {
  MessageBoxW(NULL,L"Cannot start the installer interface.",L"ASCII VISOR",MB_ICONERROR);return 3;
 }
 WaitForSingleObject(process.hProcess,INFINITE);
 DWORD code=1;GetExitCodeProcess(process.hProcess,&code);
 CloseHandle(process.hThread);CloseHandle(process.hProcess);
 /* Retain the uniquely named temporary directory for diagnostics; no recursive deletion. */
 return (int)code;
}
