#include "macro_dict.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

void macro_dict_put(MacroDictionary *dict, const char *key, const MacroDef *value) {
   unsigned long hash = fnv1a_hash(key);

   MacroDictionaryNode *node = &dict->buckets[hash % 32];
   if (node->key == NULL) {
      node->key = key;
      node->value = *value;
      node->hash = hash;
      return;
   }

   while (node->next != NULL) {
      node = node->next;
   }

   MacroDictionaryNode *new = malloc(sizeof(*node->next));
   memset(new, 0, sizeof(*new));
   new->key = key;
   new->value = *value;
   new->hash = hash;
   node->next = new;
}

const MacroDef *macro_dict_get(MacroDictionary *dict, const char *key) {
   unsigned long hash = fnv1a_hash(key);

   MacroDictionaryNode *node = &dict->buckets[hash % 32];
   while (node != NULL) {
      if (hash == node->hash && strcmp(key, node->key) == 0) {
         return &node->value;
      }

      node = node->next;
   }

   return NULL;
}
