#pragma once
#include <SFML/Graphics.hpp>

class Resources;
using RS = Resources;

class Resources
{
public:
   static void init() { font.loadFromFile("resources/Anonymous Pro.ttf"); }
   inline static sf::Font font;
};
