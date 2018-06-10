#include "./defenser.h"
#include "../CommonDef.h"
#include <chrono>
#include <random>

Defenser::Defenser() {}
Defenser::~Defenser() {}

void Defenser::SetShipPosition(const std::vector<PShip>& shipes) {
  char ship_map[KMAP_SIZE][KMAP_SIZE] = {{0, }, };

  int n = 0;
  for(PShip ship : shipes) {
    int ship_sz = ship->GetSize();
    ShipPoses sposes; 
    sposes.reserve(ship_sz);
    
    int cur_y = 0, cur_x = n++;
    for(int i = 0; i < ship_sz; ++i) {
      sposes.push_back(std::make_pair(cur_y, cur_x));
      ship_map[cur_y][cur_x] = 1;
      ++cur_y;
    }
    ship->SetPositions(sposes);
  }
}


