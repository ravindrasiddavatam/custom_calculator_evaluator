
#ifndef SQRT_NODE_H
#define SQRT_NODE_H
#include "binop_node.h"

class SqrtNode : public BinopNode {
public:
  // evaluate the root
  virtual ASTResult eval(RefEnv *env);

  // must have this to satisfy the pure virtual function
  virtual ASTResult apply(const ASTResult &lhs, const ASTResult &rhs);
};
#endif