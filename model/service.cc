#include "./service.h"
#include "./aircraft.h"
#include "./battleship.h"
#include "./cruiser.h"
#include "./destroyer.h"

Service::Service() : m_Turn(0), m_Allive(0), m_recentDestoy(nullptr){
}
Service::~Service() {
  this->CleanUp();
}

void Service::Init() {
  this->CleanUp();
  m_shipes.push_back(new Aircraft());
  m_shipes.push_back(new BattleShip());
  m_shipes.push_back(new Cruiser());
  m_shipes.push_back(new Destroyer());
  m_shipes.push_back(new Destroyer());
  m_Allive = m_shipes.size();
  m_Turn = 1;
}

void Service::CleanUp() {
  for(auto& ptr : m_shipes) {
    if(ptr) {
      delete ptr;
      ptr = nullptr;
    }
  }
  m_shipes.clear();
}

int Service::GetTurn() {
  return m_Turn++;
}

const std::vector<PShip>& Service::GetShipes() {
  return m_shipes;
}

AttackResult Service::Attack(const Position& pos) {
  AttackResult result = AttackResult::MISS;
  for(auto ship : m_shipes) {
    bool is_hit = ship->HitCheck(pos);
    if(is_hit) {
      if(ship->GetHp() == 0) {
        m_Allive -= 1;
        m_recentDestoy = ship;
        result = AttackResult::DESTROY;
      } else {
        m_recentDestoy = nullptr;
        result = AttackResult::HIT;
      }
      break;
    } else {
      m_recentDestoy = nullptr;
    }
  }
  return result;
}

bool Service::IsFinish() {
  return (m_Allive == 0 ? true : false);
}

PShip Service::GetDestroyedShip(){
  return m_recentDestoy;
}
