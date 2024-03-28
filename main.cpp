#include <iostream>
#include <memory>
#include <span>
#include <stack>
#include "Token.hpp"
#include "ASTNode.hpp"

std::vector<Token> createTree(std::span<Token> tokens)
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
      
      while (not stack.empty() and stack.top().isOperator() and token.getPrecedence() <= stack.top().getPrecedence())
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

int main()
{
   std::string input;

   std::cout << "Calc > ";
   std::getline(std::cin, input);

   auto tokens = Token::tokenise(input);
   auto ordered = createTree(tokens);

   for (auto token : ordered)
   {
      std::cout << token.getValue() << "(" << token.getType() << ") ";
   }

   std::cout << '\n';
}
