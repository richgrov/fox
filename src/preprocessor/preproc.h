#ifndef FOX_PREPROC_H_
#define FOX_PREPROC_H_

#include <stdio.h>

#include "operator.h"

typedef enum {
   ERR_EOF,
   ERR_UNEXPECTED,
} PreprocError;

typedef enum {
   PROC_ERROR, // not in the standard, but used internally
   PROC_IDENTIFIER,
   PROC_NUMBER,
   PROC_CHAR,
   PROC_STR,
   PROC_CHEVRON_STR, // #include strings quoted in < >
   PROC_OPERATOR,
   PROC_MISC, // non-whitespace, non-comment character that isn't any of the above
} PreprocType;

typedef struct {
   PreprocType type;
   union {
      char char_data;
      char *str_data;
      Operator op_data;
      PreprocError err_data;
   };
} PreprocToken;

void preprocess(const char *src, size_t size);

#endif // !FOX_PREPROC_H_
