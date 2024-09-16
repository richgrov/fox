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
   default:
      return "???";
   }
}
