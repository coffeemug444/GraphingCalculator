#include "Token.hpp"
#include <sstream>


std::ostream& operator<< (std::ostream& out, TokenType type)
{
   switch (type)
   {
   case NUMBER:      out << "NUMBER"; break;
   case X:           out << "X"; break;
   case CONSTANT:    out << "CONSTANT"; break;
   case PLUS:        out << "PLUS"; break;
   case MINUS:       out << "MINUS"; break;
   case MULTIPLY:    out << "MULTIPLY"; break;
   case DIVIDE:      out << "DIVIDE"; break;
   case POWER:       out << "POWER"; break;
   case SQRT:        out << "SQRT"; break;
   case EXP:         out << "EXP"; break; 
   case LN:          out << "LN"; break;  
   case LOG:         out << "LOG"; break;
   case SIN:         out << "SIN"; break;
   case COS:         out << "COS"; break;
   case TAN:         out << "TAN"; break;
   case ARCSIN:      out << "ARCSIN"; break;
   case ARCCOS:      out << "ARCCOS"; break;
   case ARCTAN:      out << "ARCTAN"; break;
   case STEP:        out << "STEP"; break;
   case ABS:         out << "ABS"; break;
   case REAL:        out << "REAL"; break;
   case IMAG:        out << "IMAG"; break;
   case UNARY_PLUS:  out << "UNARY_PLUS"; break;
   case UNARY_MINUS: out << "UNARY_MINUS"; break;
   case LPAREN:      out << "LPAREN"; break;
   case RPAREN:      out << "RPAREN"; break;
   }
   return out;
}

std::ostream& operator<< (std::ostream& out, const Token& token)
{
   out << token.getValue() << " (" << token.getType() << ")";
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
   {EXP, 4},
   {LN, 4},
   {LOG, 4},
   {SIN, 4},
   {COS, 4},
   {TAN, 4},
   {ARCSIN, 4},
   {ARCCOS, 4},
   {ARCTAN, 4},
   {STEP, 4},
   {ABS, 4},
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
   case NUMBER:
   case X:
   case CONSTANT:
   case SQRT:
   case EXP:
   case LN:
   case LOG:
   case UNARY_PLUS:
   case UNARY_MINUS:
   case LPAREN:
   case RPAREN:
   case SIN:
   case COS:
   case TAN:
   case ARCSIN:
   case ARCCOS:
   case ARCTAN:
   case STEP:
   case ABS:
      break;
   }
   return false;
}

bool Token::isUnaryOperator() const
{
   switch (m_type)
   {
   case SQRT:
   case EXP:
   case LN:
   case LOG:
   case SIN:
   case COS:
   case TAN:
   case ARCSIN:
   case ARCCOS:
   case ARCTAN:
   case UNARY_PLUS:
   case UNARY_MINUS:
   case STEP:
   case ABS:
   case REAL:
   case IMAG:
      return true;
   case PLUS:
   case MINUS:
   case MULTIPLY:
   case DIVIDE:
   case POWER:
   case NUMBER:
   case X:
   case CONSTANT:
   case LPAREN:
   case RPAREN:
      break;
   }
   return false;
}

bool Token::isNumber() const
{
   switch (m_type)
   {
   case NUMBER:
   case X:
   case CONSTANT:
      return true;
   case SQRT:
   case EXP:
   case LN:
   case LOG:
   case SIN:
   case COS:
   case TAN:
   case ARCSIN:
   case ARCCOS:
   case ARCTAN:
   case UNARY_PLUS:
   case UNARY_MINUS:
   case STEP:
   case ABS:
   case REAL:
   case IMAG:
   case PLUS:
   case MINUS:
   case MULTIPLY:
   case DIVIDE:
   case POWER:
   case LPAREN:
   case RPAREN:
      break;
   }
   return false;
}

