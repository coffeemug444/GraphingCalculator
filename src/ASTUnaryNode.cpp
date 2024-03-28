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

double ASTUnaryNode::sin(double x) const
{
   return std::sin(m_child->evaluate(x));
}
double ASTUnaryNode::cos(double x) const
{
   return std::cos(m_child->evaluate(x));
}
double ASTUnaryNode::tan(double x) const
{
   return std::tan(m_child->evaluate(x));
}
double ASTUnaryNode::arcsin(double x) const
{
   return std::asin(m_child->evaluate(x));
}
double ASTUnaryNode::arccos(double x) const
{
   return std::acos(m_child->evaluate(x));
}
double ASTUnaryNode::arctan(double x) const
{
   return std::atan(m_child->evaluate(x));
}
