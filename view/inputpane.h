#include "./pane.h"
#include "../CommonDef.h"

class InputPane : public Pane {
  private:
    std::string m_status;
  public:
    InputPane(int, int, int, int);
    ~InputPane();

    virtual void Draw();
    Position GetInput();
    void Update(const Position&, AttackResult, std::string);
    void GameEnd();
};
