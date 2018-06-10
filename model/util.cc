//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "../CommonDef.h"

Position operator+(const Position& a, const Position& b) {
  return std::make_pair(a.first + b.first, a.second + b.second);
}
Position operator-(const Position& a, const Position& b) {
  return std::make_pair(a.first - b.first, a.second - b.second);
}
std::ostream& operator<<(std::ostream& os, const Position& pos){
  os << '(' <<  pos.first
    <<", " << pos.second << ')';
  return os;
}
