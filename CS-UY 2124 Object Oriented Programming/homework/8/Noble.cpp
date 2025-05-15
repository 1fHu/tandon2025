#include<iostream>
#include<string>
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft

{

Noble::Noble(const string& name) : name(name), alive(true) {}

bool Noble :: getLive() const{
    return alive; 
}
const string&  Noble ::getName() const{
    return name;
}



void Noble::smallBattle(Noble& winner, Noble& loser,
     double winnerStr, double loserStr){

    if (loserStr != 0){
        // winnerStr never get 0 here
        double strengthRatio = (loserStr / winnerStr); 
        loser.changeStrength(0);
        loser.alive = false;
        winner.changeStrength(strengthRatio);

    } else { // loserStr == 0
        loser.alive = false;
        
    }
    

    cout << winner.name << " defeats " << loser.name << endl;
}


// working if strength is non-negative number
void  Noble ::battle(Noble& opponent){
    cout << name << " battles " << opponent.name << endl;
    defend();
    opponent.defend();

    double myArmyStrength = getStrength();
    double opponentStrength = opponent.getStrength();

    // six cases
    if (getLive() == false && opponent.getLive() == false){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    else if (getLive() == false)
    {
        cout << "He's dead " << opponent.name << endl;
    }
    else if (opponent.getLive() == false)
    {
        cout << "He's dead " << name << endl;
    }
    else if (myArmyStrength > opponentStrength)
    {
        smallBattle(*this, opponent, myArmyStrength, opponentStrength);

    }
    else if (myArmyStrength < opponentStrength)
    {
        smallBattle(opponent, *this, opponentStrength, myArmyStrength);

    }
    else { // equal strength 
        changeStrength(0);
        opponent.changeStrength(0);
        alive = false ;
        opponent.alive = false;
        cout << "Mutual Annihilation: " << name << " and " 
            << opponent.name << " die at each other's hands" << endl;
    }   
}





// ------- definition for class Lord -----
double Lord::getStrength() const {
    double totalStrength = 0;
    for (const Protector* each : allProt) {
        totalStrength += each->getStrength();
    }
    return totalStrength;
}

size_t Lord::getHiredProInd(const string& name) const{
    for (size_t i = 0; i < allProt.size(); ++i) {
        if (allProt[i]->getName() == name){ 
            return i;}
    }
    return allProt.size();
}

bool Lord::hires( Protector& freeProt){
    if (!getLive()|| freeProt.getLord() != nullptr ||
    freeProt.getStrength() == 0) {
        
        cout << getName()
            << " failed to hire " 
            << freeProt.getName() << endl;
        return false;
    }
    
    allProt.push_back(&freeProt);

    freeProt.setLord(this);
    return true;
}

bool Lord :: fires( Protector& hiredProt){

    size_t index = getHiredProInd(hiredProt.getName());

    if (!getLive() || hiredProt.getLord() == nullptr || 
    hiredProt.getStrength()  == 0) {
        cout << getName() << " failed to fire " 
            << hiredProt.getName() << endl;
        return false;
    }

    if (removeWarrior(index)){
        cout << hiredProt.getName() 
        << ", you don't work for me any more! -- " 
        << getName() << '.' << endl;
    
        return true;
    } else {
        cout << getName() << " failed to fire " 
        << hiredProt.getName() << endl;
        return false;
    }
}

bool Lord::removeWarrior(size_t proIndex){
    if (proIndex != allProt.size()){

        allProt[proIndex]->setLord(nullptr);
        for (size_t j = proIndex; j < allProt.size() - 1; ++j){
            allProt[j] = allProt[j + 1];
        }
        allProt.pop_back();
        return true;
    }
    return false;
}


void Lord ::changeStrength (double strengthRatio) {
    for (Protector* one : allProt){
        one->changeStrength(strengthRatio);
    }
}

void Lord::defend() const {
    for (const Protector* prot : allProt) {
        if (prot->getStrength() > 0) {
            prot->defend();
        }
    }
}

bool Lord::removeProtectorByName(const string& protName) {
    size_t index = getHiredProInd(protName);
    return removeWarrior(index);
}
ostream& operator<<(ostream& os, const Lord& rhs){
    os << rhs.getName() << " has an army of size: " << rhs.allProt.size();
    for (const Protector* ptr : rhs.allProt){
        os << "\n   "  << *ptr ;
    }
    return os;
}
// ------- definition for class PersonWithStrengthToFight -----

PersonWithStrengthToFight::PersonWithStrengthToFight 
(const string& name, double strength) : Noble(name), strength(strength) {}

double PersonWithStrengthToFight::getStrength() const {
    return strength;
}

void PersonWithStrengthToFight::changeStrength( double strengthRatio){
    if (strengthRatio == 0){
        strength = 0;
   }
   else {
   strength *= (1- strengthRatio) ;
    }
}

void PersonWithStrengthToFight::defend() const {
    if (getStrength() > 0){
        cout << "Ugh!" << endl;
    }
    
}

ostream& operator<<(ostream& os, const PersonWithStrengthToFight& rhs){
    os << rhs.getName() << " has strength: " << rhs.getStrength(); 
    return os; 
}}