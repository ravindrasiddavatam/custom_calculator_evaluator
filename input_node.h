
#ifndef INPUT_NODE_H
#define INPUT_NODE_H
#include "binop_node.h"

class InputNode : public BinopNode {
public:
  // evaluate the assignment
  virtual ASTResult eval(RefEnv *env);

  // must have this to satisfy the pure virtual function
  virtual ASTResult apply(const ASTResult &lhs, const ASTResult &rhs);
};
#endif