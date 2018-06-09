#include "./RandAttacker.h"
#include <vector>
#include <chrono>
#include <random>

RandomAttacker::RandomAttacker() : Attacker() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  m_RandGenerator = new std::mt19937_64(seed);
}

RandomAttacker::~RandomAttacker() {
  if(m_RandGenerator) delete m_RandGenerator;
}

Position RandomAttacker::GenRandPosition(bool chess_board=false) {
  std::vector<Position> possible_points;
  if(chess_board) {
    for(int y = 0; y < KMAP_SIZE; ++y) {
      int base = y % 2;
      for(int i = 0; i < KMAP_SIZE/2; ++i) {
        int x = i * 2 + base;
        if(m_HitMap[y][x] == AttackResult::NONDETER 
            || m_HitMap[y][x] == AttackResult::HIT) {
          possible_points.emplace_back(std::make_pair(y, x));
        }
      }
    }
    int idx = (*m_RandGenerator)() % possible_points.size();
    return possible_points[idx];
  }

  int y, x;
  for(;;){
    y = (*m_RandGenerator)() % KMAP_SIZE;
    x = (*m_RandGenerator)() % KMAP_SIZE;
    if(m_HitMap[y][x] == AttackResult::NONDETER) 
      break;
  }
  return std::make_pair(y, x);
}

Position RandomAttacker::GetAttackPosition() {
  return GenRandPosition(false);
}
