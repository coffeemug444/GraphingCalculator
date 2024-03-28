#include "ASTUnaryNode.hpp"
#include <cmath>

ASTUnaryNode::ASTUnaryNode(TokenType unary_operator, std::shared_ptr<ASTNode> child)
   :m_unary_operator{unary_operator}
   ,m_child{child}
{
}

complex ASTUnaryNode::evaluate(complex x) const 
{
   switch (m_unary_operator)
   {
   case UNARY_PLUS: return plus(x);
   case UNARY_MINUS: return minus(x);
   case SQRT: return sqrt(x);
   case EXP: return exp(x);
   case LN: return ln(x);
   case LOG: return log(x);
   case SIN: return sin(x); 
   case COS: return cos(x); 
   case TAN: return tan(x); 
   case ARCSIN: return arcsin(x); 
   case ARCCOS: return arccos(x); 
   case ARCTAN: return arctan(x); 
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

complex ASTUnaryNode::plus(complex x) const
{
   return m_child->evaluate(x);
}

complex ASTUnaryNode::minus(complex x) const
{
   return -m_child->evaluate(x);
}

complex ASTUnaryNode::sqrt(complex x) const
{
   auto val = std::sqrt(m_child->evaluate(x));
   return std::sqrt(m_child->evaluate(x));
}

complex ASTUnaryNode::exp(complex x) const
{
   return std::exp(m_child->evaluate(x));
}

complex ASTUnaryNode::ln(complex x) const
{
   return std::log(m_child->evaluate(x));
}

complex ASTUnaryNode::log(complex x) const
{
   return std::log10(m_child->evaluate(x));
}

complex ASTUnaryNode::sin(complex x) const
{
   return std::sin(m_child->evaluate(x));
}
complex ASTUnaryNode::cos(complex x) const
{
   return std::cos(m_child->evaluate(x));
}
complex ASTUnaryNode::tan(complex x) const
{
   return std::tan(m_child->evaluate(x));
}
complex ASTUnaryNode::arcsin(complex x) const
{
   return std::asin(m_child->evaluate(x));
}
complex ASTUnaryNode::arccos(complex x) const
{
   return std::acos(m_child->evaluate(x));
}
complex ASTUnaryNode::arctan(complex x) const
{
   return std::atan(m_child->evaluate(x));
}
