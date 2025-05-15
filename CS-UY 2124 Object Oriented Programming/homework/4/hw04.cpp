/*
  hw04.cpp
  Association: Noble - Warrior
  Arthur: Simon Hu
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Warrior class
member variables: string name, double strength = 0; bool status = false;
Four getter functions and one change status and one change strength function.
*/
class Warrior{
     string name;
     double strength = 0;
     bool status = false;
     

public:
     Warrior (const string& name, int strength) : name(name), strength(strength) {}
     friend ostream& operator<<(ostream& os, const Warrior& rhs);
     
     const string& getName() const { return name; }
     int getStrength() const { return strength; }
     bool getStatus() const{ return status;}
     bool getLive() const { 
          if (strength == 0){
               return false;
          }
          else {
               return true;
          } 
     }
 
     void changeStatus(){
          if (status == false){
               status = true;
          }
          else {
               status = false;
          }
     }

     void changeStrength( double strengthRatio){
          if (strengthRatio == 0){
               strength *= 0;
          }
          else {
          strength *= (1- strengthRatio) ;}
     }
};


/*
Noble class
member variables: string name;
     vector< Warrior*> army;
has function hire, fire, changeWarriorStrength and battle. 
*/
class Noble{
     string name;
     vector< Warrior*> army;

     friend ostream& operator<<(ostream& os, const Noble& rhs);

public:
     // constructor
     Noble(const string& name) : name(name) {}

     /*
     hire any warrior
     input: warrior reference of a free warrior
     return: bool (whether succeed or not)
     */
     bool hire( Warrior& freeWarrior){
          // check warrior is free and live
          if (freeWarrior.getStatus() == true || freeWarrior.getLive() == false){
               cout << name << " failed to hire " << freeWarrior.getName() << endl;
               return false;
          }
          
          Warrior* oneFreeWarrior = &freeWarrior;
          army.push_back(oneFreeWarrior);
          freeWarrior.changeStatus();
          
          return true;
     }

     /*
     fire any warrior
     input: warrior reference of a hired warrior
     return: bool (whether succeed or not)
     */
     bool fire(Warrior& hiredWarrior){
          // check warrior is hired and live
          if (hiredWarrior.getStatus() == false || hiredWarrior.getLive() == false){
               cout << name << " failed to fire " << hiredWarrior.getName() << endl;
               return false;
          }
          
          size_t index = army.size();
          for (size_t i = 0; i < army.size(); ++i) {
               if (army[i] == &hiredWarrior){
                    
                    index = i;
                    break;
               }
          }
          if (index == army.size()) { // not found
               cout << name << " failed to fire " << hiredWarrior.getName() << endl;
               return false;
          }
          for (size_t j = index; j < army.size() - 1; ++j){
               army[j] = army[j + 1];
          }
          cout << hiredWarrior.getName() << ", you don't work for me any more! -- " 
               << name << '.' << endl;
          army.pop_back();
          hiredWarrior.changeStatus();

          
          return true;
     }

     /*change all warrior's strength in one army
     input: double strengthRatio 
     return: None
     */
     void changeWarriorStrength( double strengthRatio){ 
          for (Warrior* oneWarrior : army){
               oneWarrior->changeStrength(strengthRatio);
          }
     }
     
     /*
     handle battle of six cases
     input: Noble opponent reference
     return: None */
     void battle(Noble& opponent){
          cout << name << " battles " << opponent.name << endl;
          // army's total strength
          double myArmyStrength = 0;
          double opponentStrength = 0;
          for (Warrior* oneWarrior : army){
               myArmyStrength += oneWarrior->getStrength();
          }
          for (Warrior* oneWarrior : opponent.army){
               opponentStrength += oneWarrior->getStrength();
          }
          
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
               double strengthRatio = (opponentStrength / myArmyStrength);
               opponent.changeWarriorStrength(0);
               changeWarriorStrength(strengthRatio);
               cout << name << " defeats " << opponent.name << endl;
          }
          else if (myArmyStrength < opponentStrength)
          {   
               double strengthRatio = (myArmyStrength / opponentStrength);
               changeWarriorStrength(0);
               opponent.changeWarriorStrength(strengthRatio);
               cout << opponent.name << " defeats " << name << endl;
          }
          else { // equal strength 
               changeWarriorStrength(0);
               opponent.changeWarriorStrength(0);
               cout << "Mutual Annihilation: " << name << " and " 
                    << opponent.name << " die at each other's hands" << endl;
          }   
     }
};

ostream& operator<<(ostream& os, const Warrior& rhs) {
     os << rhs.name << ": " << rhs.strength; // changed from getter since already friends
     return os;
}

ostream& operator<<(ostream& os, const Noble& rhs) {
     os << rhs.name << " has an army of " << rhs.army.size();
     for (const Warrior* warriorptr : rhs.army){
          os << "\n   "  << *warriorptr ;
     }
     return os;
}

int main()
{
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
	
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
} // main
