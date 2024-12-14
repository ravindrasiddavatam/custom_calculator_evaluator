#include "input_node.h"
#include "ref_node.h"
#include <iostream>

// evaluate the Input
ASTResult InputNode::eval(RefEnv *env) {



  ASTResult holder;
  std::string input;
  holder.type = ASTResult::REAL;
  RefNode *ref = (RefNode *) right();




  if(left()){
    left()->eval(env);
    getline(std::cin, input);
  } else {
    std::cout << ref->name() <<"=";
    getline(std::cin, input);
  }
  
  
  

  holder.value.r = std::stof(input);
  ref->assign(env, holder);
  ASTResult mains;
  mains.type = ASTResult::VOID;
  return mains;
}

// must have this to satisfy the pure virtual function
ASTResult InputNode::apply(const ASTResult &lhs, const ASTResult &rhs) {
  // This function is never called
  return ASTResult();
}