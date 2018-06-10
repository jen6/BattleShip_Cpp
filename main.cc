//C++ battleship
//학번 : 20171635, 이름 : 손건

#include "./controller/battleshipApp.h"
#include "unistd.h"

int main() {
  BattleShipApp app;
  for(;;){
   app.Init();
   app.Play();
   app.End();
   //app.Play(10);
  }
}
