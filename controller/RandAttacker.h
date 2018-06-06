#pragma once
#include "./Attacker.h"
#include <random>

class RandomAttacker : public Attacker {
  protected:
    std::mt19937_64* m_RandGenerator = nullptr;
    Position GenRandPosition();
  public:
    RandomAttacker();
    virtual ~RandomAttacker();
    virtual Position GetAttackPosition();
};

