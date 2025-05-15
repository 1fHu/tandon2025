/*
  hw05.cpp
  Association: Noble - Warrior
  Arthor: Simon Hu (revised)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
Warrior class
member variables: string name, double strength = 0; 
                    bool status of whether dead = false;
Four getter functions and one change status and 
          one change strength function.
*/
class Warrior{
     friend ostream& operator<<(ostream& os, const Warrior& rhs);
public:
    Warrior (const string& name, double strength)
     : name(name), strength(strength) {}
    
    
    const string& getName() const { return name; }
    double getStrength() const { return strength; }
    bool getStatus() const{ return status;}
    bool getLive() const { return (strength != 0); }

    void changeStatus(){
         status = !status;
    }

    void changeStrength( double strengthRatio){
         if (strengthRatio == 0){
              strength = 0;
         }
         else {
         strength *= (1- strengthRatio) ;}
    }

private: 
     string name;
     double strength = 0;
     bool status = false;
};

/*
Noble class
member variables: string name; vector< Warrior*> army; 
functions: getName, hire, fire, changeWarriorStrength and battle. 
*/
class Noble{
     friend ostream& operator<<(ostream& os, const Noble& rhs);
public:
     // constructor
     Noble(const string& name) : name(name), alive(true) {}

     const string& getName() const {return name;}

     bool hire( Warrior& freeWarrior){
          if (!alive){
               cout << name
                    << " is dead and cannot hire warriors." << endl;
               return false;
          }
          if (freeWarrior.getStatus() == true ||
              freeWarrior.getLive() == false) {
               cout << name << " failed to hire " 
                    << freeWarrior.getName() << endl;
               return false;
          }
          
          army.push_back(&freeWarrior);
          freeWarrior.changeStatus();
          return true;
     }

