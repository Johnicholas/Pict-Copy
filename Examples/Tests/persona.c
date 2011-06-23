/*
 * A C version of Pict persona test (this is best way of ensuring that the
 * Pict version works ok, since the persona program is supposed to give
 * different results on different machines).
 */

#include "../../Runtime/pict.h"
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>

void main ()
{
  int n;
  gid_t *g;
  struct passwd *pwd;
  printf("Effective user id: %ld\n",(long)geteuid());
  printf("Effective group id: %ld\n",(long)getegid());
  printf("Real user id: %ld\n",(long)getuid());
  printf("Real group id: %ld\n",(long)getgid());
  printf("Supplementary groups:");
  n = getgroups(0,NULL);
  g = (gid_t *)malloc(n * sizeof(gid_t));
  if ((g == NULL) || (getgroups(n,g) < 0)) {
    fprintf(stderr,"Fatal error: getGroups");
    exit(1);
  };
  while (n--) printf(" %ld",(long)*g++);
  printf("\n");
  pwd = getpwuid(getuid());
  if (pwd == NULL) {
    fprintf(stderr,"Fatal error: uidPasswordInfo");
    exit(1);
  };
  printf("userName: %s\n",pwd->pw_name);
  printf("realName: %s\n",pwd->pw_gecos);
  printf("password: %s\n",pwd->pw_passwd);
  printf("homeDir : %s\n",pwd->pw_dir);
  printf("shell   : %s\n",pwd->pw_shell);
  exit(0);
}
