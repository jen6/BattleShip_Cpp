//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./battleshipApp.h"
#include "../model/service.h"
#include "../view/battleshipMap.h"
#include "../view/inputpane.h"
#include "../view/statepane.h"
#include "./defenser.h"
#include "./Attacker.h"
#include "./RandAttacker.h"
#include "./RandTraceAttacker.h"
#include "./HeatMapAttacker.h"

#include <ncurses.h>
#include <unistd.h>

BattleShipApp::BattleShipApp() {
  m_service = nullptr;
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
  m_service = new Service();
  m_service->Init();
  m_defenceMap = new BattleShipMap(4, 3, "defense");
  m_attackMap = new BattleShipMap(4, 15, "attack");
  m_state = new StatePane(30, 3, 30, 8);
  m_input = new InputPane(30, 13, 30, 6);
  std::vector<int> ship_sizes;
  auto shipes = m_service->GetShipes();
  for(auto ship : shipes) 
    ship_sizes.push_back(ship->GetSize());
  m_attacker = new HeatMapAttacker(ship_sizes);
//  m_attacker = new RandomTraceAttacker(ship_sizes);
  //m_attacker = new RandomAttacker();
  
  m_defenser = new Defenser();
}

void BattleShipApp::Render() {
  m_defenceMap->Draw();
  m_attackMap->Draw();
  m_state->Draw();
  m_input->Draw();
}

void BattleShipApp::Play() {
  auto shipes = m_service->GetShipes();
  m_defenser->SetShipPosition(shipes);

  for(auto ship : shipes) {
    m_defenceMap->SetShip(ship->GetType(), ship->GetPositions());
    m_state->InsertShip(ship->GetName(), static_cast<char>(ship->GetType()), ship->GetSize());
  }
  Render();
  while(!m_service->IsFinish()) {
    refresh();
    //auto pos = m_input->GetInput();
    auto pos = m_attacker->GetAttackPosition();
    auto result = m_service->Attack(pos);
    auto destroy = m_service->GetDestroyedShip();

    if(destroy){
      m_attacker->SetResult(pos, result, destroy->GetSize());
      m_input->Update(pos, result, destroy->GetName());

      int idx;
      for(idx = 0; idx < shipes.size(); ++idx) 
        if (shipes[idx] == destroy) break;
      m_state->Update(idx);
    }
    else {
      m_attacker->SetResult(pos, result);
      m_input->Update(pos, result, "");
    }

    m_state->SetTurn(m_service->GetTurn());
    m_attackMap->Update(pos, result);
    Render();
    usleep(500000);
  }
  m_input->GameEnd();
  Render();
  getch();
}

void BattleShipApp::Play(int play_size) {
  int turn_sum = 0;
  for(int play_cnt = 0; play_cnt < play_size; ++play_cnt) {
    Clear();
    Init();
    m_service->Init();
    auto shipes = m_service->GetShipes();
    m_defenser->SetShipPosition(shipes);

    for(auto ship : shipes) {
      m_defenceMap->SetShip(ship->GetType(), ship->GetPositions());
      m_state->InsertShip(ship->GetName(), static_cast<char>(ship->GetType()), ship->GetSize());
    }
    Render();
    while(!m_service->IsFinish()) {
      refresh();
      //auto pos = m_input->GetInput();
      auto pos = m_attacker->GetAttackPosition();
      auto result = m_service->Attack(pos);
      auto destroy = m_service->GetDestroyedShip();

      if(destroy){
        m_attacker->SetResult(pos, result, destroy->GetSize());
        m_input->Update(pos, result, destroy->GetName());

        int idx;
        for(idx = 0; idx < shipes.size(); ++idx) 
          if (shipes[idx] == destroy) break;
        m_state->Update(idx);
      }
      else {
        m_attacker->SetResult(pos, result);
        m_input->Update(pos, result, "");
      }

      m_state->SetTurn(m_service->GetTurn());
      m_attackMap->Update(pos, result);
      Render();
//      usleep(5000);
    }
    turn_sum += m_service->GetTurn() - 1;
    m_input->GameEnd();
    Render();
  }
  std::string average_str = std::to_string(turn_sum / play_size);
  m_input->GameEnd(average_str);
  Render();
  getch();
  End();
}

void BattleShipApp::Clear() {
  if(m_service) {
    delete m_service;
    m_service = nullptr;
  }
  if(m_attacker) {
    delete m_attacker;
    m_attacker = nullptr;
  }
  if(m_defenser) {
    delete m_defenser;
    m_defenser = nullptr;
  }
  if(m_attackMap) {
    delete m_attackMap;
    m_attackMap = nullptr;
  }
  if(m_defenceMap) {
    delete m_defenceMap;
    m_defenceMap = nullptr;
  }
  if(m_state) {
    delete m_state;
    m_state = nullptr;
  }
  if(m_input) {
    delete m_input;
    m_input = nullptr;
  }
}

void BattleShipApp::End() {
  endwin();
  Clear();
}
