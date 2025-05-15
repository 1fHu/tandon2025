#include<iostream>
#include<string>
#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft

{
// noble class
Noble::Noble(const string& name) : name(name), alive(true) {}

const string& Noble::getName() const {return name;}
bool Noble::getLive() const { return alive;}

size_t Noble::getHiredWarInd(const string& name) const {
    for (size_t i = 0; i < army.size(); ++i) {
        if (army[i]->getName() == name){ 
            return i;}
    }
    return army.size();
}

bool Noble::hire( Warrior& freeWarrior){
    if (!alive){
        cout << name
            << " is dead and cannot hire warriors." << endl;
        return false;
    }
    if (freeWarrior.isHired() == true ||
        freeWarrior.getLive() == false) {
        cout << name << " failed to hire " 
            << freeWarrior.getName() << endl;
        return false;
    }
    
    army.push_back(&freeWarrior);
    freeWarrior.changeStatus();
    freeWarrior.setHisNoble(this);
    return true;
}

bool Noble::fire(Warrior& hiredWarrior){
    if (!alive){
        cout << name
            << " is dead and cannot fire warriors." << endl;
        return false;
    }

    size_t index = getHiredWarInd(hiredWarrior.getName());

    if (hiredWarrior.isHired() == false || 
        hiredWarrior.getLive() == false) {
        cout << name << " failed to fire " 
            << hiredWarrior.getName() << endl;
        return false;
    }

    if (removeWarrior(index)){
        cout << hiredWarrior.getName() 
        << ", you don't work for me any more! -- " 
        << name << '.' << endl;
    
        return true;
    } else {
        cout << name << " failed to fire " 
        << hiredWarrior.getName() << endl;
        return false;
    }
}

bool Noble::removeWarrior(size_t warIndex){
    if (warIndex != army.size()){
        army[warIndex]->changeStatus();
        army[warIndex]->setHisNoble(nullptr);
        for (size_t j = warIndex; j < army.size() - 1; ++j){
            army[j] = army[j + 1];
        }
        army.pop_back();
        return true;
    }
    return false;
}

// Update strength of all warriors in the army
void Noble::changeWarriorStrength( double strengthRatio){ 
    for (Warrior* oneWarrior : army){
        oneWarrior->changeStrength(strengthRatio);
    }
}

double Noble::getArmyStrength() const {
    double totalStrength = 0;
    for (Warrior* each : army) {
        totalStrength += each->getStrength();
    }
    return totalStrength;
}

void Noble::smallBattle(Noble& winner, Noble& loser, double winnerStr, double loserStr){
    double strengthRatio = (loserStr / winnerStr);
    loser.changeWarriorStrength(0);
    loser.alive = false;
    winner.changeWarriorStrength(strengthRatio);
    cout << winner.name << " defeats " << loser.name << endl;
}

void Noble::battle(Noble& opponent){
    cout << name << " battles " << opponent.name << endl;

    double myArmyStrength = getArmyStrength();
    double opponentStrength = opponent.getArmyStrength();

    // six cases
    if (myArmyStrength == 0 && opponentStrength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    else if (myArmyStrength == 0)
    {
        cout << "He's dead, " << opponent.name << endl;
    }
    else if (opponentStrength == 0)
    {
        cout << "He's dead, " << name << endl;
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
        changeWarriorStrength(0);
        opponent.changeWarriorStrength(0);
        alive = false ;
        opponent.alive = false;
        cout << "Mutual Annihilation: " << name << " and " 
            << opponent.name << " die at each other's hands" << endl;
    }   
}

ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.army.size();
    for (const Warrior* warriorptr : rhs.army){
        os << "\n   "  << *warriorptr ;
    }
    return os;
}

}