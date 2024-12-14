
#ifndef DISPLAY_NODE_H
#define DISPLAY_NODE_H
#include "binop_node.h"

class DisplayNode : public BinopNode {
public:
  // evaluate the display
  virtual ASTResult eval(RefEnv *env);

  // must have this to satisfy the pure virtual function
  virtual ASTResult apply(const ASTResult &lhs, const ASTResult &rhs);
};
#endif