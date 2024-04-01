#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <utility>
#include <exception>
#include <map>
#include <iostream>

enum TokenType
{
   NUMBER,
   X,
   CONSTANT,
   PLUS,
   MINUS,
   MULTIPLY,
   DIVIDE,
   POWER,
   SQRT,
   EXP,
   LN,
   LOG,
   SIN,
   COS,
   TAN,
   ARCSIN,
   ARCCOS,
   ARCTAN,
   STEP,
   ABS,
   UNARY_PLUS,
   UNARY_MINUS,
   LPAREN,
   RPAREN
};

std::ostream& operator<< (std::ostream& out, TokenType type);

class BaseException : public std::exception
{
public:
    BaseException(const std::string& message) : m_message(message) {}

    // Override the what() method to provide a description of the error
    const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class NotATokenException : public BaseException 
{
public:
    NotATokenException(const std::string& message) : BaseException(message) {}
};

class TokenExpectedException : public BaseException 
{
public:
    TokenExpectedException(const std::string& message) : BaseException(message) {}
};

class UnexpectedTokenException : public BaseException 
{
public:
    UnexpectedTokenException(const std::string& message) : BaseException(message) {}
};


class Token
{
public:
   Token(TokenType type, std::string value);

   TokenType getType() const;
   std::string getValue() const;
   int getPrecedence() const { return m_precedence_map.at(m_type); }

   bool isBinaryOperator() const;
   bool isUnaryOperator() const;
   bool isOperator() const { return isBinaryOperator() or isUnaryOperator(); }
   bool isNumber() const;

private:
   TokenType m_type;
   std::string m_value;
   const static std::map<TokenType, int> m_precedence_map;
};

std::ostream& operator<< (std::ostream& out, const Token& token);