#include "config.h"
#include "test.h"

char buffer[27];

void main (void)
{
  COPY(buffer,"abcdefghijklmnopqrstuvwxyz",27);
  if (strcmp(buffer,"abcdefghijklmnopqrstuvwxyz") != 0) exit(1);
  COPY(buffer+3,buffer,26-3);
  if (strcmp(buffer,"abcabcdefghijklmnopqrstuvw") != 0) exit(1);
  COPY(buffer,"abcdefghijklmnopqrstuvwxyz",27);
  COPY(buffer,buffer+3,26-3);
  if (strcmp(buffer,"defghijklmnopqrstuvwxyzxyz") != 0) exit(1);
  exit(0);
}
