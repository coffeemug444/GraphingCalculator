#include "ASTNumberNode.hpp"

ASTNumberNode::ASTNumberNode(complex value, TokenType type)
   :m_type{type}
   ,m_value{value}
{
}

ASTNumberNode::ASTNumberNode() 
   :m_type{X}
   ,m_value{0}
{
}

complex ASTNumberNode::evaluate(complex x) const 
{
   if (m_type == X) return x;
   return m_value;
}