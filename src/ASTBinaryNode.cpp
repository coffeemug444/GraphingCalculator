#include "ASTBinaryNode.hpp"
#include <cmath>

ASTBinaryNode::ASTBinaryNode(TokenType binary_operator, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right)
   :m_binary_operator{binary_operator}
   ,m_left{left}
   ,m_right{right}
{
}

complex ASTBinaryNode::evaluate(complex x) const
{
   switch (m_binary_operator)
   {
   case PLUS: return plus(x);
   case MINUS: return minus(x);
   case MULTIPLY: return multiply(x);
   case DIVIDE: return divide(x);
   case POWER: return pow(x);
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
      break;
   }
   return 0.0; // shouldn't happen
}

complex ASTBinaryNode::plus(complex x) const
{
   return m_left->evaluate(x) + m_right->evaluate(x);
}

complex ASTBinaryNode::minus(complex x) const
{
   return m_left->evaluate(x) - m_right->evaluate(x);
}

complex ASTBinaryNode::multiply(complex x) const
{
   return m_left->evaluate(x) * m_right->evaluate(x);
}

complex ASTBinaryNode::divide(complex x) const
{
   return m_left->evaluate(x) / m_right->evaluate(x);
}

complex ASTBinaryNode::pow(complex x) const
{
   return std::pow(m_left->evaluate(x), m_right->evaluate(x));
}
