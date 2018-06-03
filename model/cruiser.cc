#include "./cruiser.h"

Cruiser::Cruiser() : Ship() {
  m_Hp = 3; m_Size = 3;
  m_poses.reserve(3);
  m_Type = ShipType::CRUISER;
  m_name = "Cruiser";
}

Cruiser::~Cruiser() {}
