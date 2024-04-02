#include "Input.hpp"

#include "Resources.hpp"




Input::Input(float width, float height, float y_offset, Graph& graph)
:WIDTH{width}
,HEIGHT{height}
,Y_OFFSET{y_offset}
,m_graph{graph}
,m_input_label{"y = ", RS::font}
,m_str{""}
,m_cursor_pos{0}
,m_text{m_str, RS::font}
,m_background{{WIDTH, HEIGHT}}
,m_cursor_base_screenpos{0.f, 0.f}
,m_char_width{16.f}
,m_cursor{{1.f, 26.f}}
{
   m_background.setPosition({0, Y_OFFSET});
   m_background.setFillColor(sf::Color::Black);

   m_input_label.setPosition({0, Y_OFFSET});
   m_text.setPosition({m_input_label.getGlobalBounds().width, Y_OFFSET});

   m_cursor.setPosition({m_input_label.getGlobalBounds().width - 2.f, Y_OFFSET + 9.f});
   m_cursor_base_screenpos = m_cursor.getPosition();

   m_cursor.setFillColor(sf::Color::White);
}

void Input::resize(float width, float height, float y_offset)
{
   WIDTH = width;
   HEIGHT = height;
   Y_OFFSET = y_offset;

   m_background.setPosition({0, Y_OFFSET});
   m_background.setSize({WIDTH, HEIGHT});

   m_input_label.setPosition({0, Y_OFFSET});
   m_text.setPosition({m_input_label.getGlobalBounds().width, Y_OFFSET});

   m_cursor.setPosition({m_input_label.getGlobalBounds().width - 2.f, Y_OFFSET + 9.f});
   m_cursor_base_screenpos = m_cursor.getPosition();
   
   setCursorPos(m_cursor_pos);
}

void Input::inputChar(char c)
{
   m_str.insert(m_str.begin() + m_cursor_pos, c);
   inputRight();

   updateStr();
}

void Input::inputBackspace()
{
   if (m_cursor_pos == 0) return;
   m_str.erase(m_cursor_pos - 1, 1);
   inputLeft();

   updateStr();
}

void Input::inputDelete()
{
   if (m_cursor_pos >= static_cast<int>(m_str.size())) return;
   m_str.erase(m_cursor_pos, 1);

   updateStr();
}

void Input::setCursorPos(int pos)
{
   m_cursor_pos = pos;
   auto screen_pos = m_cursor_base_screenpos;
   screen_pos.x += m_cursor_pos * m_char_width;

   m_cursor.setPosition(screen_pos);
}

void Input::inputLeft()
{
   setCursorPos(std::max(0, m_cursor_pos - 1));
}

void Input::inputRight()
{
   setCursorPos(std::min(static_cast<int>(m_str.size()), m_cursor_pos + 1));
}

void Input::inputHome()
{
   setCursorPos(0);
}

void Input::inputEnd()
{
   setCursorPos(static_cast<int>(m_str.size()));
}

void Input::updateStr()
{
   m_text.setString(m_str);

   m_graph.setEquation(m_str);
}

void Input::draw(sf::RenderTarget& target, sf::RenderStates) const
{
   target.draw(m_background);
   target.draw(m_input_label);
   target.draw(m_text);
   target.draw(m_cursor);
}