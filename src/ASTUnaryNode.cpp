#include "ASTUnaryNode.hpp"
#include <cmath>

ASTUnaryNode::ASTUnaryNode(TokenType unary_operator, std::shared_ptr<ASTNode> child)
   :m_unary_operator{unary_operator}
   ,m_child{child}
{
}

double ASTUnaryNode::evaluate(double x) const 
{
   switch (m_unary_operator)
   {
   case UNARY_PLUS: return plus(x);
   case UNARY_MINUS: return minus(x);
   case SQRT: return sqrt(x);
   case EXP: return exp(x);
   case LN: return ln(x);
   case LOG: return log(x);
   case PLUS:
   case MINUS:
   case MULTIPLY:
   case DIVIDE:
   case POWER:
   case NUMBER:
   case X:
   case LPAREN:
   case RPAREN:
      break;
   }
   return 0.0; // shouldn't happen
}

double ASTUnaryNode::plus(double x) const
{
   return m_child->evaluate(x);
}

double ASTUnaryNode::minus(double x) const
{
   return -m_child->evaluate(x);
}

double ASTUnaryNode::sqrt(double x) const
{
   return std::sqrt(m_child->evaluate(x));
}

double ASTUnaryNode::exp(double x) const
{
   return std::exp(m_child->evaluate(x));
}

double ASTUnaryNode::ln(double x) const
{
   return std::log(m_child->evaluate(x));
}

double ASTUnaryNode::log(double x) const
{
   return std::log10(m_child->evaluate(x));
}
