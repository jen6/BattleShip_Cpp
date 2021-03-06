//C++ battleship
//학번 : 20171635, 이름 : 손건

#pragma once
#include "./RandAttacker.h"
#include "./state_def.h"
#include <random>
#include <stack>

class RandomTraceAttacker : public RandomAttacker {
  protected:
    States m_state;
    bool m_traceMode;
    Position m_tracePos;
    std::stack<Position> m_verticalSt;

    static const Position kPos_up;
    static const Position kPos_right;
    static const Position kPos_down;
    static const Position kPos_left;

    void SetDestroy();
    void HandleState();
    virtual Position GenRandPosition();
  public:
    RandomTraceAttacker(std::vector<int> );
    virtual ~RandomTraceAttacker();
    virtual Position GetAttackPosition();
};

