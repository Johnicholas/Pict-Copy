#include "config.h"
#include "test.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/un.h>

#ifdef __USE_FIXED_PROTOTYPES__
extern int listen(int,int);
extern int socket(int,int,int);
extern int bind(int,struct sockaddr *,int);
extern int accept(int,struct sockaddr *,int*);
extern int setitimer (int,struct itimerval*,struct itimerval*);
#endif

int s;

void fail (char *msg)
{
  fprintf(stderr,"%s\n",msg);
  close(s); unlink("socket.tst"); exit(1);
}

void handler (int arg)
{
  fail("SIGALRM");
}

int main (void)
{
  if ((s = socket(PF_UNIX,SOCK_STREAM,0)) == -1) {
    fprintf(stderr,"socket failed\n"); return 1;
  }
  {
    struct sockaddr_un name;
    name.sun_family = AF_UNIX;
    strcpy(name.sun_path,"socket.tst"); unlink("socket.tst");
    if (bind(s,(struct sockaddr *)&name,sizeof(name)) == -1) fail("bind");
    if (listen(s,2) == -1) fail("listen");
  }
  {
    int flags;
    if ((flags = fcntl(s,F_GETFL)) == -1) fail("fcntl(F_GETFL)");
#ifdef USE_NDELAY
    if (fcntl(s,F_SETFL,flags | O_NDELAY) == -1)
      fail("fcntl(F_SETFL,O_NDELAY)");
#else
    if (fcntl(s,F_SETFL,flags | O_NONBLOCK) == -1)
      fail("fcntl(F_SETFL,O_NONBLOCK)");
#endif
  }
  {
    struct sigaction a;
    a.sa_handler = handler; sigfillset(&a.sa_mask);
    a.sa_flags = 0; sigaction(SIGALRM,&a,NULL);
  }
  {
    struct itimerval it;
    it.it_interval.tv_usec = 0; it.it_interval.tv_sec = 0;
    it.it_value.tv_usec = 0; it.it_value.tv_sec = 1;
    if (setitimer(ITIMER_REAL,&it,NULL) == -1) fail("setitimer");
  }
  {
    struct sockaddr sa;
    int len = sizeof(struct sockaddr);
    if (accept(s,&sa,&len) != -1) fail("accept succeeded");
    if (errno != EAGAIN && errno != EWOULDBLOCK) fail("accept failed");
  }
  close(s);
  unlink("socket.tst");
  return 0;
}
