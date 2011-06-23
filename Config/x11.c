#include "config.h"
#include "test.h"
#include <X11/Xlib.h>

int main (int argc, char **argv)
{
  if (argc) return 0;
  /*
   * The following code should never be reached.  It is present to
   * force a link error if we don't find the X11 library.
   */
  XOpenDisplay("");
  return 1;
}
