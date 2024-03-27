#include "ASTBinaryNode.hpp"
#include <cmath>

ASTBinaryNode::ASTBinaryNode(Token binary_operator, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right)
   :m_binary_operator{binary_operator}
   ,m_left{left}
   ,m_right{right}
{
}

double ASTBinaryNode::evaluate() const
{
   switch (m_binary_operator.getType())
   {
   case PLUS: return plus();
   case MINUS: return minus();
   case MULTIPLY: return multiply();
   case DIVIDE: return divide();
   case POWER: return pow();
   default:
      return 0.0; // shouldn't happen
   }
}

double ASTBinaryNode::plus() const
{
   return m_left->evaluate() + m_right->evaluate();
}

double ASTBinaryNode::minus() const
{
   return m_left->evaluate() - m_right->evaluate();
}

double ASTBinaryNode::multiply() const
{
   return m_left->evaluate() * m_right->evaluate();
}

double ASTBinaryNode::divide() const
{
   return m_left->evaluate() / m_right->evaluate();
}

double ASTBinaryNode::pow() const
{
   return std::pow(m_left->evaluate(), m_right->evaluate());
}
