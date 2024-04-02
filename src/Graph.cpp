#include "Graph.hpp"

Graph::Graph(double width, double height)
:WIDTH{width}
,HEIGHT{height}
,m_center{0,0}
,m_last_mouse_pos{0,0}
,m_mouse_down{false}
,m_pixels_per_unit{40.0}
,m_axes{sf::Lines, 4}
,m_background_y_grid{sf::Lines}
,m_background_x_grid{sf::Lines}
,m_real_line{sf::LineStrip, 0}
,m_imag_line{sf::LineStrip, 0}
,m_point_pairs{}
,m_leftmost_x{0.f}
,m_rightmost_x{0.f}
{
   resetAxes();
}

void Graph::resize(double width, double height)
{
   WIDTH = width;
   HEIGHT = height;

   resetAxes();
   if (m_ast) recalculatePoints();
}

void Graph::mouseScroll(float delta)
{
   float diff = std::pow(1.1, delta);
   m_pixels_per_unit *= diff;
   resetAxes();
   recalculatePoints();
}

void Graph::mouseDown(const sf::Vector2f& pos)
{
   m_mouse_down = true;
   m_last_mouse_pos = pos;
}

void Graph::mouseUp(const sf::Vector2f& pos)
{
   m_mouse_down = false;
   m_last_mouse_pos = pos;
}

void Graph::mouseMoved(const sf::Vector2f& pos)
{
   if (not m_mouse_down) return;
   sf::Vector2f diff = pos - m_last_mouse_pos;

   auto last_center_screen_pos = graphCoordToScreenspace(m_center);
   m_center = screenspaceCoordToGraph(last_center_screen_pos - sf::Vector2f{diff.x, diff.y});

   for (size_t i = 0 ; i < m_real_line.getVertexCount(); i++)
   {
      m_real_line[i].position += diff;
   }
   for (size_t i = 0 ; i < m_imag_line.getVertexCount(); i++)
   {
      m_imag_line[i].position += diff;
   }

   if (m_ast)
   {
      if (screenspaceCoordToGraph({0,0}).x <= m_leftmost_x)
      {
         addLeftHalfScreen();
      }

      if (screenspaceCoordToGraph({static_cast<float>(WIDTH),0}).x >= m_rightmost_x)
      {
         addRightHalfScreen();
      }
   }

   m_last_mouse_pos = pos;
   resetAxes();
}

void Graph::setAST(std::shared_ptr<ASTNode> ast)
{
   m_ast = ast;
   recalculatePoints();
}

void Graph::setEquation(std::string_view str)
{
   try 
   {
      m_ast = AST::createTree(str);
      recalculatePoints();
   }
   catch (const NotATokenException& e) {}
   catch (const TokenExpectedException& e) {}
   catch (const UnexpectedTokenException& e) {}
}

void Graph::recalculatePoints()
{
   m_point_pairs.clear();

   if (not m_ast) return;

   // build points over 1 screen width to the left and right
   for (int screen_x = -WIDTH; screen_x <= 2*WIDTH; screen_x++)
   {
      for (int i = 0; i < POINTS_PER_PIXEL; i++)
      {
         double fraction = i / POINTS_PER_PIXEL;

         double x = screenspaceCoordToGraph({static_cast<float>(screen_x + fraction), 0.f}).x;
         complex y = m_ast->evaluate(x);
         m_point_pairs.push_back({x,y});
      }
   }

   m_leftmost_x = screenspaceCoordToGraph({-static_cast<float>(WIDTH), 0.f}).x;
   m_rightmost_x = screenspaceCoordToGraph({2*static_cast<float>(WIDTH), 0.f}).x;

   rebuildLines();
}

void Graph::addLeftHalfScreen()
{
   float x = m_leftmost_x;
   float diff = 1.f/(m_pixels_per_unit*POINTS_PER_PIXEL);

   for (int pixel = 1; pixel <= POINTS_PER_PIXEL*WIDTH/2; pixel++)
   {
      x -= diff;

      complex y = m_ast->evaluate(x);
      m_point_pairs.push_front({x,y});
   }

   m_leftmost_x = x;

   rebuildLines();
}

