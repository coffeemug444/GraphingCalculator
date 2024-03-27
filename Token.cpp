#include "Token.hpp"
#include <sstream>


Token::Token(TokenType type, std::string value)
:m_type{type}
,m_value{value}
{
}

TokenType Token::getType() const
{
   return m_type;
}

std::string Token::getValue() const
{
   return m_value;
}

bool Token::isBinaryOperator() const
{
   switch (m_type)
   {
      case PLUS:
      case MINUS:
      case MULTIPLY:
      case DIVIDE:
      case POWER:
         return true;
      default:
         return false;
   }
}

bool Token::isUnaryOperator() const
{
   switch (m_type)
   {
      case UNARY_PLUS:
      case UNARY_MINUS:
      case SQRT:
         return true;
      default:
         return false;
   }
}


std::vector<Token> Token::tokenise(std::string_view str)
{
   std::vector<Token> tokens;

   unsigned pos = 0;
   bool unary_possible = true;

   // check if it's a 1 char operator
   while (pos < str.size())
   {
      switch (str.at(pos))
      {
      case ' ':
         ++pos;
         continue;
      case '+':
      {
         TokenType type = unary_possible ? UNARY_PLUS : PLUS;
         unary_possible = true;
         tokens.push_back(Token{type, "+"});
         ++pos;
         continue;
      }
      case '-':
      {
         TokenType type = unary_possible ? UNARY_MINUS : MINUS;
         unary_possible = true;
         tokens.push_back(Token{type, "-"});
         ++pos;
         continue;
      }
      case '*':
         unary_possible = true;
         tokens.push_back(Token{MULTIPLY, "*"});
         ++pos;
         continue;
      case '/':
         unary_possible = true;
         tokens.push_back(Token{DIVIDE, "*"});
         ++pos;
         continue;
      case '^':
         unary_possible = true;
         tokens.push_back(Token{POWER, "^"});
         ++pos;
         continue;
      case '(':
         unary_possible = true;
         tokens.push_back(Token{LPAREN, "("});
         ++pos;
         continue;
      case ')':
         unary_possible = false;
         tokens.push_back(Token{RPAREN, ")"});
         ++pos;
         continue;
      default:
         break;
      }

      // could still be sqrt, a number, or invalid

      // check for sqrt
      if (str.size() - pos >= 4 && std::string("sqrt") == str.substr(pos, 4))
      {
         tokens.push_back(Token{SQRT, "sqrt"});
         pos += 4;
         continue;
      }

      // check for number
      auto char_is_numeric = [](char c) {
         return (c >= '0' and c <= '9') or (c == '.');
      };
     
      int num_len = 0;
      while ((pos + num_len) < str.size() and char_is_numeric(str.at(pos + num_len)))
      {
         ++num_len;
      }

      if (num_len == 0)
      {
         // not a number and therefore invalid...
         std::stringstream ss;
         ss << "Found character '" << str.at(pos) << "' at position " << pos << " that could not be tokenised";
         throw NotATokenException(ss.str());
      }

      tokens.push_back(Token{NUMBER, std::string(str.substr(pos, num_len))});
      unary_possible = false;
      pos += num_len;
   }

   return tokens;
}
