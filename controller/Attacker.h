#pragma once
#include "../CommonDef.h"

class Attacker {
  protected:
    AttackResult  m_HitMap[KMAP_SIZE][KMAP_SIZE];
    Position m_LastPos;
    AttackResult m_AttackResult;
    int m_DshipSize;;
    
    void HandleState();
  public:
    Attacker();
    virtual ~Attacker();
    virtual Position GetAttackPosition() = 0;
    void SetResult(const Position&, AttackResult, int = -1);
};
