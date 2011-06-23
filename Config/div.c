/*
 * We use separate functions for div and mod to avoid constant folding,
 * and then check that / and % round towards zero.
 */

#include "config.h"
#include <stdio.h>

int div (int x,int y) { return (x / y); }
int mod (int x,int y) { return (x % y); }

int main (void)
{
  int a = div(-5,3);
  int b = mod(-5,3);
  fprintf(stderr,"-5 div 3 = %d\n",a);
  fprintf(stderr,"-5 mod 3 = %d\n",b);
  return ((a != -1) || (b != -2));
}
