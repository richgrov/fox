#include "preproc.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operator.h"

typedef enum {
   PROC_EOF, // not in the standard, but used internally
   PROC_HEADER,
   PROC_IDENTIFIER,
   PROC_NUMBER,
   PROC_CHAR,
   PROC_STR,
   PROC_OPERATOR,
   PROC_MISC, // non-whitespace, non-comment character that isn't any of the above
} PreprocType;

typedef struct {
   PreprocType type;
   union {
      char char_data;
      char *str_data;
      Operator op_data;
   };
} PreprocToken;

static PreprocToken operator_token(Operator op) {
   PreprocToken result = {.type = PROC_OPERATOR, .op_data = op};
   return result;
}

typedef struct {
   const char *src;
   size_t size;
   size_t read_index;
} Preprocessor;

#define VERTICAL_TAB '\x0B'
#define FORM_FEED '\x0C'

static char try_decode_trigraph(Preprocessor *proc) {
   if (proc->read_index + 2 >= proc->size) {
      return '\0';
   }

   if (proc->src[proc->read_index] != '?' || proc->src[proc->read_index + 1] != '?') {
      return '\0';
   }

   switch (proc->src[proc->read_index + 2]) {
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

static char try_line_splice(Preprocessor *proc) {
   if (proc->read_index + 2 >= proc->size) {
      return '\0';
   }

   if (proc->src[proc->read_index] != '\\' || proc->src[proc->read_index + 1] != '\n') {
      return '\0';
   }

   return proc->src[proc->read_index + 2];
}

static char peek(Preprocessor *proc) {
   if (proc->read_index >= proc->size) {
      return '\0';
   }

   char trigraph = try_decode_trigraph(proc);
   if (trigraph != '\0') {
      return trigraph;
   }

   char next_line_char = try_line_splice(proc);
   if (next_line_char != '\0') {
      return next_line_char;
   }

   return proc->src[proc->read_index];
}

static char next(Preprocessor *proc) {
   if (proc->read_index >= proc->size) {
      return '\0';
   }

   char trigraph = try_decode_trigraph(proc);
   if (trigraph != '\0') {
      proc->read_index += 3;
      return trigraph;
   }

   char next_line_char = try_line_splice(proc);
   if (next_line_char != '\0') {
      proc->read_index += 3;
      return next_line_char;
   }

   return proc->src[proc->read_index++];
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

static bool is_alpha(char c) {
   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool is_digit(char c) {
   return c >= '0' && c <= '9';
}

static void skip_whitespace(Preprocessor *proc) {
   while (proc->read_index < proc->size && is_whitespace(proc->src[proc->read_index])) {
      ++proc->read_index;
   }
}

static PreprocToken identifier(Preprocessor *proc, char first) {
   char identifier[128] = {first};
   int identifier_index = 1;

   while (proc->read_index < proc->size) {
      // TODO: limit to 128 chars
      char c = peek(proc);
      if (!is_alpha(c) && !is_digit(c) && c != '_') {
         break;
      }

      identifier[identifier_index++] = c;
      next(proc);
   }

   char *str = malloc(identifier_index + 1);
   memcpy(str, identifier, identifier_index + 1);

   PreprocToken result = {
      .type = PROC_IDENTIFIER,
      .str_data = str,
   };
   return result;
}

static PreprocToken token(Preprocessor *proc) {
   skip_whitespace(proc);

   PreprocToken result = {0};

   char c = next(proc);
   switch (c) {
   case '\0':
      result.type = PROC_EOF;
      return result;

   case '+':
      return operator_token(OP_PLUS);

   case '-':
      return operator_token(OP_MINUS);

   case '*':
      return operator_token(OP_STAR);

   case '/':
      return operator_token(OP_SLASH);

   default:
      if (is_alpha(c) || c == '_') {
         return identifier(proc, c);
      }
      break;
   }

   result.char_data = c;
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
      switch (tok.type) {
      case PROC_EOF:
         break;

      case PROC_IDENTIFIER:
         printf("%s\n", tok.str_data);
         break;

      case PROC_OPERATOR:
         printf("%s\n", operator_to_str(tok.op_data));
         break;

      case PROC_CHAR:
         if (tok.char_data != '\r') {
            printf("%c\n", tok.char_data);
         }

      default:
         break;
      }
   }
}
