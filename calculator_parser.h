// File: calculator_parser.h
// Purpose: This file contains the definition of the calculator parser.
// Author: Robert Lowe
#ifndef CALCULATOR_PARSER_H
#define CALCULATOR_PARSER_H
#include "ast_node.h"
#include "calculator_lexer.h"

class CalculatorParser {
public:
  ASTNode *parse(CalculatorLexer *_lexer);

private:
  CalculatorLexer *_lexer;
  Lexer::Token _cur;

  // advance the lexer
  void next();
  ASTNode *parse_display();
  ASTNode *parse_input();
  ASTNode *parse_sqrt();
  // check to see if the cur  rent token matches the given token
  bool has(int t);

  // < Expression > ::= < Ref > < Expression' > 
  //                    | < Sum >                       
  ASTNode *parse_expression();

  // < Expression' > ::= ASSIGN < Expression >
  //                     | < Sum' >
  ASTNode *parse_expression2(ASTNode *left);

  //< Sum > ::= < Term > < Sum' >
  ASTNode *parse_sum();

  //< Sum' >::= ADD < Term > < Sum' >
  //                   | SUB < Term > < Sum' >
  //                   | ""
  ASTNode *parse_sum2(ASTNode *left);
                     
  //< Term >       ::= < Factor > < Term' > 
  ASTNode *parse_term();

  //< Term' >      ::= MUL < Factor > < Term' >
  //                   | DIV < Factor > < Term' >
  //                   | ""
  ASTNode *parse_term2(ASTNode *left);
  
  //< Factor >     ::= < Exponent > < Factor' >
  ASTNode *parse_factor();

  //< Factor' >    ::= POW < Exponent >
  //                   | ""
  ASTNode *parse_factor2(ASTNode *left);

  //< Exponent >   ::= INT 
  //                   | REAL
  //                   | < Ref >
  //                   | LPAR < Expression > RPAR
  ASTNode *parse_exponent();

  //< Ref >        ::= ID
  ASTNode *parse_ref();

  
};

#endif