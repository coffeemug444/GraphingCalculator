#pragma once

#include "ASTNode.hpp"
#include "Token.hpp"

class ASTNumberNode : public ASTNode
{
public:
   ASTNumberNode(complex value, TokenType type);
   ASTNumberNode();
   complex evaluate(complex x) const override;
private:
   TokenType m_type;
   complex m_value;
};
