#ifndef FOX_PREPROC_H_
#define FOX_PREPROC_H_

#include <stdio.h>

#include "vector.h"

typedef enum {
   PREPROCESS_OK,
   PREPROCESS_READ_FAIL,
   PREPROCESS_OOM,
} PreprocessResult;

typedef struct {
} PreprocToken;

PreprocessResult preprocess(FILE *file, Vector *src, PreprocToken **out_tokens);

#endif // !FOX_PREPROC_H_
