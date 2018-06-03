#pragma once
#include <ncurses.h>
class Pane{
  protected:
    int m_width, m_height;
    int m_x, m_y;
    WINDOW* m_pWindow;
  public:
    Pane(int, int, int, int);
    virtual ~Pane();
    
    virtual void Draw();
};
