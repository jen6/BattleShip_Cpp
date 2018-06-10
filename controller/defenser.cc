//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./defenser.h"
#include "../CommonDef.h"
#include <chrono>
#include <random>

Defenser::Defenser() {}
Defenser::~Defenser() {}

void Defenser::SetShipPosition(const std::vector<PShip>& shipes) {
  char ship_map[KMAP_SIZE][KMAP_SIZE] = {{0, }, };
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937_64 randGen(seed);

  for(PShip ship : shipes) {
    int ship_sz = ship->GetSize();
    ShipPoses sposes; 
    sposes.reserve(ship_sz);
    //0~7 이지만 배의 길이에 따라 0~(7-ship_sz)
    //n = (7-ship_sz) 일때 n까지 되려면 % (n+1)
    int rand_range = KMAP_SIZE - ship_sz + 1;
    int direction = randGen() % 2;
    int x, y, cur_y, cur_x;

    for(;;) {
      if(direction == 0) {
        //가로로 배치
        y = randGen() % KMAP_SIZE;
        x = randGen() % rand_range;
      } else {
        //세로로 배치
        y = randGen() % rand_range;
        x = randGen() % KMAP_SIZE;
      }
      cur_y = y; cur_x = x;
      bool flag = true;

      for(int i = 0; i < ship_sz; ++i) {
        if( ship_map[cur_y][cur_x] != 0 ) {
          flag = false;
          break;
        }
        if (direction == 0) ++cur_x;
        else ++cur_y;
      }

      if(flag) break;
    }
    
    cur_y = y; cur_x = x;
    for(int i = 0; i < ship_sz; ++i) {
      sposes.push_back(std::make_pair(cur_y, cur_x));
      ship_map[cur_y][cur_x] = 1;
      if (direction == 0) ++cur_x;
      else ++cur_y;
    }
    ship->SetPositions(sposes);
  }
}


