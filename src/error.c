#include "error.h"

#include <stdarg.h>
#include <stdio.h>

void perrorf(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);

   char msg[512];
   vsnprintf(msg, sizeof(msg), fmt, args);
   perror(msg);

   va_end(args);
}
