#include "./battleshipApp.h"
#include "../model/service.h"
#include "../view/battleshipMap.h"
#include "../view/inputpane.h"
#include "../view/statepane.h"
#include <ncurses.h>
#include <unistd.h>

BattleShipApp::BattleShipApp() {
  m_service = new Service();
  m_defenceMap = nullptr;
  m_attackMap =  nullptr;
  m_state =      nullptr;
  m_input =      nullptr;
}

BattleShipApp::~BattleShipApp() {
  if(m_service) delete m_service;
  if(m_defenceMap) delete m_defenceMap;
  if(m_attackMap) delete m_attackMap;
  if(m_state) delete m_state;
  if(m_input) delete m_input;
}

void BattleShipApp::Init() {
  initscr();
  start_color();
  cbreak();
  refresh();
  mvprintw(1, 1, "<<Battle Ship Game>>");

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  m_defenceMap = new BattleShipMap(4, 3, "defense");
  m_attackMap = new BattleShipMap(4, 15, "attack");
  m_state = new StatePane(30, 3, 30, 8);
  m_input = new InputPane(30, 13, 30, 6);

}

void BattleShipApp::Render() {
  m_defenceMap->Draw();
  m_attackMap->Draw();
  m_state->Draw();
  m_input->Draw();
}

void BattleShipApp::Play() {
  m_service->Init();
  auto shipes = m_service->GetShipes();
  for(auto ship : shipes) {
    m_defenceMap->SetShip(ship->GetType(), ship->GetPositions());
    m_state->InsertShip(ship->GetName(), static_cast<char>(ship->GetType()), ship->GetSize());
  }
  Render();
  while(!m_service->IsFinish()) {
    refresh();
    auto pos = m_input->GetInput();
    auto result = m_service->Attack(pos);
    auto destroy = m_service->GetDestroyedShip();
    if(destroy){
      m_input->Update(pos, result, destroy->GetName());
      int idx;
      for(idx = 0; idx < shipes.size(); ++idx) 
        if (shipes[idx] == destroy) break;
      m_state->Update(idx);
    }
    else
      m_input->Update(pos, result, "");
    m_state->SetTurn(m_service->GetTurn());
    m_attackMap->Update(pos, result);
    Render();
  }
  m_input->GameEnd();
  Render();
}

void BattleShipApp::End() {
  getch();
  endwin();
}
