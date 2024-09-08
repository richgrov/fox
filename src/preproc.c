#include "preproc.h"

#include <stdbool.h>
#include <stdio.h>

typedef enum {
   PROC_EOF, // not in the standard, but used internally
   PROC_HEADER,
   PROC_IDENTIFIER,
   PROC_NUMBER,
   PROC_CHAR,
   PROC_STR,
   PROC_OP,
   PROC_PUNCTUATOR,
   PROC_MISC, // non-whitespace, non-comment character that isn't any of the above
} PreprocType;

typedef struct {
   PreprocType type;
   char temp;
} PreprocToken;

typedef struct {
   const char *src;
   size_t size;
   size_t read_index;
} Preprocessor;

#define VERTICAL_TAB '\x0B'
#define FORM_FEED '\x0C'

static char decode_trigraph(char c) {
   switch (c) {
   case '=':
      return '#';
   case '(':
      return '[';
   case '/':
      return '\\';
   case ')':
      return ']';
   case '\'':
      return '^';
   case '<':
      return '{';
   case '!':
      return '|';
   case '>':
      return '}';
   case '-':
      return '~';
   default:
      return '\0';
   }
}

static char next(Preprocessor *proc) {
   if (proc->read_index >= proc->size) {
      return '\0';
   }

   char next = proc->src[proc->read_index];
   bool room_for_trigraph = proc->read_index + 2 < proc->size;
   if (next == '?' && room_for_trigraph) {
      if (proc->src[proc->read_index + 1] == '?') {
         char replaced = decode_trigraph(proc->src[proc->read_index + 2]);
         if (replaced != '\0') {
            proc->read_index += 3;
            return replaced;
         }
      }
   }

   ++proc->read_index;
   return next;
}

static bool is_whitespace(char c) {
   switch (c) {
   case ' ':
   case '\t':
   case '\n':
   case VERTICAL_TAB:
   case FORM_FEED:
      return true;
   default:
      return false;
   }
}

static void skip_whitespace(Preprocessor *proc) {
   while (proc->read_index < proc->size && is_whitespace(proc->src[proc->read_index])) {
      ++proc->read_index;
   }
}

static PreprocToken token(Preprocessor *proc) {
   skip_whitespace(proc);

   PreprocToken result;

   char c = next(proc);
   if (c == '\0') {
      result.type = PROC_EOF;
      return result;
   }

   result.temp = c;
   result.type = PROC_CHAR;
   return result;
}

void preprocess(const char *src, size_t size) {
   Preprocessor proc = {
      .src = src,
      .size = size,
      .read_index = 0,
   };

   for (PreprocToken tok = token(&proc); tok.type != PROC_EOF; tok = token(&proc)) {
      if (tok.temp != '\r') {
         printf("%c", tok.temp);
      }
   }
}
