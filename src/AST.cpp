#include "AST.hpp"

#include <stack>
#include <sstream>
#include <numbers>

#include "ASTNumberNode.hpp"
#include "ASTUnaryNode.hpp"
#include "ASTBinaryNode.hpp"


std::shared_ptr<ASTNode> AST::createTree(std::string_view str)
{
   auto tokens = tokenise(str);
   auto parsed = parse(tokens);
   auto tree = createTree(parsed);

   return tree;
}

std::vector<Token> AST::parse(std::span<Token> tokens)
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
         if (stack.empty())
         {
            throw UnexpectedTokenException("Expected LPAREN to match RPAREN");
         }
         stack.pop(); // Discard LPAREN
         continue;
      }
      
      while (not stack.empty() and stack.top().isOperator() and token.isBinaryOperator() and token.getPrecedence() <= stack.top().getPrecedence())
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



std::shared_ptr<ASTNode> AST::createTree(std::vector<Token>& parsed)
{
   if (parsed.empty())
   {
      throw TokenExpectedException("Expected more tokens");
   }
   const Token& token = parsed.back();
   parsed.pop_back();

   if (token.isNumber()) 
   {
      if (token.getType() == X)
         return std::make_shared<ASTNumberNode>();
      else if (token.getType() == NUMBER)
         return std::make_shared<ASTNumberNode>(std::stod(token.getValue()), NUMBER);
      // constant
      complex val = [token]() -> complex {
         auto str = token.getValue();
         if (str == "i")   return {0,1};
         if (str == "e")   return {std::numbers::e,0};
         if (str == "pi")  return {std::numbers::pi,0};
         if (str == "phi") return {std::numbers::phi,0};
         return 0; // shouldn't happen
      }();
      return std::make_shared<ASTNumberNode>(val, CONSTANT);
   }
   

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



std::vector<Token> AST::tokenise(std::string_view str)
{
   std::vector<Token> tokens;

   unsigned pos = 0;
   bool unary_possible = true;

   // check if it's a 1 char operator
   while (pos < str.size())
   {
      switch (str.at(pos))
      {
      case ' ':
         ++pos;
         continue;
      case '+':
      {
         TokenType type = unary_possible ? UNARY_PLUS : PLUS;
         unary_possible = true;
         tokens.push_back(Token{type, "+"});
         ++pos;
         continue;
      }
      case '-':
      {
         TokenType type = unary_possible ? UNARY_MINUS : MINUS;
         unary_possible = true;
         tokens.push_back(Token{type, "-"});
         ++pos;
         continue;
      }
      case '*':
         unary_possible = true;
         tokens.push_back(Token{MULTIPLY, "*"});
         ++pos;
         continue;
      case '/':
         unary_possible = true;
         tokens.push_back(Token{DIVIDE, "*"});
         ++pos;
         continue;
      case '^':
         unary_possible = true;
         tokens.push_back(Token{POWER, "^"});
         ++pos;
         continue;
      case '(':
         if (not unary_possible) tokens.push_back(Token{MULTIPLY, "*"});
         unary_possible = true;
         tokens.push_back(Token{LPAREN, "("});
         ++pos;
         continue;
      case ')':
         unary_possible = false;
         tokens.push_back(Token{RPAREN, ")"});
         ++pos;
         continue;
      default:
         break;
      }

      // only unary operators or numbers remaining
      // add implicit '*' if required
      if (not unary_possible) tokens.push_back(Token{MULTIPLY, "*"});

      if (str.at(pos) == 'x')
      {
         unary_possible = false;
         tokens.push_back(Token{X, "x"});
         ++pos;
         continue;
      }

      bool found = false;

      for (auto [name, token] : {
         std::pair<std::string, TokenType>{"sqrt", SQRT},
         std::pair<std::string, TokenType>{"exp", EXP},
         std::pair<std::string, TokenType>{"ln", LN},
         std::pair<std::string, TokenType>{"log", LOG},
         std::pair<std::string, TokenType>{"sin", SIN},
         std::pair<std::string, TokenType>{"cos", COS},
         std::pair<std::string, TokenType>{"tan", TAN},
         std::pair<std::string, TokenType>{"arcsin", ARCSIN},
         std::pair<std::string, TokenType>{"arccos", ARCCOS},
         std::pair<std::string, TokenType>{"arctan", ARCTAN},
         std::pair<std::string, TokenType>{"step", STEP},
         std::pair<std::string, TokenType>{"abs", ABS},
      })
      {
         if (str.size() - pos >= name.size() && name == str.substr(pos, name.size()))
         {
            // found one!
            tokens.push_back(Token{token, name});
            pos += name.size();
            unary_possible = true;
            found = true;
            break;
         }
      }
      if (found) continue;

      for (std::string name : { "pi", "i", "e", "phi" })
      {
         if (str.size() - pos >= name.size() && name == str.substr(pos, name.size()))
         {
            // found one!
            tokens.push_back(Token{CONSTANT, name});
            pos += name.size();
            unary_possible = false;
            found = true;
            break;
         }
      }
      if (found) continue;


      // could still be a number, or invalid
      // check for number
      auto char_is_numeric = [](char c) {
         return (c >= '0' and c <= '9') or (c == '.');
      };
     
      int num_len = 0;
      while ((pos + num_len) < str.size() and char_is_numeric(str.at(pos + num_len)))
      {
         ++num_len;
      }

      if (num_len == 0)
      {
         // not a number and therefore invalid...
         std::stringstream ss;
         ss << "Found character '" << str.at(pos) << "' at position " << pos << " that could not be tokenised";
         throw NotATokenException(ss.str());
      }

      tokens.push_back(Token{NUMBER, std::string(str.substr(pos, num_len))});
      unary_possible = false;
      pos += num_len;
   }

   return tokens;
}


