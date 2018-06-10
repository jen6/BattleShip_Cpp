//C++ battleship
//학번 : 20171635, 이름 : 손건

#pragma once
#include "./RandTraceAttacker.h"

class HeatMapAttacker : public RandomTraceAttacker {
  protected:
    Position GenRandPosition();
  public:
    HeatMapAttacker(std::vector<int> );
    ~HeatMapAttacker();
    Position GetAttackPosition();
};
