#include "macro_dict.h"

#include <string.h>

#include "assert.h"

void test_macro_dict() {
   MacroDictionary dict = {};

   macro_dict_put(&dict, "one", "world");
   FOX_ASSERT(strcmp(macro_dict_get(&dict, "one"), "world") == 0);

   macro_dict_put(&dict, "two", "three");
   FOX_ASSERT(strcmp(macro_dict_get(&dict, "two"), "three") == 0);

   FOX_ASSERT(macro_dict_get(&dict, "three") == NULL);
}
