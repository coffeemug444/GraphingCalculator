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
{
   resetAxes();
}

void Graph::mouseScroll(float delta)
{
   float diff = std::pow(1.1, delta);
   if (delta < 0)
   {
      m_scale /= diff;
   }
   else
   {
      m_scale *= diff;
   }
   resetAxes();
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
   m_center += static_cast<float>(m_scale/HEIGHT)*diff;

   m_last_mouse_pos = pos;
   resetAxes();
}

void Graph::resetAxes()
{
   float x_axis_pos = HEIGHT*(m_center.y/m_scale + 0.5f);

   m_axes[0] = sf::Vertex{sf::Vector2f{0, x_axis_pos}, GREY};
   m_axes[1] = sf::Vertex{sf::Vector2f{static_cast<float>(WIDTH), x_axis_pos}, GREY};
   
   float y_axis_pos = WIDTH*(m_center.x/m_scale + 0.5f);
   m_axes[2] = sf::Vertex{sf::Vector2f{y_axis_pos, 0}, GREY};
   m_axes[3] = sf::Vertex{sf::Vector2f{y_axis_pos, static_cast<float>(HEIGHT)}, GREY};

   
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates) const
{
   target.draw(m_axes);
}