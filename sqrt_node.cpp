
#include "sqrt_node.h"
#include "ref_node.h"
#include <iostream>
#include "cmath"
ASTResult SqrtNode::eval(RefEnv *env) {
  ASTResult result = right()->eval(env);
  if(result.type == ASTResult::REAL) {
      result.value.r = sqrt(result.value.r);
  } else if(result.type == ASTResult::INT) {
      result.value.r = sqrt(result.value.i);
  }
  result.type = ASTResult::REAL;
  return result;
}

// must have this to satisfy the pure virtual function
ASTResult SqrtNode::apply(const ASTResult &lhs, const ASTResult &rhs) {
  // This function is never called
  return ASTResult();
}