#include "macro_dict.h"
#include "array.h"

#include <stdbool.h>
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

#define NODE_NULL 0xFFFF

static unsigned long fnv1a_hash(const char *txt) {
   unsigned long result = FNV1A_OFFSET_BASIS;

   for (const char *c = txt; *c; ++c) {
      result ^= (unsigned char)*c;
      result *= FNV1A_PRIME;
   }

   return result;
}

void macro_dict_init(MacroDictionary *dict) {
   memset(dict, 0, sizeof(*dict));

   int num_nodes = FOX_ARRLEN(dict->nodes);
   for (int i = 0; i < num_nodes; ++i) {
      dict->nodes[i].next = i + 1;
   }
   dict->nodes[num_nodes - 1].next = NODE_NULL;

   for (int i = 0; i < FOX_ARRLEN(dict->buckets); ++i) {
      dict->buckets[i] = NODE_NULL;
   }
}

bool macro_dict_put(MacroDictionary *dict, const char *key, const MacroDef *value) {
   if (dict->next_avail == NODE_NULL) {
      return false;
   }

   unsigned long hash = fnv1a_hash(key);
   MacroDictNodeId *parent = &dict->buckets[hash % 32];

   while (*parent != NODE_NULL) {
      parent = &dict->nodes[*parent].next;
   }
   *parent = dict->next_avail;

   MacroDictNode *new = &dict->nodes[dict->next_avail];
   dict->next_avail = new->next;
   memset(new, 0, sizeof(*new));
   new->key = key;
   new->hash = hash;
   new->value = *value;
   new->next = NODE_NULL;
   return true;
}

const MacroDef *macro_dict_get(MacroDictionary *dict, const char *key) {
   unsigned long hash = fnv1a_hash(key);

   MacroDictNodeId node_id = dict->buckets[hash % 32];
   while (node_id != NODE_NULL) {
      MacroDictNode *node = &dict->nodes[node_id];

      if (hash == node->hash && strcmp(key, node->key) == 0) {
         return &node->value;
      }

      node_id = node->next;
   }

   return NULL;
}
