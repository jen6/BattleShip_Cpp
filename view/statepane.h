#include "./pane.h"
#include <vector>
#include <string>

class StatePane : Pane {
  private:
    std::vector<std::string> m_shipes;
    std::vector<int> m_status;
    int m_turn;

  public:
    StatePane(int, int, int, int);
    ~StatePane();

    virtual void Draw();
    void InsertShip(std::string, char, int);
    void Update(int );
    void SetTurn(int );
};
