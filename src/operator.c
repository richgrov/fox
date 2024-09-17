#include "operator.h"

const char *operator_to_str(Operator op) {
   switch (op) {
   case OP_PLUS:
      return "+";
   case OP_MINUS:
      return "-";
   case OP_STAR:
      return "*";
   case OP_SLASH:
      return "/";
   case OP_PERCENT:
      return "%";
   case OP_BANG:
      return "!";
   case OP_AMPERSAND:
      return "&";
   case OP_PIPE:
      return "|";
   case OP_UP_CARET:
      return "^";
   case OP_PLUS_EQUAL:
      return "+=";
   case OP_MINUS_EQUAL:
      return "-=";
   case OP_STAR_EQUAL:
      return "*=";
   case OP_SLASH_EQUAL:
      return "/=";
   case OP_PERCENT_EQUAL:
      return "%=";
   case OP_BANG_EQUAL:
      return "!=";
   case OP_AMPERSAND_EQUAL:
      return "&=";
   case OP_PIPE_EQUAL:
      return "|=";
   case OP_UP_CARET_EQUAL:
      return "^=";
   default:
      return "???";
   }
}
