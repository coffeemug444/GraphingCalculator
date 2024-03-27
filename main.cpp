#include <iostream>
#include "Token.hpp"


int main()
{
   std::string input;

   std::cout << "Calc > ";
   std::getline(std::cin, input);

   auto tokens = Token::tokenise(input);

   for (auto token : tokens)
   {
      std::cout << token.getValue();
   }

   std::cout << '\n';
}
