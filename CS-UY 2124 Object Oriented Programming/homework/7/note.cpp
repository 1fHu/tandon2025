
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Noble;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& rhs);
public:
    Warrior (const string& name, double strength)
     : name(name), strength(strength) {}
    
    
    const string& getName() const { return name; }
    double getStrength() const { return strength; }
    bool isHired() const{ return status;}
    bool getLive() const { return (strength != 0); }

    void changeStatus(){ // default value as false
         status = !status;
    }

    void changeStrength( double strengthRatio){
         if (strengthRatio == 0){
              strength = 0;
         }
         else {
         strength *= (1- strengthRatio) ;}
    }
    void setHisNoble (Noble* newNoble) {
        hisNoble = newNoble;
    }

    bool runaway();

private: 
    string name;
    double strength = 0;
    bool status = false;
    Noble* hisNoble = nullptr;
};


class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs);
public:
    // constructor
    Noble(const string& name) : name(name), alive(true) {}

    const string& getName() const {return name;}
    bool getLive() const { return alive;}

    size_t getHiredWarInd(const string& name) const {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i]->getName() == name){ 
                return i;}
        }
        return army.size();
    }

    bool hire( Warrior& freeWarrior){
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

    bool fire(Warrior& hiredWarrior){
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

    bool removeWarrior(size_t warIndex){
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
    void changeWarriorStrength( double strengthRatio){ 
        for (Warrior* oneWarrior : army){
            oneWarrior->changeStrength(strengthRatio);
        }
    }

    double getArmyStrength() const {
        double totalStrength = 0;
        for (Warrior* each : army) {
            totalStrength += each->getStrength();
        }
        return totalStrength;
    }

    void smallBattle(Noble& winner, Noble& loser, double winnerStr, double loserStr){
        double strengthRatio = (loserStr / winnerStr);
        loser.changeWarriorStrength(0);
        loser.alive = false;
        winner.changeWarriorStrength(strengthRatio);
        cout << winner.name << " defeats " << loser.name << endl;
    }

    //handle battle of six cases
    void battle(Noble& opponent){
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

private:
    string name;
    vector< Warrior*> army;
    bool alive;
};

ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << rhs.name << ": " << rhs.strength;
    return os;
}

ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.army.size();
    for (const Warrior* warriorptr : rhs.army){
        os << "\n   "  << *warriorptr ;
    }
    return os;
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

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha 
	 << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha 
	 << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}
