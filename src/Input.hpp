#pragma once

#include <SFML/Graphics.hpp>

#include "Graph.hpp"

class Input : public sf::Drawable
{
public:
   Input(float width, float height, float y_offset, Graph& graph);

   void inputChar(char c);
   void inputBackspace();
   void inputDelete();
   void inputLeft();
   void inputRight();
   void inputHome();
   void inputEnd();

   void resize(float width, float height, float y_offset);

   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
   float WIDTH;
   float HEIGHT;
   float Y_OFFSET;

   Graph& m_graph;

   void setCursorPos(int pos);
   void updateStr();

   sf::Text m_input_label;

   std::string m_str;
   int m_cursor_pos;

   sf::Text m_text;
   sf::RectangleShape m_background;

   sf::Vector2f m_cursor_base_screenpos;
   const float m_char_width;
   sf::RectangleShape m_cursor;
};
