#pragma once

#include <memory>
#include "ASTNode.hpp"
#include "Token.hpp"

class ASTBinaryNode : public ASTNode
{
public:
   explicit ASTBinaryNode(TokenType binary_operator, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right);

   complex evaluate(complex x) const override;
private:
   complex plus(complex x) const;
   complex minus(complex x) const;
   complex multiply(complex x) const;
   complex divide(complex x) const;
   complex pow(complex x) const;

   TokenType m_binary_operator;
   std::shared_ptr<ASTNode> m_left;
   std::shared_ptr<ASTNode> m_right;
};
