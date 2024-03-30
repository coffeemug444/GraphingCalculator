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

   const int POINTS = 3*WIDTH; //  arbitrary

   const int X_RANGE = 10;
   const int Y_RANGE = 10;

   sf::VertexArray real_line{sf::LinesStrip, POINTS};
   sf::VertexArray imag_line{sf::LinesStrip, POINTS};
   for (int p = 0; p < POINTS; p++)
   {
      float screen_x = p*(WIDTH / POINTS);

      // screen goes from x {-5 to 5}
      float x = (p / static_cast<float>(POINTS)) * X_RANGE - 5.f;

      // screen goes from y {-5 to 5}
      complex y = complex(HEIGHT/2, HEIGHT/2) - complex(HEIGHT/Y_RANGE)*tree->evaluate(x); // y is flipped in graphics

      real_line[p] = sf::Vertex{sf::Vector2f{screen_x, static_cast<float>(y.real())}, sf::Color::White};
      imag_line[p] = sf::Vertex{sf::Vector2f{screen_x, static_cast<float>(y.imag())}, sf::Color::Red};
   };

   Graph graph(WIDTH, HEIGHT);
   

   while (window.isOpen())
   {
      pollEvents(window, graph);

      window.clear();
      window.draw(graph);
      window.draw(real_line);
      window.draw(imag_line);
      window.display();
   }

   std::cout << tree->evaluate(0);

   
std::cout << '\n';
}
