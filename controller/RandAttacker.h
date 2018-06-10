//C++ battleship
//학번 : 20171635, 이름 : 손건

#pragma once
#include "./Attacker.h"
#include <random>

class RandomAttacker : public Attacker {
  protected:
    std::mt19937_64* m_RandGenerator = nullptr;
    virtual Position GenRandPosition();
  public:
    RandomAttacker(std::vector<int> );
    virtual ~RandomAttacker();
    virtual Position GetAttackPosition();
};

