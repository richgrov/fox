#ifndef FOX_ASSERT_H_
#define FOX_ASSERT_H_

#include <stdio.h>
#include <stdlib.h>

#define FOX_ASSERT(x)                                                                              \
   if (!(x)) {                                                                                     \
      printf("%s:%d: assertion failed\n", __FILE__, __LINE__);                                     \
      abort();                                                                                     \
   }

#endif // !FOX_ASSERT_H_
