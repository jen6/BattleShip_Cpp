//C++ battleship
//학번 : 20171635, 이름 : 손건
#include "./HeatMapAttacker.h"
#include <algorithm>

Position HeatMapAttacker::GenRandPosition() {
  int cntMap[KMAP_SIZE][KMAP_SIZE] = {{0,}, };
  int ship_sz = *std::max_element(m_shiplengths.begin(), m_shiplengths.end());

  for(int i = 0; i < 50000; ++i) {
    int rand_range = KMAP_SIZE - ship_sz + 1;
    int x, y, cur_y, cur_x;
    int direction;
    for(;;) {
      direction = (*m_RandGenerator)() % 2;
      if(direction == 0) {
        //가로로 배치
        y = (*m_RandGenerator)() % KMAP_SIZE;
        x = (*m_RandGenerator)() % rand_range;
      } else {
        //세로로 배치
        y = (*m_RandGenerator)() % rand_range;
        x = (*m_RandGenerator)() % KMAP_SIZE;
      }
      cur_y = y; cur_x = x;
      bool flag = true;

      for(int i = 0; i < ship_sz; ++i) {
        if( m_HitMap[cur_y][cur_x] == AttackResult::DESTROY ||
            m_HitMap[cur_y][cur_x] == AttackResult::MISS) {
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
      cntMap[cur_y][cur_x] += 1;
      if (direction == 0) ++cur_x;
      else ++cur_y;
    }
  }

  int b_y = 0, b_x = 0;
  for(int i = 0; i < KMAP_SIZE; ++i) {
    for(int j = 0; j < KMAP_SIZE; ++j) {
      if(cntMap[i][j] > cntMap[b_y][b_x]) {
        b_y = i; b_x = j;
      }
    }
  }

  return std::make_pair(b_y, b_x);
}

HeatMapAttacker::HeatMapAttacker(std::vector<int> shipes) : RandomTraceAttacker(shipes) {}
HeatMapAttacker::~HeatMapAttacker() {}

Position HeatMapAttacker::GetAttackPosition() {
  if(m_AttackResult == AttackResult::DESTROY) SetDestroy();
  Position base, ret;
  for(;;) {
    HandleState();

    if(m_traceMode) base = m_tracePos;
    else  base = m_LastPos;

    switch(m_state) {
      case States::STATE_RAND:
        ret = GenRandPosition();
        m_tracePos = ret;
        break;
      case States::STATE_UP:
        ret = base + kPos_up;
        break;
      case States::STATE_RIGHT:
        ret = base + kPos_right;
        break;
      case States::STATE_DOWN:
        ret = base + kPos_down;
        break;
      case States::STATE_LEFT:
        ret = base + kPos_left;
        break;
    }

    int y = ret.first, x = ret.second;
    if(!(0 <= y && y < KMAP_SIZE) || !(0 <= x && x < KMAP_SIZE)){
      //for passing this direction
      m_AttackResult = AttackResult::MISS;
      continue;
    }

    if(m_HitMap[y][x] == AttackResult::MISS || m_HitMap[y][x] == AttackResult::DESTROY) {
      m_AttackResult = AttackResult::MISS;
      continue;
    } else if(m_HitMap[y][x] == AttackResult::HIT) {
      m_AttackResult = AttackResult::HIT;
      m_LastPos = ret;
      continue;
    }
    break;
  }
  return ret;
}
