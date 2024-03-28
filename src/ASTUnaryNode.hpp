#pragma once

#include <memory>
#include "ASTNode.hpp"
#include "Token.hpp"

class ASTUnaryNode : public ASTNode
{
public:
   explicit ASTUnaryNode(TokenType unary_operator, std::shared_ptr<ASTNode> child);

   double evaluate(double x) const override;
private:
   double plus(double x) const;
   double minus(double x) const;
   double sqrt(double x) const;
   double exp(double x) const;
   double ln(double x) const;
   double log(double x) const;
   double sin(double x) const;
   double cos(double x) const;
   double tan(double x) const;
   double arcsin(double x) const;
   double arccos(double x) const;
   double arctan(double x) const;


   TokenType m_unary_operator;
   std::shared_ptr<ASTNode> m_child;
};
