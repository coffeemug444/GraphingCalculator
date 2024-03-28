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
   PLUS,
   MINUS,
   MULTIPLY,
   DIVIDE,
   POWER,
   SQRT,
   UNARY_PLUS,
   UNARY_MINUS,
   LPAREN,
   RPAREN
};

std::ostream& operator<< (std::ostream& out, TokenType type);

class NotATokenException : public std::exception {
public:
    NotATokenException(const std::string& message) : m_message(message) {}

    // Override the what() method to provide a description of the error
    const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
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

   static std::vector<Token> tokenise(std::string_view str);

private:
   TokenType m_type;
   std::string m_value;
   const static std::map<TokenType, int> m_precedence_map;
};