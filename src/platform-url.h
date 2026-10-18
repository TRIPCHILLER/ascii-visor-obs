#pragma once
#ifdef _WIN32
static void visor_open_url(const char *url) {
 WCHAR wide[2048];
 if(!MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,url,-1,wide,2048))return;
 if((INT_PTR)ShellExecuteW(NULL,L"open",wide,NULL,NULL,SW_SHOWNORMAL)<=32)
  blog(LOG_WARNING,"[ASCII VISOR] Could not open browser");
}
#else
#include <spawn.h>
#include <pthread.h>
#include <sys/wait.h>
#include <errno.h>
extern char **environ;
static void *visor_wait_browser(void *value) {
 pid_t child=*(pid_t *)value;free(value);
 while(waitpid(child,NULL,0)<0 && errno==EINTR){}
 return NULL;
}
static void visor_open_url(const char *url) {
#ifdef __APPLE__
 const char *command="/usr/bin/open";
#else
 const char *command="xdg-open";
#endif
 /* No shell expansion; URL is one argument. Reap the launcher off the UI thread. */
 pid_t *child=malloc(sizeof(*child));if(!child)return;
 char *args[]={(char *)command,(char *)url,NULL};
 if(posix_spawnp(child,command,NULL,NULL,args,environ)){free(child);return;}
 pthread_t waiter;
 if(!pthread_create(&waiter,NULL,visor_wait_browser,child))pthread_detach(waiter);
 else visor_wait_browser(child);
}
#endif
