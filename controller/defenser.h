//C++ battleship
//학번 : 20171635, 이름 : 손건

#pragma once
#include "../CommonDef.h"
#include "../model/ship.h"
#include <vector>

class Defenser {
  public:
    Defenser();
    ~Defenser();

    void SetShipPosition(const std::vector<PShip>& );
};
