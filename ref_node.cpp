// File: ref_node.cpp
// Purpose: Implementation of the reference node.
#include <iostream>
#include <string.h>
#include "ref_node.h"

// Constructor and Destructor
RefNode::RefNode(const std::string &_name) {
  this->_name = _name;  
}
std::string StringVar(const std::string& input) {
    std::string result;
    bool escape = false;
    for (char c : input) {
        if (!escape && c == '\\') {
            escape = true;
        } else {
            if (!escape && c == '"') {
            } else {
                if (escape) {
                    switch (c) {
                        case 'n': result += '\n'; break;
                        default:result += c;
                    } escape = false;
                } else {
                    result += c;
                }
            }
        }
    }
    return result;
}
RefNode::~RefNode() {
  
}

// Evaluate the node
ASTResult RefNode::eval(RefEnv *env) {
  ASTResult *result = env->lookup(this->_name);
  if (this->_name.find('"') != std::string::npos) {
    std::cout << StringVar(this->_name);
    ASTResult error;
    error.type = ASTResult::VOID;
    return error;
  }  
  if(!result) {
    //TODO: Better error handling
    std::cerr << "Error: Variable " << this->_name << " not found." << std::endl;
    ASTResult error;
    error.type = ASTResult::VOID;
    return error;
  }

  return *result;
}

// Assign a value to the reference
void RefNode::assign(RefEnv *env, ASTResult _value) {
  // the logic of local declaration
  // if not defined, add it and then assign a value
  ASTResult *result = env->lookup(this->_name);
  if(!result) {
    env->declare(this->_name);
    result = env->lookup(this->_name);
  }

  // assign the value
  *result = _value;
}