void Graph::addRightHalfScreen()
{
   float x = m_rightmost_x;
   float diff = 1.f/(m_pixels_per_unit*POINTS_PER_PIXEL);

   for (int pixel = 1; pixel <= POINTS_PER_PIXEL*WIDTH/2; pixel++)
   {
      x += diff;

      complex y = m_ast->evaluate(x + diff);
      m_point_pairs.push_back({x,y});
   }

   m_rightmost_x = x;

   rebuildLines();
}

void Graph::rebuildLines()
{
   m_real_line.resize(m_point_pairs.size());
   m_imag_line.resize(m_point_pairs.size());

   for (size_t p = 0; p < m_point_pairs.size(); p++)
   {
      float x = m_point_pairs.at(p).first;
      float y_r = m_point_pairs.at(p).second.real();
      float y_i = m_point_pairs.at(p).second.imag();
      
      m_real_line[p] = sf::Vertex{graphCoordToScreenspace({x,y_r}), sf::Color::White};
      m_imag_line[p] = sf::Vertex{graphCoordToScreenspace({x,y_i}), sf::Color::Red};
   }
}

void Graph::resetAxes()
{
   m_background_y_grid.resize(2*static_cast<int>(WIDTH * 0.07));
   m_background_x_grid.resize(2*static_cast<int>(HEIGHT * 0.07));

   auto zero_zero = graphCoordToScreenspace(sf::Vector2f{0.f,0.f});

   m_axes[0] = sf::Vertex{sf::Vector2f{0, zero_zero.y}, GREY};
   m_axes[1] = sf::Vertex{sf::Vector2f{static_cast<float>(WIDTH), zero_zero.y}, GREY};
   
   m_axes[2] = sf::Vertex{sf::Vector2f{zero_zero.x, 0}, GREY};
   m_axes[3] = sf::Vertex{sf::Vector2f{zero_zero.x, static_cast<float>(HEIGHT)}, GREY};

   float scale = m_pixels_per_unit;
   while (scale < 20) scale *= 5;
   while (scale > 100) scale /= 5;

   float x_gridline_first = std::fmod(zero_zero.y - HEIGHT/2.f, scale) + HEIGHT/2.f;
   int num_x_gridlines = m_background_x_grid.getVertexCount() / 2;
   int num_neg_x_gridlines = num_x_gridlines / 2;
   for (int i = 0; i < num_x_gridlines; i++)
   {
      float offset = (i-num_neg_x_gridlines)*scale;
      m_background_x_grid[2*i] = sf::Vertex{sf::Vector2f{0, x_gridline_first + offset}, DARKGREY};
      m_background_x_grid[2*i+1] = sf::Vertex{sf::Vector2f{static_cast<float>(WIDTH), x_gridline_first + offset}, DARKGREY};
   }

   float y_gridline_spacing = scale;
   float y_gridline_first = std::fmod(zero_zero.x - WIDTH/2.f, y_gridline_spacing) + WIDTH/2.f;
   int num_y_gridlines = m_background_y_grid.getVertexCount() / 2;
   int num_neg_y_gridlines = num_y_gridlines / 2;
   for (int i = 0; i < num_y_gridlines; i++)
   {
      float offset = (i-num_neg_y_gridlines)*y_gridline_spacing;
      m_background_y_grid[2*i] = sf::Vertex{sf::Vector2f{y_gridline_first + offset, 0}, DARKGREY};
      m_background_y_grid[2*i+1] = sf::Vertex{sf::Vector2f{y_gridline_first + offset, static_cast<float>(HEIGHT)}, DARKGREY};
   }
   
}

sf::Vector2f Graph::graphCoordToScreenspace(sf::Vector2f coord) const
{
   coord -= m_center;
   coord *= static_cast<float>(m_pixels_per_unit);
   coord.y *= -1;
   coord += sf::Vector2f{static_cast<float>(WIDTH/2), static_cast<float>(HEIGHT/2)};
   return coord;
}
sf::Vector2f Graph::screenspaceCoordToGraph(sf::Vector2f coord) const
{
   coord -= sf::Vector2f{static_cast<float>(WIDTH/2), static_cast<float>(HEIGHT/2)};
   coord.y *= -1;
   coord /= static_cast<float>(m_pixels_per_unit);
   coord += m_center;
   return coord;
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates) const
{
   target.draw(m_background_x_grid);
   target.draw(m_background_y_grid);
   target.draw(m_axes);

   target.draw(m_real_line);
   target.draw(m_imag_line);
}
