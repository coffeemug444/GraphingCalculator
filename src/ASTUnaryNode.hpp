#pragma once

#include <memory>
#include "ASTNode.hpp"
#include "Token.hpp"

class ASTUnaryNode : public ASTNode
{
public:
   explicit ASTUnaryNode(TokenType unary_operator, std::shared_ptr<ASTNode> child);

   complex evaluate(complex x) const override;
private:
   complex step(complex x) const;

   TokenType m_unary_operator;
   std::shared_ptr<ASTNode> m_child;
};
