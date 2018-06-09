#include "./RandTraceAttacker.h"

const Position RandomTraceAttacker::kPos_up(-1, 0);
const Position RandomTraceAttacker::kPos_right(0, 1);
const Position RandomTraceAttacker::kPos_down(1, 0);
const Position RandomTraceAttacker::kPos_left(0, -1);

RandomTraceAttacker::RandomTraceAttacker() 
  : RandomAttacker(), m_state(States::STATE_RAND), 
  m_traceMode(false), m_tracePos(-1, -1) {}

  RandomTraceAttacker::~RandomTraceAttacker() {}

  void RandomTraceAttacker::SetDestroy() {
    Position direction, pos = m_LastPos;
    if(m_state == States::STATE_UP) direction = kPos_down;
    else if(m_state == States::STATE_DOWN) direction = kPos_up;
    else if(m_state == States::STATE_RIGHT) direction = kPos_left;
    else if(m_state == States::STATE_LEFT) direction = kPos_right;

    for(int i = 0; i < m_DshipSize; ++i) {
      int y = pos.first, x = pos.second;
      m_HitMap[y][x] = AttackResult::DESTROY;
      pos = pos + direction;
    }
  }

  void RandomTraceAttacker::HandleState() {
    switch(m_state) {
      case States::STATE_RAND:
        if(m_AttackResult == AttackResult::MISS) {
          m_state = States::STATE_RAND;
        } else if (m_AttackResult == AttackResult::HIT) {
          m_state = States::STATE_UP;
        }else if(m_AttackResult == AttackResult::DESTROY) {
          m_traceMode = false;
          m_state = States::STATE_RAND;
        } 
        break;
      case States::STATE_UP:
        if(m_AttackResult == AttackResult::MISS) {
          m_traceMode = true;
          m_state = States::STATE_DOWN;
        } else if (m_AttackResult == AttackResult::HIT) {
          m_traceMode = false;
          m_verticalSt.push(m_LastPos);
          m_state = States::STATE_UP;
        }else if(m_AttackResult == AttackResult::DESTROY) {
          m_traceMode = false;
          //clear buf because destroy
          std::stack<Position> buf;
          m_verticalSt.swap(buf);
          m_state = States::STATE_RAND;
        } 
        break;
      case States::STATE_DOWN:
        if(m_AttackResult == AttackResult::MISS) {
          m_traceMode = true;
          m_state = States::STATE_RIGHT;
        } else if (m_AttackResult == AttackResult::HIT) {
          m_traceMode = false;
          m_verticalSt.push(m_LastPos);
          m_state = States::STATE_DOWN;
        }else if(m_AttackResult == AttackResult::DESTROY) {
          m_traceMode = false;
          //clear buf because destroy
          std::stack<Position> buf;
          m_verticalSt.swap(buf);
          m_state = States::STATE_RAND;
        } 
        break;
      case States::STATE_RIGHT:
        if(m_AttackResult == AttackResult::MISS) {
          m_traceMode = true;
          m_state = States::STATE_LEFT;
        } else if (m_AttackResult == AttackResult::HIT) {
          m_traceMode = false;
          m_state = States::STATE_RIGHT;
        }else if(m_AttackResult == AttackResult::DESTROY) {
          m_traceMode = false;
          if(!m_verticalSt.empty()) {
            m_LastPos = m_verticalSt.top();
            m_tracePos = m_LastPos;
            m_verticalSt.pop();
            m_state = States::STATE_RIGHT;
          }else {
            m_state = States::STATE_RAND;
          }
        } 
        break;
      case States::STATE_LEFT:
        if(m_AttackResult == AttackResult::MISS) {
          m_traceMode = false;
          m_state = States::STATE_RAND;
        } else if (m_AttackResult == AttackResult::HIT) {
          m_traceMode = false;
          m_state = States::STATE_LEFT;
        }else if(m_AttackResult == AttackResult::DESTROY) {
          m_traceMode = false;
          if(!m_verticalSt.empty()) {
            m_LastPos = m_verticalSt.top();
            m_tracePos = m_LastPos;
            m_verticalSt.pop();
            m_state = States::STATE_RIGHT;
          }else {
            m_state = States::STATE_RAND;
          }
        } 
        break;
    }
  }

Position RandomTraceAttacker::GetAttackPosition() {
  if(m_AttackResult == AttackResult::DESTROY) SetDestroy();
  Position base, ret;
  for(;;) {
    HandleState();

    if(m_traceMode) base = m_tracePos;
    else  base = m_LastPos;

    switch(m_state) {
      case States::STATE_RAND:
        ret = this->RandomAttacker::GenRandPosition(true);
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
