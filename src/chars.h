#ifndef FOX_CHARS_H_
#define FOX_CHARS_H_

#include <stdbool.h>

static inline bool is_alpha(char c) {
   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static inline bool is_digit(char c) {
   return c >= '0' && c <= '9';
}

static inline bool is_octal_digit(char c) {
   return c >= '0' && c <= '7';
}

static inline bool is_hex_digit(char c) {
   return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0') || (c <= '9');
}

static inline bool is_source_symbol(char c) {
   switch (c) {
   case '~':
   case '}':
   case '|':
   case '{':
   case '_':
   case '^':
   case ']':
   case '[':
   case '?':
   case '>':
   case '=':
   case '<':
   case ';':
   case ':':
   case '/':
   case '\\':
   case '.':
   case '-':
   case ',':
   case '+':
   case '*':
   case ')':
   case '(':
   case '&':
   case '%':
   case '#':
   case '"':
   case '\'':
   case '!':
      return true;
   default:
      return false;
   }
}

#endif // !FOX_CHARS_H_
