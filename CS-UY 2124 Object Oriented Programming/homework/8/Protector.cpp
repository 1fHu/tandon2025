#include<iostream>
#include<string>
#include "Protector.h"
#include "Noble.h"
using namespace std;
namespace WarriorCraft
{
Protector:: Protector (const string& name, double strength)
: name(name), strength(strength), lordPtr(nullptr) {}

Lord* Protector::getLord () const{
    return lordPtr;
}

double Protector::getStrength() const {
    return strength;
}

const string& Protector::getName() const{
    return name; 
} 

void Protector::setLord (Lord* newLord) {
    lordPtr = newLord; 
}

void Protector::changeStrength( double strengthRatio){
    if (strengthRatio == 0){
        strength = 0;
   }
   else {
   strength *= (1- strengthRatio) ;
    }
}

ostream& operator<<(ostream& os, const Protector& rhs) {
    os << rhs.name << " has strength " << rhs.strength;
    return os;
}

void Wizard::defend() const {
    if (getStrength() > 0 && getLord() != nullptr) {
        cout << "POOF!" << endl;
    }
}

void Archer::defend() const  {
    if (getStrength() > 0 && getLord() != nullptr) {
        cout << "TWANG!  " << getName()
     << " says: Take that in the name of my lord, "
     << getLord()->getName() << endl;
    }
}
void Swordsman::defend() const {
    if (getStrength() > 0 && getLord() != nullptr) {
        cout << "CLANG!  " << getName()
     << " says: Take that in the name of my lord, "
     << getLord()->getName() << endl;
    }
}

void Protector::runaway() {
    if (lordPtr != nullptr) {
        cout << name << " flees in terror, abandoning his lord, "
             << lordPtr->getName() << endl;

        // Ask the lord to remove this protector by name
        lordPtr->removeProtectorByName(name);

        // Unlink from the lord
        lordPtr = nullptr;
    }
}}