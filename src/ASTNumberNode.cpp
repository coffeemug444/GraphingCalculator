#include "ASTNumberNode.hpp"

ASTNumberNode::ASTNumberNode(double value) 
   :m_value{value}
{
}

double ASTNumberNode::evaluate() const 
{
   return m_value;
}