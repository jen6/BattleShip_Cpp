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

Position RandomAttacker::GenRandPosition() {
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
  return GenRandPosition();
}
