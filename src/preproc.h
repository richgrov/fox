#ifndef FOX_PREPROC_H_
#define FOX_PREPROC_H_

#include <stdio.h>

typedef enum {
   PREPROCESS_OK,
   PREPROCESS_READ_FAIL,
} PreprocessResult;

typedef struct {
} PreprocToken;

PreprocessResult preprocess(FILE *file, PreprocToken **out_tokens);

#endif // !FOX_PREPROC_H_
