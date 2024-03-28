#pragma once

#include <memory>
#include "ASTNode.hpp"
#include "Token.hpp"

class ASTUnaryNode : public ASTNode
{
public:
   explicit ASTUnaryNode(TokenType unary_operator, std::shared_ptr<ASTNode> child);

   double evaluate() const override;
private:
   double plus() const;
   double minus() const;
   double sqrt() const;
   double exp() const;
   double ln() const;
   double log() const;


   TokenType m_unary_operator;
   std::shared_ptr<ASTNode> m_child;
};
