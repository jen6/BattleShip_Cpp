#pragma once
#include "./RandAttacker.h"
#include "./state_def.h"
#include <random>

class RandomTraceAttacker : public RandomAttacker {
  protected:
    States m_state;
    bool m_traceMode;
    Position m_tracePos;

    static const Position kPos_up;
    static const Position kPos_right;
    static const Position kPos_down;
    static const Position kPos_left;

    void HandleState();
  public:
    RandomTraceAttacker();
    virtual ~RandomTraceAttacker();
    virtual Position GetAttackPosition();
};
