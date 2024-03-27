#pragma once

#include <memory>
#include "ASTNode.hpp"
#include "Token.hpp"

class ASTUnaryNode : public ASTNode
{
public:
   explicit ASTUnaryNode(Token unary_operator, std::shared_ptr<ASTNode> child);

   double evaluate() const override;
private:
   double plus() const;
   double minus() const;
   double sqrt() const;


   Token m_unary_operator;
   std::shared_ptr<ASTNode> m_child;
};
