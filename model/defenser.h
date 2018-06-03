#pragma once
#include "../CommonDef.h"
#include "./ship.h"
#include <vector>

class Defenser {
  public:
    Defenser();
    ~Defenser();

    void SetShipPosition(std::vector<PShip>& );
};
