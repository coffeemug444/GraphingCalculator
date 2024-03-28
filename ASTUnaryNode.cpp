#include "ASTUnaryNode.hpp"
#include <cmath>

ASTUnaryNode::ASTUnaryNode(TokenType unary_operator, std::shared_ptr<ASTNode> child)
   :m_unary_operator{unary_operator}
   ,m_child{child}
{
}

double ASTUnaryNode::evaluate() const 
{
   switch (m_unary_operator)
   {
   case PLUS: return plus();
   case MINUS: return minus();
   case SQRT: return sqrt();
   case EXP: return exp();
   case LN: return ln();
   case LOG: return log();
   default:
      return 0.0; // shouldn't happen
   }
}

double ASTUnaryNode::plus() const
{
   return m_child->evaluate();
}

double ASTUnaryNode::minus() const
{
   return -m_child->evaluate();
}

double ASTUnaryNode::sqrt() const
{
   return std::sqrt(m_child->evaluate());
}

double ASTUnaryNode::exp() const
{
   return std::exp(m_child->evaluate());
}

double ASTUnaryNode::ln() const
{
   return std::log(m_child->evaluate());
}

double ASTUnaryNode::log() const
{
   return std::log10(m_child->evaluate());
}
