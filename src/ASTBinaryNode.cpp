#include "ASTBinaryNode.hpp"
#include <cmath>

ASTBinaryNode::ASTBinaryNode(TokenType binary_operator, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right)
   :m_binary_operator{binary_operator}
   ,m_left{left}
   ,m_right{right}
{
}

double ASTBinaryNode::evaluate(double x) const
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

double ASTBinaryNode::plus(double x) const
{
   return m_left->evaluate(x) + m_right->evaluate(x);
}

double ASTBinaryNode::minus(double x) const
{
   return m_left->evaluate(x) - m_right->evaluate(x);
}

double ASTBinaryNode::multiply(double x) const
{
   return m_left->evaluate(x) * m_right->evaluate(x);
}

double ASTBinaryNode::divide(double x) const
{
   return m_left->evaluate(x) / m_right->evaluate(x);
}

double ASTBinaryNode::pow(double x) const
{
   return std::pow(m_left->evaluate(x), m_right->evaluate(x));
}
