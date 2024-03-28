#include <iostream>
#include <memory>
#include <span>
#include <stack>
#include "Token.hpp"
#include "AST.hpp"
#include <complex>


int main()
{
   std::string input;

   std::cout << "Calc > ";
   std::getline(std::cin, input);

   auto tree = AST::createTree(input);

   std::cout << tree->evaluate(0);

   
std::cout << '\n';
}
