#pragma once

#include <memory>
#include "ASTNode.hpp"
#include "Token.hpp"

class ASTBinaryNode : public ASTNode
{
public:
   explicit ASTBinaryNode(TokenType binary_operator, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right);

   double evaluate() const override;
private:
   double plus() const;
   double minus() const;
   double multiply() const;
   double divide() const;
   double pow() const;

   TokenType m_binary_operator;
   std::shared_ptr<ASTNode> m_left;
   std::shared_ptr<ASTNode> m_right;
};
