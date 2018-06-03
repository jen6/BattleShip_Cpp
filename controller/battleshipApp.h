#pragma once

class Service;
class BattleShipMap;
class StatePane;
class InputPane;

class BattleShipApp {
  private:
    Service* m_service;
    BattleShipMap *m_defenceMap, *m_attackMap;
    StatePane* m_state;
    InputPane* m_input;

    void Render();
  public:
    BattleShipApp();
    ~BattleShipApp();

    void Init();
    void Play();
    void End();
};