     bool fire(Warrior& hiredWarrior){
          if (!alive){
               cout << name
                    << " is dead and cannot fire warriors." << endl;
               return false;
          }
          if (hiredWarrior.getStatus() == false || 
               hiredWarrior.getLive() == false) {
               cout << name << " failed to fire " 
                    << hiredWarrior.getName() << endl;
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
               cout << name << " failed to fire " 
                    << hiredWarrior.getName() << endl;
               return false;
          }
          for (size_t j = index; j < army.size() - 1; ++j){
               army[j] = army[j + 1];
          }
          cout << hiredWarrior.getName() 
               << ", you don't work for me any more! -- " 
               << name << '.' << endl;
          army.pop_back();
          hiredWarrior.changeStatus();
          return true;
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
    
     void smallBattle(Noble winner, Noble loser, double winnerStr, double loserStr){
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

size_t find_noble_index( const string& nobleName,
      const vector<Noble*>& allNobles);
size_t find_warrior_index( const string& warriorName,
      const vector<Warrior*>& allWarriors);

void setNoble(ifstream& nobleFile, vector<Noble*>& allNobles);
void setWarrior(ifstream& nobleFile, vector<Warrior*>& allWarriors);
bool hireFireCommand(ifstream& nobleFile, const string& cmd, 
     vector<Noble*>& allNobles, vector<Warrior*>& allWarriors);
bool battleCmd(ifstream& nobleFile, vector<Noble*>& allNobles);
void showStatus(const vector<Noble*>& allNobles, 
     const vector<Warrior*>& allWarriors);
void deleteAll(vector<Noble*>& allNobles, vector<Warrior*>& allWarriors);


int main(){
    ifstream nobleFile("nobleWarriors.txt");
    if (!nobleFile){ 
        cout << "The file doesn't exist. ";
        exit(1);
    }
    
    string firstWord;
    vector<Noble*> allNobles; 
    vector<Warrior*> allWarriors;

    while (nobleFile >> firstWord){
        if (firstWord == "Noble")
        {
          setNoble(nobleFile, allNobles);      
        }
        else if (firstWord == "Warrior")
        {
          setWarrior(nobleFile, allWarriors);
        }
        else if (firstWord == "Hire")
        {
          hireFireCommand(nobleFile, firstWord, allNobles, allWarriors);             
        }

        else if (firstWord == "Fire")
        {
          hireFireCommand(nobleFile, firstWord, allNobles, allWarriors);      
        }
                    
        else if (firstWord == "Status")
        {
          showStatus(allNobles,allWarriors);
        }
        else if (firstWord == "Battle")
        {
          battleCmd(nobleFile, allNobles);
        }
        else if (firstWord == "Clear")
        {
          deleteAll(allNobles, allWarriors);
        }
    } // while loop

    nobleFile.close();
} //  main

void setNoble(ifstream& nobleFile, vector<Noble*>& allNobles){
     string nobleName;
     nobleFile >> nobleName;

     size_t index = find_noble_index(nobleName, allNobles);
     if (index != allNobles.size()){                      // check non-existence
         cout << nobleName << " already exists, cannot be redefined. " << endl;
     }
     else {
          allNobles.push_back( new Noble(nobleName));
     }
     
}

void setWarrior(ifstream& nobleFile, vector<Warrior*>& allWarriors){
     string warriorName; 
     double warriorStrength;
     nobleFile >> warriorName >> warriorStrength;

     size_t index = find_warrior_index(warriorName, allWarriors);
     if (index != allWarriors.size()){                   // check non-existence
         cout << warriorName << " already exists, cannot be redefined. " << endl;
     }
     else{
     allWarriors.push_back(new Warrior(warriorName, warriorStrength));}
}

size_t find_noble_index( const string& nobleName, const vector<Noble*>& allNobles){
     for (size_t i = 0; i < allNobles.size(); ++i) {
          if (allNobles[i]->getName() == nobleName){ 
               return i;}
     }
     return allNobles.size();
}

size_t find_warrior_index( const string& warriorName, const vector<Warrior*>& allWarriors){
     for (size_t i = 0; i < allWarriors.size(); ++i) {
          if (allWarriors[i]->getName() == warriorName){ 
               return i;}
     }
     return allWarriors.size();
}

void showStatus(const vector<Noble*>& allNobles, const vector<Warrior*>& allWarriors){
     cout << "Status\n======\nNobles: " << endl;
     if (allNobles.size() == 0){ 
          cout << "NONE" << endl;
     }
     else
          {for (size_t i = 0; i < allNobles.size(); ++i){
               cout << *allNobles[i] << endl;
          }}
     cout << "\nUnemployed Warriors:" << endl;
     bool allemployed = true;
     for (size_t j = 0; j < allWarriors.size(); ++j){
          if (allWarriors[j]->getStatus() == false){
               cout << "   " << *allWarriors[j] << endl;
               allemployed = false;
          }
     } 
     if (allemployed == true){
          cout << "NONE" << endl;
     }
}

void deleteAll(vector<Noble*>& allNobles, vector<Warrior*>& allWarriors){
     for (size_t i = 0; i < allNobles.size(); ++i){
          delete allNobles[i];
     }
     allNobles.clear();
     for (size_t j = 0; j < allWarriors.size(); ++j){
          delete allWarriors[j];
     }
     allWarriors.clear();
}

bool hireFireCommand(ifstream& nobleFile, const string& cmd, 
                    vector<Noble*>& allNobles, vector<Warrior*>& allWarriors){
     string nobleName;
     string warriorName;
     nobleFile >> nobleName >> warriorName;            
     
     size_t nobleIndex = find_noble_index(nobleName, allNobles);
     size_t warriorIndex = find_warrior_index(warriorName, allWarriors);

     if (nobleIndex == allNobles.size() ){
         cout << "Attempting to hire or fire by unknown noble: " << nobleName << endl; 
         return false;
     }
     else if (warriorIndex == allWarriors.size()){ 
         cout << "Attempting to hire or fire using unknown warrior: " 
               << warriorName << endl; 
         return false;
     }
     else if (cmd == "Hire"){
         allNobles[nobleIndex]->hire(*allWarriors[warriorIndex]);
         return true;
     }

     else { // fire
          allNobles[nobleIndex]->fire(*allWarriors[warriorIndex]);
          return true;
     }

}

bool battleCmd(ifstream& nobleFile, vector<Noble*>& allNobles){
     string mainNoble;
     string opponentNoble; 
     nobleFile >> mainNoble >> opponentNoble;

     size_t nobleIndex1 = find_noble_index(mainNoble, allNobles);
     size_t  nobleIndex2 = find_noble_index(opponentNoble, allNobles);
     if (nobleIndex1 == allNobles.size()){
          cout << "Unknown noble: " << mainNoble <<
          " attemping to begin a battle "<< endl; 
          return false; 
     }
     else if (nobleIndex2==allNobles.size())
     {
          cout << "Unknown noble: " << opponentNoble <<
          " attemping to accept a battle "<< endl; 
          return false;
     }
     else {
     allNobles[nobleIndex1]->battle(*allNobles[nobleIndex2]);
     return true;
     }
}
