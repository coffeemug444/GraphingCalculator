#pragma once

#include <span>
#include <vector>
#include <string>
#include <memory>

#include "Token.hpp"
#include "ASTNode.hpp"

class AST
{
public:
   static std::vector<Token> tokenise(std::string_view str);
   static std::vector<Token> parse(std::span<Token> tokens);
   static std::shared_ptr<ASTNode> createTree(std::vector<Token>& parsed);

   static std::shared_ptr<ASTNode> createTree(std::string_view str);
};
