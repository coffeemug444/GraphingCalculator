#include "Token.hpp"
#include <sstream>


std::ostream& operator<< (std::ostream& out, TokenType type)
{
    switch (type)
    {
    case NUMBER:      out << "NUMBER"; break;
    case PLUS:        out << "PLUS"; break;
    case MINUS:       out << "MINUS"; break;
    case MULTIPLY:    out << "MULTIPLY"; break;
    case DIVIDE:      out << "DIVIDE"; break;
    case POWER:       out << "POWER"; break;
    case SQRT:        out << "SQRT"; break;
    case UNARY_PLUS:  out << "UNARY_PLUS"; break;
    case UNARY_MINUS: out << "UNARY_MINUS"; break;
    case LPAREN:      out << "LPAREN"; break;
    case RPAREN:      out << "RPAREN"; break;
    }
    return out;
}

// B - BRACKETS
// E - EXPONENTS
// D - DIVISION
// M - MULTIPLICATION
// A - ADDITION
// S - SUBTRACTION
const std::map<TokenType, int> Token::m_precedence_map
{
   {NUMBER, 6},
   {PLUS, 1},
   {MINUS, 1},
   {MULTIPLY, 2},
   {DIVIDE, 2},
   {POWER, 3},
   {SQRT, 4},
   {UNARY_PLUS, 5},
   {UNARY_MINUS, 5},
   {LPAREN, 6},
   {RPAREN, 6}
};

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

bool Token::isNumber() const
{
   return m_type == NUMBER;
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
