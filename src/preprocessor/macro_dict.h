#ifndef FOX_MACRO_DICT_H_
#define FOX_MACRO_DICT_H_

#include <stdbool.h>

typedef struct {
   const char *expansion;
   const char **params;
   int num_params;
} MacroDef;

typedef unsigned short MacroDictNodeId;

typedef struct {
   const char *key;
   unsigned long hash;
   MacroDef value;
   MacroDictNodeId next;
} MacroDictNode;

typedef struct {
   MacroDictNode nodes[1024];
   MacroDictNodeId buckets[32];
   MacroDictNodeId next_avail;
} MacroDictionary;

void macro_dict_init(MacroDictionary *dict);

bool macro_dict_put(MacroDictionary *dict, const char *key, const MacroDef *value);

const MacroDef *macro_dict_get(MacroDictionary *dict, const char *key);

#endif // !FOX_MACRO_DICT_H_
