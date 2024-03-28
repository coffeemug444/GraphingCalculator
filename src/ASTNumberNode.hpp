#pragma once

#include "ASTNode.hpp"
#include "Token.hpp"

class ASTNumberNode : public ASTNode
{
public:
   explicit ASTNumberNode(double value);
   ASTNumberNode();
   complex evaluate(complex x) const override;
private:
   TokenType m_type;
   double m_value;
};
