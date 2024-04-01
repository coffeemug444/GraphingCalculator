#include "Graph.hpp"

Graph::Graph(double width, double height)
:WIDTH{width}
,HEIGHT{height}
,m_center{0,0}
,m_last_mouse_pos{0,0}
,m_mouse_down{false}
,m_scale{10.0}
,m_axes{sf::Lines, 4}
,m_background_y_grid{sf::Lines, 30}
,m_background_x_grid{sf::Lines, 30}
,m_real_line{sf::LineStrip, 0}
,m_imag_line{sf::LineStrip, 0}
,m_point_pairs{}
,m_leftmost_x{0.f}
,m_rightmost_x{0.f}
{
   resetAxes();
}

void Graph::mouseScroll(float delta)
{
   float diff = std::pow(1.1, -delta);
   m_scale *= diff;
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
   m_center.y += static_cast<float>(m_scale/HEIGHT)*diff.y;
   m_center.x += static_cast<float>(m_scale/WIDTH)*diff.x;

   for (size_t i = 0 ; i < m_real_line.getVertexCount(); i++)
   {
      m_real_line[i].position += diff;
   }
   for (size_t i = 0 ; i < m_imag_line.getVertexCount(); i++)
   {
      m_imag_line[i].position += diff;
   }

   if (screenspaceCoordToGraph({0,0}).x <= m_leftmost_x)
   {
      addLeftHalfScreen();
   }

   if (screenspaceCoordToGraph({static_cast<float>(WIDTH),0}).x >= m_rightmost_x)
   {
      addRightHalfScreen();
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
   float diff = static_cast<float>(m_scale/(POINTS_PER_PIXEL*WIDTH));

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

   float diff = static_cast<float>(m_scale/(POINTS_PER_PIXEL*WIDTH));

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
   float x_axis_pos = HEIGHT*(m_center.y/m_scale + 0.5f);

   m_axes[0] = sf::Vertex{sf::Vector2f{0, x_axis_pos}, GREY};
   m_axes[1] = sf::Vertex{sf::Vector2f{static_cast<float>(WIDTH), x_axis_pos}, GREY};
   
   float y_axis_pos = WIDTH*(m_center.x/m_scale + 0.5f);
   m_axes[2] = sf::Vertex{sf::Vector2f{y_axis_pos, 0}, GREY};
   m_axes[3] = sf::Vertex{sf::Vector2f{y_axis_pos, static_cast<float>(HEIGHT)}, GREY};

   float scale = m_scale;
   while (scale < 5) scale *= 5;
   while (scale > 15) scale /= 5;


   float x_gridline_spacing = HEIGHT/scale;
   float x_gridline_first = std::fmod(x_axis_pos - HEIGHT/2.f, x_gridline_spacing) + HEIGHT/2.f;
   for (int i = -7; i <= 7; i++)
   {
      m_background_x_grid[2*(i+7)] = sf::Vertex{sf::Vector2f{0, x_gridline_first + i*x_gridline_spacing}, DARKGREY};
      m_background_x_grid[2*(i+7)+1] = sf::Vertex{sf::Vector2f{static_cast<float>(WIDTH), x_gridline_first + i*x_gridline_spacing}, DARKGREY};
   }

   float y_gridline_spacing = WIDTH/scale;
   float y_gridline_first = std::fmod(y_axis_pos - WIDTH/2.f, y_gridline_spacing) + WIDTH/2.f;
   for (int i = -7; i <= 7; i++)
   {
      m_background_y_grid[2*(i+7)] = sf::Vertex{sf::Vector2f{y_gridline_first + i*x_gridline_spacing, 0}, DARKGREY};
      m_background_y_grid[2*(i+7)+1] = sf::Vertex{sf::Vector2f{y_gridline_first + i*x_gridline_spacing, static_cast<float>(HEIGHT)}, DARKGREY};
   }
   
}

sf::Vector2f Graph::graphCoordToScreenspace(sf::Vector2f coord) const
{
   float screen_x = WIDTH * ((coord.x + m_center.x) / m_scale + 0.5);
   float screen_y = HEIGHT * ((-coord.y + m_center.y) / m_scale + 0.5);
   return sf::Vector2f{screen_x, screen_y};
}

sf::Vector2f Graph::screenspaceCoordToGraph(sf::Vector2f coord) const
{
   float graph_x = (coord.x/WIDTH - 0.5f)*m_scale - m_center.x;
   float graph_y = (0.5f - coord.y/HEIGHT)*m_scale + m_center.y;
   return sf::Vector2f{graph_x, graph_y};
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates) const
{
   target.draw(m_background_x_grid);
   target.draw(m_background_y_grid);
   target.draw(m_axes);

   target.draw(m_real_line);
   target.draw(m_imag_line);
}
