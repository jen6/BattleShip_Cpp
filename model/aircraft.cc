//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./aircraft.h"

Aircraft::Aircraft() : Ship() {
  m_Hp = 5; m_Size = 5;
  m_poses.reserve(5);
  m_Type = ShipType::AIRCRAFT;
  m_name = "AirCraft";
}

Aircraft::~Aircraft() {}
