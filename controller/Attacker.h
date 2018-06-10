//C++ battleship
//학번 : 20171635, 이름 : 손건

#pragma once
#include "../CommonDef.h"
#include <vector>

class Attacker {
  protected:
    AttackResult  m_HitMap[KMAP_SIZE][KMAP_SIZE];
    Position m_LastPos;
    AttackResult m_AttackResult;
    std::vector<int> m_shiplengths;
    int m_DshipSize;
    
    void HandleState();
  public:
    Attacker(std::vector<int> );
    virtual ~Attacker();
    virtual Position GetAttackPosition() = 0;
    void SetResult(const Position&, AttackResult, int = -1);
};
