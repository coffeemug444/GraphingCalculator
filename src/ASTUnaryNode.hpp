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
   complex plus(complex x) const;
   complex minus(complex x) const;
   complex sqrt(complex x) const;
   complex exp(complex x) const;
   complex ln(complex x) const;
   complex log(complex x) const;
   complex sin(complex x) const;
   complex cos(complex x) const;
   complex tan(complex x) const;
   complex arcsin(complex x) const;
   complex arccos(complex x) const;
   complex arctan(complex x) const;


   TokenType m_unary_operator;
   std::shared_ptr<ASTNode> m_child;
};
