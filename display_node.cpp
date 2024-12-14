
#include "display_node.h"
#include "ref_node.h"
#include <iostream>
ASTResult DisplayNode::eval(RefEnv *env) {
  ASTResult result = right()->eval(env);
  if(result.type == ASTResult::INT) {
      std::cout << result.value.i << std::endl;
    } else if(result.type == ASTResult::REAL) {
      std::cout << result.value.r << std::endl;
    }
  result.type = ASTResult::VOID;
  return result;
}

// must have this to satisfy the pure virtual function
ASTResult DisplayNode::apply(const ASTResult &lhs, const ASTResult &rhs) {
  // This function is never called
  return ASTResult();
}