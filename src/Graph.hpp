#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include "AST.hpp"

class Graph : public sf::Drawable
{
public:
   Graph(double width, double height);

   void mouseScroll(float delta);

   void mouseDown(const sf::Vector2f& pos);
   void mouseUp(const sf::Vector2f& pos);

   void mouseMoved(const sf::Vector2f& pos);

   void setAST(std::shared_ptr<ASTNode> ast);
   void setEquation(std::string_view str);

   void resize(double width, double height);

   void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
   sf::Vector2f graphCoordToScreenspace(sf::Vector2f coord) const;
   sf::Vector2f screenspaceCoordToGraph(sf::Vector2f coord) const;

   void resetAxes();
   void recalculatePoints();
   void rebuildLines();
   void addLeftHalfScreen();
   void addRightHalfScreen();

   const sf::Color GREY{0x7f7f7fff};
   const sf::Color DARKGREY{0x3f3f3fff};

   double WIDTH;
   double HEIGHT;
   const static inline double POINTS_PER_PIXEL = 2;

   std::shared_ptr<ASTNode> m_ast;

   sf::Vector2f m_center;
   sf::Vector2f m_last_mouse_pos;
   bool m_mouse_down;
   double m_pixels_per_unit; // level of zoom into the graph. The higher this value the more zoomed in we are

   sf::VertexArray m_axes;
   sf::VertexArray m_background_y_grid;
   sf::VertexArray m_background_x_grid;
   sf::VertexArray m_real_line;
   sf::VertexArray m_imag_line;

   std::deque<std::pair<float,complex>> m_point_pairs;

   float m_leftmost_x;
   float m_rightmost_x;

};

