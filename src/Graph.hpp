#pragma once

#include <SFML/Graphics.hpp>
#include "AST.hpp"

class Graph : public sf::Drawable
{
public:
   Graph(double width, double height);

   void mouseScroll(float delta);

   void mouseDown(const sf::Vector2f& pos);
   void mouseUp(const sf::Vector2f& pos);

   void mouseMoved(const sf::Vector2f& pos);

   // void setAST(std::shared_ptr<AST> ast);

   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
   void resetAxes();

   const sf::Color GREY{0x7f7f7fff};
   const sf::Color DARKGREY{0x3f3f3fff};

   const double WIDTH;
   const double HEIGHT;

   std::shared_ptr<AST> m_ast;

   sf::Vector2f m_center;
   sf::Vector2f m_last_mouse_pos;
   bool m_mouse_down;
   double m_scale;

   sf::VertexArray m_axes;
   sf::VertexArray m_background_y_grid;
   sf::VertexArray m_background_x_grid;

};

