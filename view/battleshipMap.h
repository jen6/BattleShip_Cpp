//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./pane.h"
#include "../CommonDef.h"

class BattleShipMap : public Pane {
  protected:
    char m_mapData[KMAP_SIZE][KMAP_SIZE];
    std::string m_mapName;
  public:
    BattleShipMap(int, int, std::string);
    ~BattleShipMap();

    virtual void Draw();
    void Update(const Position&, AttackResult);
    bool SetShip(ShipType, const ShipPoses& );
};
