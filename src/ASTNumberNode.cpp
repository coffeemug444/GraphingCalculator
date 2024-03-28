#include "ASTNumberNode.hpp"

ASTNumberNode::ASTNumberNode(double value) 
   :m_type{NUMBER}
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