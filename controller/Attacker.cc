//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./Attacker.h"

Attacker::Attacker(std::vector<int> shipes) 
  : m_AttackResult(AttackResult::MISS), m_shiplengths(shipes) {
  for(int i = 0; i < KMAP_SIZE; ++i) {
    for(int j = 0; j < KMAP_SIZE; ++j) {
      m_HitMap[i][j] = AttackResult::NONDETER;
    }
  }
}

Attacker::~Attacker() {}

void Attacker::SetResult(
    const Position& pos, AttackResult result, int destroyed_shipsz) {
  m_LastPos = pos; m_AttackResult = result;
  m_DshipSize = destroyed_shipsz;
  if(destroyed_shipsz != -1) {
    for(int& sz : m_shiplengths) {
      if(sz == destroyed_shipsz) {
        sz = 0;
        break;
      }
    }
  }

  int y = pos.first, x = pos.second;
  m_HitMap[y][x] = result;
}

