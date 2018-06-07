#include "./RandAttacker.h"
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
  int y, x;
  for(;;){
    y = (*m_RandGenerator)() % KMAP_SIZE;
    if(!chess_board) { 
      x = (*m_RandGenerator)() % KMAP_SIZE;
      if(m_HitMap[y][x] == AttackResult::NONDETER) 
        break;
    } else {
      int base = y % 2;
      x = (*m_RandGenerator)() % (KMAP_SIZE / 2);
      x *= 2;
      x += base;
      if(m_HitMap[y][x] == AttackResult::NONDETER 
          || m_HitMap[y][x] == AttackResult::HIT) 
        break;
    }
  }
  return std::make_pair(y, x);
}

Position RandomAttacker::GetAttackPosition() {
  return GenRandPosition(false);
}
