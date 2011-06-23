/*
 * Check result type of sprintf.
 */

#include "config.h"
#include "test.h"
#include <stdio.h>

int main (void)
{
  char c[10];
#ifdef BAD_SPRINTF
  char *p = sprintf(c,"%d",55);
  fprintf(stderr,"String %s (length %ld)\n",c,strlen(p));
  return (strcmp(c,"55") != 0 || strlen(p) != 2);
#else
  int n = sprintf(c,"%d",55);
  fprintf(stderr,"String %s (length %d)\n",c,n);
  return (strcmp(c,"55") != 0 || n != 2);
#endif
}
