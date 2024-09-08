#include "preproc.h"

#include <stdio.h>

void preprocess(const char *src, size_t size) {
   printf("%.*s", (int)size, src);
}
