#include "config.h"
#include "test.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#ifdef __USE_FIXED_PROTOTYPES__
extern int socketpair(int,int,int,int[2]);
#endif

int signalled = 0;

void handler (int arg)
{
  fprintf(stderr,"Got signal\n");
  signalled = 1;
}

int main (void)
{
#if defined(SIGIO) && defined(FASYNC) && defined(F_SETFL) && defined(F_SETOWN)
  int p[2];
  int ret;
  struct sigaction a;
  a.sa_handler = handler;
  sigfillset(&a.sa_mask);
  a.sa_flags = 0;
  sigaction(SIGIO,&a,NULL);
  if (socketpair(AF_UNIX,SOCK_STREAM,0,p) == -1) return 1;
  if ((ret = fcntl(p[0],F_GETFL,0)) == -1) return 1;
  if (fcntl(p[0],F_SETFL,ret | FASYNC) == -1) return 1;
  if (fcntl(p[0],F_SETOWN,getpid()) == -1) return 1;
  switch (fork()) {
  case -1:
    return 1;
  case 0:
    fprintf(stderr,"Child running\n");
    fprintf(stderr,"Writing character\n");
    write(p[1],"x",1);
    fprintf(stderr,"Sleeping\n");
    sleep(1);
    fprintf(stderr,"Exiting\n");
    exit(0);
  default:
    fprintf(stderr,"Waiting\n");
    while(wait(NULL) == -1 && errno == EINTR) 
      fprintf(stderr,"Waiting again\n");
  }
  if (!signalled) return 1;
  return 0;
/* Make sure we can receive SIGIO for stdin and stdout */
  if (fcntl(0,F_SETOWN,getpid()) == -1) return 1;
  if (fcntl(1,F_SETOWN,getpid()) == -1) return 1;
  if ((ret = open("file",O_CREAT | O_TRUNC,0644)) == -1) return 1;
  if (fcntl(ret,F_SETOWN,getpid()) == -1) return 1;
  return 0;
#else
  return 1;
#endif
}
