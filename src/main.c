#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "preproc.h"

int main(int argc, char **argv) {
   if (argc < 2) {
      puts("error: no files specified");
      return -1;
   }

   FILE *file = fopen(argv[1], "r");
   if (file == NULL) {
      char errmsg[512];
      snprintf(errmsg, sizeof(errmsg), "failed to open %s", argv[1]);
      perror(errmsg);
      return errno;
   }

   int retval = 0;

   PreprocToken *tokens;
   Vector src = {};

   switch (preprocess(file, &src, &tokens)) {
   case PREPROCESS_READ_FAIL:
      char errmsg[512];
      snprintf(errmsg, sizeof(errmsg), "failed to read %s", argv[1]);
      perror(errmsg);
      retval = -1;
      goto err_read;

   case PREPROCESS_OOM:
      fprintf(stderr, "failed to read %s: out of memory\n", argv[1]);
      retval = -1;
      goto err_read;

   case PREPROCESS_OK:
      break;
   }

   printf("%.*s", (int)src.size, (char *)src.alloc);
   vector_deinit(&src);

err_read:
   fclose(file);
   return retval;
}
