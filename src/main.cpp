#include <iostream>
#include <SFML/Graphics.hpp>

#include "AST.hpp"


void pollEvents(sf::RenderWindow& window) 
{
   sf::Event event;
   while (window.pollEvent(event))
   {
      switch (event.type)
      {
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

   const float WIDTH = 200.f;
   const float HEIGHT = 200.f;
   sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Graphing calculator");

   const int POINTS = 195; //  arbitrary

   sf::VertexArray line{sf::LinesStrip, POINTS};
   for (int p = 0; p < POINTS; p++)
   {
      float screen_x = p*(WIDTH / POINTS);

      // screen goes from x {-5 to 5}
      float x = (screen_x / WIDTH) * 10.f - 5.f;

      // screen goes from y {-5 to 5}
      float y = (HEIGHT/2) - 10*tree->evaluate(x); // y is flipped in graphics

      line[p] = sf::Vertex{sf::Vector2f{screen_x, y}, sf::Color::White};
   }
   

   while (window.isOpen())
   {
      pollEvents(window);

      window.clear();
      window.draw(line);
      window.display();
   }

   std::cout << tree->evaluate(0);

   
std::cout << '\n';
}
