#include "./battleship.h"

BattleShip::BattleShip() : Ship() {
  m_Hp = 4; m_Size = 4;
  m_poses.reserve(4);
  m_Type = ShipType::BATTLESHIP;
  m_name = "BattleShip";
}

BattleShip::~BattleShip() {}
