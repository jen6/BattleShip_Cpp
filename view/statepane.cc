#include "./statepane.h"
#include <string>

StatePane::StatePane(int x, int y, int width, int height) 
  : Pane(x, y, width, height), m_turn(0) {
    mvwprintw(m_pWindow, 0, 3, "< STATUS >");
}

StatePane::~StatePane() {}
void StatePane::Draw() {
  std::string turn_str = "Turn " + std::to_string(m_turn);
  mvwprintw(m_pWindow, 1, 2, turn_str.c_str());
  for(int i = 0; i < m_status.size(); ++i) {
    if(m_status[i] == 0) {
      wattron(m_pWindow, COLOR_PAIR(1)); 
      mvwprintw(m_pWindow, i+2, 2, m_shipes[i].c_str());
      wattroff(m_pWindow, COLOR_PAIR(1)); 
    } else {
      wattron(m_pWindow, COLOR_PAIR(4)); 
      mvwprintw(m_pWindow, i+2, 2, m_shipes[i].c_str());
      wattroff(m_pWindow, COLOR_PAIR(4)); 
    }
  }
  wrefresh(m_pWindow);
}

void StatePane::InsertShip(std::string name, char mark, int sz) {
  std::string buf = name;
  buf += " : ";
  for(int i = 0; i < sz; ++i) buf += mark;
  m_shipes.emplace_back(buf);
  m_status.push_back(0);
}

void StatePane::Update(int idx) {
  if(0<= idx && idx < m_status.size()) m_status[idx] = 1;
}

void StatePane::SetTurn(int turn) {
  m_turn = turn;
}
