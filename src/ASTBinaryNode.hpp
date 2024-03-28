#pragma once

#include <memory>
#include "ASTNode.hpp"
#include "Token.hpp"

class ASTBinaryNode : public ASTNode
{
public:
   explicit ASTBinaryNode(TokenType binary_operator, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right);

   double evaluate(double x) const override;
private:
   double plus(double x) const;
   double minus(double x) const;
   double multiply(double x) const;
   double divide(double x) const;
   double pow(double x) const;

   TokenType m_binary_operator;
   std::shared_ptr<ASTNode> m_left;
   std::shared_ptr<ASTNode> m_right;
};
