//C++ battleship
//학번 : 20171635, 이름 : 손건

#pragma once
#include <iostream>
#include <vector>

const int KMAP_SIZE = 8;
using Position = std::pair<int, int>;
Position operator+(const Position& , const Position&);
Position operator-(const Position& , const Position&);
std::ostream& operator<<(std::ostream&, const Position &);

using ShipPoses = std::vector<Position>;

enum class AttackResult : char {
  NONDETER = 0,
  HIT = 'H',
  MISS = 'M',
  DESTROY = 'D',
};

enum class ShipType : char{
  AIRCRAFT = 'A',
  BATTLESHIP = 'B',
  CRUISER = 'C',
  DESTROYER = 'D',
};
