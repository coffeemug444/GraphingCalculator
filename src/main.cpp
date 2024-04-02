#include <iostream>
#include <SFML/Graphics.hpp>

#include "Resources.hpp"
#include "AST.hpp"
#include "Graph.hpp"
#include "Input.hpp"

float WIDTH = 400.f;
float HEIGHT = 400.f;
const float INPUT_HEIGHT = 50.f;

void pollEvents(sf::RenderWindow& window, Graph& graph, Input& input) 
{
   sf::Event event;
   while (window.pollEvent(event))
   {
      switch (event.type)
      {
      case sf::Event::Resized:
      {
         WIDTH = static_cast<float>(window.getSize().x);
         HEIGHT = static_cast<float>(window.getSize().y) - INPUT_HEIGHT;

         window.setView(sf::View(sf::FloatRect{0.f,0.f,WIDTH, HEIGHT + INPUT_HEIGHT}));

         input.resize(WIDTH, INPUT_HEIGHT, HEIGHT);
         graph.resize(WIDTH, HEIGHT);

         break;
      }
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
            case sf::Keyboard::Key::Home:
               input.inputHome();
               break;
            case sf::Keyboard::Key::End:
               input.inputEnd();
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
   sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT + INPUT_HEIGHT), "Graphing calculator");
   window.setFramerateLimit(60);

   Graph graph(WIDTH, HEIGHT);
   Input input(WIDTH, INPUT_HEIGHT, HEIGHT, graph);

   while (window.isOpen())
   {
      pollEvents(window, graph, input);

      window.clear();
      window.draw(graph);
      window.draw(input);
      window.display();
   }
}
