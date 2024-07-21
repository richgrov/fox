#include "preproc.h"
#include "vector.h"

#include <stdio.h>

PreprocessResult preprocess(FILE *file, Vector *src, PreprocToken **out_tokens) {
   PreprocessResult result = PREPROCESS_OK;

   if (!vector_init(src, 4096)) {
      return PREPROCESS_OOM;
   }

   size_t read_amount;
   size_t len;

   do {
      if (!vector_reserve(src, 4096)) {
         result = PREPROCESS_OOM;
         goto err_realloc;
      }

      char *begin = src->alloc + src->size;
      read_amount = src->capacity - src->size;
      len = fread(begin, 1, read_amount, file);
      src->size += len;
   } while (len == read_amount);

   if (!feof(file)) {
      result = PREPROCESS_READ_FAIL;
      goto err_realloc;
   }

   return PREPROCESS_OK;

err_realloc:
   vector_deinit(src);

   return result;
}
