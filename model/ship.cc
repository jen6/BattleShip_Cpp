#include "ship.h"

Ship::Ship() {}
Ship::~Ship() {}

std::string Ship::GetName() const {
  return m_name;
}

ShipPoses Ship::GetPositions() {
  return m_poses;
}

ShipType Ship::GetType() {
  return m_Type;
}
int Ship::GetSize() {
  return m_Size;
}

int Ship::GetHp() {
  return m_Hp;
}

bool Ship::HitCheck(const Position& pos) {
  for(auto iter = m_poses.begin(); iter != m_poses.end(); ++iter) {
    if(*iter != pos) continue;
    m_Hp -= 1;
    m_poses.erase(iter);
    return true;
  }
  return false;
}

void Ship::SetPositions(const ShipPoses& shipposes) {
  m_poses = shipposes;
}
