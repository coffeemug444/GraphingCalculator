#include <iostream>
#include <SFML/Graphics.hpp>

#include "Resources.hpp"
#include "AST.hpp"
#include "Graph.hpp"
#include "Input.hpp"


void pollEvents(sf::RenderWindow& window, Graph& graph, Input& input) 
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
      case sf::Event::TextEntered:
      {
         if (std::isprint(event.text.unicode))
         {
            input.inputChar(static_cast<char>(event.text.unicode));
         }
         break;
      }
      case sf::Event::KeyPressed:
      {
         switch(event.key.code)
         {
            case sf::Keyboard::Key::BackSpace:
               input.inputBackspace();
               break;
            case sf::Keyboard::Key::Delete:
               input.inputDelete();
               break;
            case sf::Keyboard::Key::Left:
               input.inputLeft();
               break;
            case sf::Keyboard::Key::Right:
               input.inputRight();
               break;
            default: break;
         }
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
   RS::init();

   const float WIDTH = 400.f;
   const float GRAPH_HEIGHT = 400.f;
   const float INPUT_HEIGHT = 50.f;
   const float WINDOW_HEIGHT = GRAPH_HEIGHT + INPUT_HEIGHT;
   sf::RenderWindow window(sf::VideoMode(WIDTH, WINDOW_HEIGHT), "Graphing calculator", sf::Style::Close | sf::Style::Titlebar);
   window.setFramerateLimit(60);

   Graph graph(WIDTH, GRAPH_HEIGHT);
   Input input(WIDTH, INPUT_HEIGHT, GRAPH_HEIGHT, graph);

   while (window.isOpen())
   {
      pollEvents(window, graph, input);

      window.clear();
      window.draw(graph);
      window.draw(input);
      window.display();
   }
}
