//C++ battleship
//학번 : 20171635, 이름 : 손건

#pragma once
#include <vector>
#include "../CommonDef.h"

class Ship {
  protected:
    int m_Hp, m_Size;
    ShipPoses m_poses;
    ShipType m_Type;
    std::string m_name;

  public:
    Ship();
    virtual ~Ship();

    std::string GetName() const;
    ShipPoses GetPositions();
    int GetSize();
    int GetHp();
    ShipType GetType();
    bool HitCheck(const Position&);
    void SetPositions(const ShipPoses&);
};

using PShip = Ship*;
