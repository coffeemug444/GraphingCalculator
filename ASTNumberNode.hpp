#pragma once

#include "ASTNode.hpp"

class ASTNumberNode : public ASTNode
{
public:
   explicit ASTNumberNode(double value);
   double evaluate() const override;
private:
   double m_value;
};
