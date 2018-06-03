#pragma once
#include "../CommonDef.h"
#include "./defenser.h"
#include "./ship.h"
#include <vector>

class Service {
  private:
    int m_Turn;
    int m_Allive;
    Defenser* m_defense;
    std::vector<PShip> m_shipes;
    PShip m_recentDestoy;
  public:
    Service();
    ~Service();

    void Init();
    void CleanUp();
    int GetTurn();
    const std::vector<PShip>& GetShipes();
    AttackResult Attack(const Position& );
    bool IsFinish();
    PShip GetDestroyedShip();
};
