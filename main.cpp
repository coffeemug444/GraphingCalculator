#include <iostream>
#include <memory>
#include <span>
#include <stack>
#include "Token.hpp"
#include "ASTNode.hpp"
#include "ASTNumberNode.hpp"
#include "ASTUnaryNode.hpp"
#include "ASTBinaryNode.hpp"
#include <complex>

std::vector<Token> parseTokens(std::span<Token> tokens)
{
   std::vector<Token> output;
   std::stack<Token> stack;

   for (Token& token : tokens)
   {
      if (token.isNumber()) 
      {
         output.push_back(token);
         continue;
      }
      if (token.getType() == LPAREN)
      {
         stack.push(token);
         continue;
      }
      if (token.getType() == RPAREN)
      {
         while (not stack.empty() and stack.top().getType() != LPAREN)
         {
            output.push_back(stack.top());
            stack.pop();
         }
         stack.pop(); // Discard LPAREN
         continue;
      }
      
      while (not stack.empty() and token.isBinaryOperator() and token.getPrecedence() <= stack.top().getPrecedence())
      {
         output.push_back(stack.top());
         stack.pop();
      }
      stack.push(token);
   }

   while (not stack.empty())
   {
      output.push_back(stack.top());
      stack.pop();
   }

   return output;
}

std::shared_ptr<ASTNode> createTree(std::vector<Token>& parsed)
{
   const Token& token = parsed.back();
   parsed.pop_back();

   if (token.isNumber()) return std::make_shared<ASTNumberNode>(std::stod(token.getValue()));

   if (token.isUnaryOperator())
   {
      std::shared_ptr<ASTNode> child = createTree(parsed);
      return std::make_shared<ASTUnaryNode>(token.getType(), child);
   }

   // must be a binary operator
   std::shared_ptr<ASTNode> right = createTree(parsed);
   std::shared_ptr<ASTNode> left = createTree(parsed);
   return std::make_shared<ASTBinaryNode>(token.getType(), left, right);
}

int main()
{
   std::string input;

   std::cout << "Calc > ";
   std::getline(std::cin, input);

   auto tokens = Token::tokenise(input);
   auto parsed = parseTokens(tokens);
   auto tree = createTree(parsed);

   std::cout << tree->evaluate();

   
std::cout << '\n';
}
