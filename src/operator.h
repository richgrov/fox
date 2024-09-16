#ifndef FOX_OPERATOR_H_
#define FOX_OPERATOR_H_

typedef enum {
   OP_PLUS,
   OP_MINUS,
   OP_STAR,
   OP_SLASH,
} Operator;

const char *operator_to_str(Operator op);

#endif // !FOX_OPERATOR_H_
