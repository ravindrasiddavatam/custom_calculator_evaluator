// File: calculator_parser.cpp
// Purpose: This file contains the implementation of the calculator parser.

#include "calculator_parser.h"
#include "add_node.h"
#include "divide_node.h"
#include "multiply_node.h"
#include "pow_node.h"
#include "subtract_node.h"
#include "number_node.h"
#include "ref_node.h"
#include "assign_node.h"
#include "display_node.h"
#include "input_node.h"
#include <stdexcept>
#include "sqrt_node.h"
// advance the lexer
void CalculatorParser::next() { _cur = _lexer->next(); }

// check to see if the current token matches the given token
bool CalculatorParser::has(int t) { return _cur.tok == t; }


// < Expression > ::= < Ref > < Expression' > 
//                    | < Sum >                       
ASTNode *CalculatorParser::parse_expression() {
  if(has(CalculatorLexer::ID)) {
    ASTNode *left = parse_ref();
    return parse_expression2(left);
  } else if(has(CalculatorLexer::DISPLAY)) {
    return parse_display();
  } else if(has(CalculatorLexer::INPUT)) {
    return parse_input();
  } else if(has(CalculatorLexer::SQRT)) {
    return parse_sqrt();
  }

  return parse_sum();
}

// < Expression' > ::= ASSIGN < Expression >
//                     | < Sum' >
ASTNode *CalculatorParser::parse_expression2(ASTNode *left) {
  if(has(CalculatorLexer::ASSIGN)) {
    next();
    AssignNode *node = new AssignNode();
    node->left(left);
    node->right(parse_expression());
    return node;
  }

  return parse_sum2(left);
}

// < Sum > ::= < Term > < Sum’ >
ASTNode *CalculatorParser::parse_sum() {
  ASTNode *node = parse_term();
  return parse_sum2(node);
}

// < Sum' > ::= ADD <Term> <Sum'>
//                   | SUB <Term> <Sum'>
//                   | ""
ASTNode *CalculatorParser::parse_sum2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::ADD)) {
    next(); // consume ADD
    result = new AddNode();
  } else if (has(CalculatorLexer::SUB)) {
    next(); // consume SUB
    result = new SubtractNode();
  } else if (has(CalculatorLexer::MUL) || has(CalculatorLexer::DIV) || has(CalculatorLexer::POW)) {
    return parse_term2(left);
  }

  if(result) {
    result->left(left);
    result->right(parse_term());
    return parse_sum2(result);
  }

  return left; // epsilon
}

// <Term> ::= <Factor> <Term'>
ASTNode *CalculatorParser::parse_term() {
  ASTNode *node = parse_factor();
  return parse_term2(node);
}

// <Term'> ::= MUL <Factor> <Term'>
//             | DIV <Factor> <Term'>
//             | ""
ASTNode *CalculatorParser::parse_term2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::MUL)) {
    next(); // consume MUL 
    result = new MultiplyNode();
  } else if (has(CalculatorLexer::DIV)) {
    next(); // consume DIV 
    result = new DivideNode();
  } else if (has(CalculatorLexer::POW)) {
    return parse_factor2(left);
  }

  if(result) {
    result->left(left);
    result->right(parse_term());
    return parse_term2(result);
  }

  return left; // epsilon
}
ASTNode *CalculatorParser::parse_input() {
  // detect an error
  if(!has(CalculatorLexer::INPUT)) {
    throw std::runtime_error("Expected INPUT");
  }
  next();
  InputNode *node = new InputNode();
  ASTNode *left =parse_ref();
  if(has(CalculatorLexer::SCOLLON)) {
    next();
    node->right(parse_ref());
    node->left(left);
    next();
  } else {
    node->right(left);
    next();
  }
  return node;
}
// <Factor> ::= <Exponent> <Factor'>
ASTNode *CalculatorParser::parse_factor() {
  ASTNode *node = parse_exponent();
  return parse_factor2(node);
}

// <Factor'> ::= POW <Exponent>
//               | ""
ASTNode *CalculatorParser::parse_factor2(ASTNode *left) {
  if (has(CalculatorLexer::POW)) {
    next(); // consume POW
    ASTNode *right = parse_exponent();
    PowNode *node = new PowNode();
    node->left(left);
    node->right(right);
    return parse_factor2(node);
  }

  return left; // epsilon
}

// <Exponent> ::= INT
//                | REAL
//                | LPAR <Expression> RPAR
//                | < Ref >
ASTNode *CalculatorParser::parse_exponent() {
  if (has(CalculatorLexer::INT) || has(CalculatorLexer::REAL)) {
    ASTNode *node = new NumberNode(_cur);
    next(); 
    return node;
  } else if (has(CalculatorLexer::LPAREN)) {
    next(); // consume LPAR
    ASTNode *node = parse_expression();
    if (!has(CalculatorLexer::RPAREN)) {
      throw std::runtime_error("Expected ')'");
    }
    next(); // consume RPAR
    return node;
  } else {
    return parse_ref();
  }
}


ASTNode *CalculatorParser::parse_sqrt() {
  // detect an error
  if(!has(CalculatorLexer::SQRT)) {
    throw std::runtime_error("Expected SQRT");
  }
  next();
  SqrtNode *node = new SqrtNode();
  node->right(parse_expression());
  next();
  return node;
}

//< Ref >        ::= ID
ASTNode *CalculatorParser::parse_ref() {
  // detect an error
  if(!has(CalculatorLexer::ID)) {
    throw std::runtime_error("Expected ID");
  }

  ASTNode *node = new RefNode(_cur.lexeme);
  next();
  return node;
}





ASTNode *CalculatorParser::parse(CalculatorLexer *lexer) {
  // initialize the lexer
  _lexer = lexer;
  next(); 
  
  ASTNode *result = parse_expression();
  return result;
}

ASTNode *CalculatorParser::parse_display() {
  // detect an error
  if(!has(CalculatorLexer::DISPLAY)) {
    throw std::runtime_error("Expected DISPLAY");
  }
    next();
    DisplayNode *node = new DisplayNode();
    node->right(parse_expression());
    next();
    return node;
}