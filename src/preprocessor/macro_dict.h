#ifndef FOX_MACRO_DICT_H_
#define FOX_MACRO_DICT_H_

typedef struct MacroDictionaryNode {
   struct MacroDictionaryNode *next;
   const char *key;
   const char *value;
   unsigned long hash;
} MacroDictionaryNode;

typedef struct {
   struct MacroDictionaryNode buckets[32];
} MacroDictionary;

void macro_dict_put(MacroDictionary *dict, const char *key, const char *value);

const char *macro_dict_get(MacroDictionary *dict, const char *key);

#endif // !FOX_MACRO_DICT_H_
