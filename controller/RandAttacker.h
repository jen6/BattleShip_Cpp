#pragma once
#include "./Attacker.h"
#include <random>

class RandomAttacker : public Attacker {
  protected:
    std::mt19937_64* m_RandGenerator = nullptr;
    Position GenRandPosition(bool);
  public:
    RandomAttacker();
    virtual ~RandomAttacker();
    virtual Position GetAttackPosition();
};

