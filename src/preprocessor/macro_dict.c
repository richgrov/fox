#include "macro_dict.h"

#include <stdint.h>

#if UINTPTR_MAX == 0xFFFFFFFF

#define FNV1A_OFFSET_BASIS 2166136261UL
#define FNV1A_PRIME 16777619UL

#elif UINTPTR_MAX == 0xFFFFFFFFFFFFFFFF

#define FNV1A_OFFSET_BASIS 14695981039346656037UL
#define FNV1A_PRIME 1099511628211UL

#endif

static unsigned long fnv1a_hash(const char *txt) {
   unsigned long result = FNV1A_OFFSET_BASIS;

   for (const char *c = txt; *c; ++c) {
      result ^= (unsigned char)*c;
      result *= FNV1A_PRIME;
   }

   return result;
}
