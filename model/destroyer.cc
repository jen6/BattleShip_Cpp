//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./destroyer.h"

Destroyer::Destroyer() : Ship() {
  m_Hp = 2; m_Size = 2;
  m_poses.reserve(2);
  m_Type = ShipType::DESTROYER;
  m_name = "Destroyer";
}

Destroyer::~Destroyer() {}
