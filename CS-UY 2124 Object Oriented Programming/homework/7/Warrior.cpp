#include<iostream>
#include<string>
#include "Warrior.h"
#include "Noble.h"
using namespace std;
namespace WarriorCraft

{
// warrior class
Warrior:: Warrior (const string& name, double strength)
: name(name), strength(strength) {}

const string& Warrior:: getName() const { return name; }
double Warrior::getStrength() const { return strength; }
bool Warrior::isHired() const{ return status;}
bool Warrior::getLive() const { return (strength != 0); }


void Warrior::changeStatus(){ // default value as false
    status = !status;
}

void Warrior::changeStrength( double strengthRatio){
    if (strengthRatio == 0){
         strength = 0;
    }
    else {
    strength *= (1- strengthRatio) ;}
}
void Warrior::setHisNoble (Noble* newNoble) {
   hisNoble = newNoble;
}

bool Warrior::runaway(){
    if (hisNoble->getLive() == false || getLive() == false
         || hisNoble == nullptr){
        cout << name
            << " is unable to run away. " << endl;
        return false;
    } else {
        size_t warIndex = hisNoble->getHiredWarInd(name);
        string nobleName = hisNoble->getName();
        if (hisNoble->removeWarrior(warIndex)){
            cout << name << " flees in terror, abandoning his lord, "
            << nobleName << endl;
            return true;
        } else {
            cout << name
            << " is unable to run away. " << endl;
            return false;
        }
    }
}

ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << rhs.name << ": " << rhs.strength;
    return os;
}
}