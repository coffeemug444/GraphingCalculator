#include "ASTUnaryNode.hpp"
#include <cmath>

ASTUnaryNode::ASTUnaryNode(Token unary_operator, std::shared_ptr<ASTNode> child)
   :m_unary_operator{unary_operator}
   ,m_child{child}
{
}

double ASTUnaryNode::evaluate() const 
{
   switch (m_unary_operator.getType())
   {
   case PLUS: return plus();
   case MINUS: return minus();
   case SQRT: return sqrt();
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
