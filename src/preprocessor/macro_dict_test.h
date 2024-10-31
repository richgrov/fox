#include "macro_dict.h"

#include <stdbool.h>
#include <string.h>

#include "assert.h"

static bool macro_def_eq(const MacroDef *m1, const MacroDef *m2) {
   if (m1 != m2 && (m1 == NULL || m2 == NULL)) {
      return false;
   }

   if (!strcmp(m1->expansion, m2->expansion)) {
      return false;
   }

   if (m1->num_params != m2->num_params) {
      return false;
   }

   for (int i = 0; i < m1->num_params; ++i) {
      if (strcmp(m1->params[i], m2->params[i]) != 0) {
         return false;
      }
   }

   return true;
}

void test_macro_dict() {
   MacroDictionary dict = {};
   macro_dict_init(&dict);

   const char *args1[] = {"a", "b", "c"};
   const MacroDef d1 = {
      .params = args1,
      .num_params = 3,
      .expansion = "hi",
   };
   macro_dict_put(&dict, "one", &d1);
   FOX_ASSERT(macro_def_eq(macro_dict_get(&dict, "one"), &d1) == 0);

   const char *args2[] = {"d", "e", "f", "g"};
   const MacroDef d2 = {
      .params = args2,
      .num_params = 4,
      .expansion = "bye",
   };
   macro_dict_put(&dict, "two", &d2);
   FOX_ASSERT(macro_def_eq(macro_dict_get(&dict, "two"), &d2) == 0);

   FOX_ASSERT(macro_dict_get(&dict, "three") == NULL);
}
