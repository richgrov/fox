#ifndef FOX_OPERATOR_H_
#define FOX_OPERATOR_H_

typedef enum {
   OP_PLUS,
   OP_MINUS,
   OP_STAR,
   OP_SLASH,
   OP_BANG,
   OP_AMPERSAND,
   OP_PIPE,
   OP_UP_CARET,
   OP_PLUS_EQUAL,
   OP_MINUS_EQUAL,
   OP_STAR_EQUAL,
   OP_SLASH_EQUAL,
   OP_BANG_EQUAL,
   OP_AMPERSAND_EQUAL,
   OP_PIPE_EQUAL,
   OP_UP_CARET_EQUAL,
} Operator;

const char *operator_to_str(Operator op);

#endif // !FOX_OPERATOR_H_
