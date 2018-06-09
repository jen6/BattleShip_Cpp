#include "./controller/battleshipApp.h"
#include "unistd.h"

int main() {
  BattleShipApp app;
  for(;;){
    app.Init();
    app.Play();
    app.End();
  }
}
