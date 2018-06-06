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
