#pragma once

#include "ASTNode.hpp"
#include "Token.hpp"

class ASTNumberNode : public ASTNode
{
public:
   explicit ASTNumberNode(double value);
   ASTNumberNode();
   double evaluate(double x) const override;
private:
   TokenType m_type;
   double m_value;
};
