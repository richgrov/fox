#include "preproc.h"

#include <errno.h>
#include <stdio.h>

#include "memory.h"

PreprocessResult preprocess(FILE *file, PreprocToken **out_tokens) {
   char buf[16 * 1024];
   size_t len;

   do {
      len = fread(buf, sizeof(buf[0]), FOX_ARRLEN(buf), file);
      printf("%.*s", (int)len, buf);
   } while (len == FOX_ARRLEN(buf));

   if (!feof(file)) {
      return errno;
   }

   return PREPROCESS_OK;
}
