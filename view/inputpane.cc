//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./inputpane.h"

InputPane::InputPane(int x, int y, int width, int height) 
  : Pane(x, y, width, height) {
    mvwprintw(m_pWindow, 0, 3, "< INPUT >");
}

InputPane::~InputPane() {}

void InputPane::Draw() {
  wclear(m_pWindow);
  box(m_pWindow, 0, 0);
  mvwprintw(m_pWindow, 0, 3, "< INPUT >");
  wattron(m_pWindow, COLOR_PAIR(3));
  mvwprintw(m_pWindow, 1, 2, "Input Position...(ex A 3)");
  mvwprintw(m_pWindow, 2, 2, "Input : ");
  mvwprintw(m_pWindow, 3, 2, m_status.c_str());
  wattroff(m_pWindow, COLOR_PAIR(3));
  wmove(m_pWindow, 2, 10);
  
  wrefresh(m_pWindow);
}

Position InputPane::GetInput() {
  char buf[3] = {0, };
  flushinp();
  for(int i = 0; i < 2; ++i) buf[i] = mvwgetch(m_pWindow, 2, 10+i);
  Position pos;
  pos.first = buf[0]-'A';
  pos.second = buf[1]-'1';
  return pos;
}

void InputPane::Update(const Position& pos, AttackResult res, std::string name="") {
  m_status = "";
  if(res == AttackResult::HIT) {
    m_status += pos.first + 'A';
    m_status += pos.second + '1';
    m_status += ": HIT";
  } else if(res == AttackResult::MISS) {
    m_status += pos.first + 'A';
    m_status += pos.second + '1';
    m_status += ": MISS";
  } else if(res == AttackResult::DESTROY) {
    m_status += name;
    m_status += " : DESTROYED";
  }else {
    m_status = "Game Clear!";
  }
}

void InputPane::GameEnd(std::string str) {
  if(str == "")
    m_status = "Game End";
  else
    m_status = str + " : average turn";
}
