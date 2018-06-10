//C++ battleship
//학번 : 20171635, 이름 : 손건

#pragma once

class Service;
class BattleShipMap;
class StatePane;
class InputPane;
class Attacker;
class Defenser;

class BattleShipApp {
  private:
    Service* m_service;
    Attacker* m_attacker;
    Defenser* m_defenser;
    BattleShipMap *m_defenceMap, *m_attackMap;
    StatePane* m_state;
    InputPane* m_input;

    void Render();
    void Clear();
  public:
    BattleShipApp();
    ~BattleShipApp();

    void Init();
    void Play();
    void Play(int);
    void End();
};
