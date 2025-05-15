#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft

{class Warrior;

class Noble{
    friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
public:
    
    Noble(const std::string& name);

    const std::string& getName() const;
    bool getLive() const;

    size_t getHiredWarInd(const std::string& name) const;

    bool hire( Warrior& freeWarrior);

    bool fire(Warrior& hiredWarrior);

    bool removeWarrior(size_t warIndex);

    // Update strength of all warriors in the army
    void changeWarriorStrength (double strengthRatio);

    double getArmyStrength() const ;

    void smallBattle(Noble& winner, Noble& loser, double winnerStr, double loserStr);

    //handle battle of six cases
    void battle(Noble& opponent);

private:
    std::string name;
    std::vector< Warrior*> army;
    bool alive;
}; // Noble
}

#endif