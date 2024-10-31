#include "macro_dict.h"

#include <string.h>

#include "assert.h"

void test_macro_dict() {
   MacroDictionary dict = {};
   macro_dict_put(&dict, "hello", "world");
   const char *value = macro_dict_get(&dict, "hello");
   FOX_ASSERT(strcmp(value, "world") == 0);
}
