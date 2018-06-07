#include "./Attacker.h"

Attacker::Attacker() {
  for(int i = 0; i < KMAP_SIZE; ++i) {
    for(int j = 0; j < KMAP_SIZE; ++j) {
      m_HitMap[i][j] = AttackResult::NONDETER;
    }
  }
}

Attacker::~Attacker() {}

void Attacker::SetResult(const Position& pos, AttackResult result) {
  m_LastPos = pos; m_AttackResult = result;
  int y = pos.first, x = pos.second;
  m_HitMap[y][x] = result;
}

