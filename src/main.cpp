#include <iostream>
#include <SFML/Graphics.hpp>

#include "AST.hpp"
#include "Graph.hpp"


void pollEvents(sf::RenderWindow& window, Graph& graph) 
{
   sf::Event event;
   while (window.pollEvent(event))
   {
      switch (event.type)
      {
      case sf::Event::MouseButtonPressed:
      {
         if (event.mouseButton.button != sf::Mouse::Button::Left) break;
         // LMB pressed
         float x = static_cast<float>(event.mouseButton.x);
         float y = static_cast<float>(event.mouseButton.y);
         graph.mouseDown(sf::Vector2f{x,y});
         break;
      }
      case sf::Event::MouseButtonReleased:
      {
         if (event.mouseButton.button != sf::Mouse::Button::Left) break;
         // LMB released
         float x = static_cast<float>(event.mouseButton.x);
         float y = static_cast<float>(event.mouseButton.y);
         graph.mouseUp(sf::Vector2f{x,y});
         break;
      }
      case sf::Event::MouseMoved:
      {
         float x = static_cast<float>(event.mouseMove.x);
         float y = static_cast<float>(event.mouseMove.y);
         graph.mouseMoved(sf::Vector2f{x,y});
         break;
      }
      case sf::Event::MouseWheelScrolled:
      {
         graph.mouseScroll(event.mouseWheelScroll.delta);
         break;
      }
      case sf::Event::Closed:
         window.close();
         break;
      default:
         break;
      }
   }
}


int main()
{
   std::string input;
   std::cout << "Calc > ";
   std::getline(std::cin, input);
   auto tree = AST::createTree(input);

   const float WIDTH = 400.f;
   const float HEIGHT = 400.f;
   sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Graphing calculator", sf::Style::Close | sf::Style::Titlebar);
   window.setFramerateLimit(60);

   Graph graph(WIDTH, HEIGHT);
   graph.setAST(tree);


   while (window.isOpen())
   {
      pollEvents(window, graph);

      window.clear();
      window.draw(graph);
      // window.draw(real_line);
      // window.draw(imag_line);
      window.display();
   }

   std::cout << tree->evaluate(0);

   
std::cout << '\n';
}
