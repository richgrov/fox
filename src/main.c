#include <errno.h>
#include <stdio.h>

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

   PreprocToken *tokens;
   switch (preprocess(file, &tokens)) {
   case PREPROCESS_READ_FAIL:
      char errmsg[512];
      snprintf(errmsg, sizeof(errmsg), "failed to read %s", argv[1]);
      perror(errmsg);
      goto err;

   case PREPROCESS_OK:
      break;
   }

   fclose(file);
   return 0;

err:
   fclose(file);
   return -1;
}
