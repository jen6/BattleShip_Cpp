//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./battleshipMap.h"

BattleShipMap::BattleShipMap(int x, int y, std::string name) 
  : Pane(x, y, KMAP_SIZE+4, KMAP_SIZE+2), m_mapName(name) {
    for(int i = 0; i < KMAP_SIZE; ++i) {
      for(int j = 0; j < KMAP_SIZE; ++j) {
        m_mapData[i][j] = '0';
      }
    }

    for(int i = 0; i < KMAP_SIZE; ++i) {
      mvprintw(i + 1 + m_y, m_x - 1, "%c", 'A' + i);
      mvprintw(m_y + m_height, m_x + 2 + i, "%d", 1 + i);
    }

    mvwprintw(m_pWindow, 0, 3, m_mapName.c_str());
  }

BattleShipMap::~BattleShipMap() {}

void BattleShipMap::Draw() {
  for(int i = 0; i < KMAP_SIZE; ++i) {
    for(int j = 0; j < KMAP_SIZE; ++j) {
      if(m_mapData[i][j] == '0'){
        wattron(m_pWindow, COLOR_PAIR(2));
        mvwprintw(m_pWindow, i+1, j+2, "%c", m_mapData[i][j]);
        wattroff(m_pWindow, COLOR_PAIR(2));
      } else {
        wattron(m_pWindow, COLOR_PAIR(4));
        mvwprintw(m_pWindow, i+1, j+2, "%c", m_mapData[i][j]);
        wattroff(m_pWindow, COLOR_PAIR(4));
      }
    }
  }
  wrefresh(m_pWindow);
}

void BattleShipMap::Update(const Position& pos, AttackResult res) {
  int y = pos.first, x = pos.second;
  if(!(0 <= y && y < KMAP_SIZE) || !(0 <= x && x < KMAP_SIZE)){
    return;
  }
  if(m_mapData[y][x] != '0') return;
  if(res == AttackResult::DESTROY) res = AttackResult::HIT;
  m_mapData[y][x] = static_cast<char>(res);
}

bool BattleShipMap::SetShip(ShipType st, const ShipPoses& shipPos) {
  char shipMark = '0';
  switch(st) {
    case ShipType::AIRCRAFT :
      shipMark = 'A';
      break;
    case ShipType::BATTLESHIP :
      shipMark = 'B';
      break;
    case ShipType::CRUISER :
      shipMark = 'C';
      break;
    case ShipType::DESTROYER :
      shipMark = 'D';
      break;
    default:
      return false;
  }

  for(const auto& pos : shipPos) {
    int y = pos.first, x = pos.second;
    if(!(0 <= y && y < KMAP_SIZE) || !(0 <= x && x < KMAP_SIZE)){
      return false;
    }
    if(m_mapData[y][x] != '0') return false;
  }

  for(const auto& pos : shipPos) {
    int y = pos.first, x = pos.second;
    m_mapData[y][x] = shipMark;
  }
  return true;
}
