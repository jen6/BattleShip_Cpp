#include "./RandTraceAttacker.h"

const Position RandomTraceAttacker::kPos_up(-1, 0);
const Position RandomTraceAttacker::kPos_right(0, 1);
const Position RandomTraceAttacker::kPos_down(1, 0);
const Position RandomTraceAttacker::kPos_left(0, -1);

RandomTraceAttacker::RandomTraceAttacker() 
  : RandomAttacker(), m_state(States::STATE_RAND), 
  m_traceMode(false), m_tracePos(-1, -1) {}

  RandomTraceAttacker::~RandomTraceAttacker() {}

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
          m_state = States::STATE_UP;
        }else if(m_AttackResult == AttackResult::DESTROY) {
          m_traceMode = false;
          m_state = States::STATE_RAND;
        } 
        break;
      case States::STATE_DOWN:
        if(m_AttackResult == AttackResult::MISS) {
          m_traceMode = true;
          m_state = States::STATE_RIGHT;
        } else if (m_AttackResult == AttackResult::HIT) {
          m_traceMode = false;
          m_state = States::STATE_DOWN;
        }else if(m_AttackResult == AttackResult::DESTROY) {
          m_traceMode = false;
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
          m_state = States::STATE_RAND;
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
          m_state = States::STATE_RAND;
        } 
        break;
    }
  }

Position RandomTraceAttacker::GetAttackPosition() {
  HandleState();

  Position ret;
  switch(m_state) {
    case States::STATE_RAND:
      ret = this->RandomAttacker::GetAttackPosition();
      m_tracePos = ret;
      break;
    case States::STATE_UP:
      if(m_traceMode) m_LastPos = m_tracePos;
      ret = m_LastPos + kPos_up;
      break;
    case States::STATE_RIGHT:
      if(m_traceMode) m_LastPos = m_tracePos;
      ret = m_LastPos + kPos_right;
      break;
    case States::STATE_DOWN:
      if(m_traceMode) m_LastPos = m_tracePos;
      ret = m_LastPos + kPos_down;
      break;
    case States::STATE_LEFT:
      if(m_traceMode) m_LastPos = m_tracePos;
      ret = m_LastPos + kPos_left;
      break;
  }

  int y = ret.first, x = ret.second;
  if(!(0 <= y && y < KMAP_SIZE) || !(0 <= x && x < KMAP_SIZE)){
    //for passing this direction
    m_AttackResult = AttackResult::MISS;
    ret = GetAttackPosition();
  }

  if(m_HitMap[y][x] == AttackResult::MISS || m_HitMap[y][x] == AttackResult::DESTROY) {
    m_AttackResult = AttackResult::MISS;
    ret = GetAttackPosition();
  } else if(m_HitMap[y][x] == AttackResult::HIT) {
    m_AttackResult = AttackResult::HIT;
    m_LastPos = ret;
    ret = GetAttackPosition();
  }
  return ret;
}
