#include "ASTUnaryNode.hpp"
#include <cmath>

ASTUnaryNode::ASTUnaryNode(TokenType unary_operator, std::shared_ptr<ASTNode> child)
   :m_unary_operator{unary_operator}
   ,m_child{child}
{
}

complex ASTUnaryNode::evaluate(complex x) const 
{
   complex child = m_child->evaluate(x);
   switch (m_unary_operator)
   {
   case UNARY_PLUS:  return child;
   case UNARY_MINUS: return -child;
   case SQRT:        return std::sqrt(child);
   case EXP:         return std::exp(child);
   case LN:          return std::log(child);
   case LOG:         return std::log10(child);
   case SIN:         return std::sin(child);
   case COS:         return std::cos(child);
   case TAN:         return std::tan(child);
   case ARCSIN:      return std::asin(child);
   case ARCCOS:      return std::acos(child);
   case ARCTAN:      return std::atan(child);
   case STEP:        return step(child);
   case ABS:         return std::abs(child);
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
   return 0.0; // shouldn't happen
}

complex ASTUnaryNode::step(complex x) const
{
   double r = x.real() <= 0.0 ? 0.0 : 1.0;
   double i = x.imag() <= 0.0 ? 0.0 : 1.0;
   return complex{r, i};
}
