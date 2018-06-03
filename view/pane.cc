#include "./pane.h"
Pane::Pane(int x, int y, int width, int height)
  : m_width(width), m_height(height), m_x(x), m_y(y) {
    m_pWindow = newwin(height, width, y, x);
    box(m_pWindow, 0, 0);
    wrefresh(m_pWindow);
  }

Pane::~Pane(){
  delwin(m_pWindow);
}

void Pane::Draw() {
  box(m_pWindow, 0, 0);
  touchwin(m_pWindow);
  wrefresh(m_pWindow);
}
