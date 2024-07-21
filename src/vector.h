#ifndef FOX_VECTOR_H_
#define FOX_VECTOR_H_

#include <stdlib.h>

typedef struct {
   void *alloc;
   size_t size;
   size_t capacity;
} Vector;

static inline int vector_init(Vector *vec, size_t size) {
   vec->alloc = malloc(size);
   if (vec->alloc == NULL) {
      return 0;
   }

   vec->size = 0;
   vec->capacity = size;
   return 1;
}

static inline void vector_deinit(Vector *vec) {
   free(vec->alloc);
}

static inline int vector_reserve(Vector *vec, size_t addtl_size) {
   size_t min_size = vec->size + addtl_size;
   if (vec->capacity >= min_size) {
      return 1;
   }

   void *alloc = realloc(vec->alloc, min_size);
   if (alloc == NULL) {
      return 0;
   }

   vec->alloc = alloc;
   vec->capacity += addtl_size;
   return 1;
}

#endif // !FOX_VECTOR_H_
