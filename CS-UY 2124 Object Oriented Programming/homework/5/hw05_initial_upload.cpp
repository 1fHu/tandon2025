/*
  hw05.cpp
  Association: Noble - Warrior
  Arthur: Simon Hu
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
    Warrior (const string& name, int strength) : name(name), strength(strength) {}
    
    
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
    Noble(const string& name) : name(name) {}

    const string& getName() const {return name;}
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

private:
     string name;
     vector< Warrior*> army;
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

size_t find_noble_index( const string& nobleName, vector<Noble*> allNobles);
size_t find_warrior_index( const string& warriorName, vector<Warrior*> allWarriors);


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
            string nobleName;
            nobleFile >> nobleName;

            size_t index = find_noble_index(nobleName, allNobles);
            if (index != allNobles.size()){                      // check non-existence
                cout << nobleName << " already exists, cannot be redefined. " << endl;
                continue;
            }
            allNobles.emplace_back( new Noble(nobleName));
            
        }
        else if (firstWord == "Warrior")
        {
            string warriorName; 
            int warriorStrength;
            nobleFile >> warriorName >> warriorStrength;

            size_t index = find_warrior_index(warriorName, allWarriors);
            if (index != allWarriors.size()){                   // check non-existence
                cout << warriorName << " already exists, cannot be redefined. " << endl;
            }
            else{
            allWarriors.emplace_back(new Warrior(warriorName, warriorStrength));}
        }
        else if (firstWord == "Hire")
        {
            string nobleName;
            string warriorName;
            nobleFile >> nobleName >> warriorName;            
            
            size_t nobleIndex = find_noble_index(nobleName, allNobles);
            size_t warriorIndex = find_warrior_index(warriorName, allWarriors);

            if (nobleIndex == allNobles.size() ){
                cout << "Attempting to hire by unknown noble: " << nobleName << endl; 
            }
            else if (warriorIndex == allWarriors.size()){   // check existence
                cout << "Attempting to hire using unknown warrior: " << warriorName << endl; 
            }
            else{
                allNobles[nobleIndex]->hire(*allWarriors[warriorIndex]);} // do hire
                        
        }

        else if (firstWord == "Fire")
        {
            string nobleName;
            string warriorName;
            nobleFile >> nobleName >> warriorName;            
            
            size_t nobleIndex = find_noble_index(nobleName, allNobles);
            size_t warriorIndex = find_warrior_index(warriorName, allWarriors);
            if (nobleIndex == allNobles.size() ){
                cout << "Attempting to fire by unknown noble: " << nobleName << endl; 
            }
            else if (warriorIndex == allWarriors.size()){   // check existence
                cout << "Attempting to fire using unknown warrior: " << warriorName << endl; 
            }
            else{
                allNobles[nobleIndex]->fire(*allWarriors[warriorIndex]);} // do fire
                            
        }
                    
        else if (firstWord == "Status")
        {
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
        else if (firstWord == "Battle")
        {
            string mainNoble;
            string opponentNoble; 
            nobleFile >> mainNoble >> opponentNoble;

            size_t nobleIndex1 = find_noble_index(mainNoble, allNobles);
            size_t  nobleIndex2 = find_noble_index(opponentNoble, allNobles);
            if (nobleIndex1 == allNobles.size()){
               cout << "Unknown noble: " << mainNoble <<
               " attemping to begin a battle "<< endl; 
           }
           else if (nobleIndex2==allNobles.size())
           {
               cout << "Unknown noble: " << opponentNoble <<
               " attemping to accept a battle "<< endl; 
           }
           else{
            allNobles[nobleIndex1]->battle(*allNobles[nobleIndex2]);}
        }
        else if (firstWord == "Clear")
        {
          for (size_t i = 0; i < allNobles.size(); ++i){
               delete allNobles[i];
          }
          allNobles.clear();
          for (size_t j = 0; j < allWarriors.size(); ++j){
               delete allWarriors[j];
          }
          allWarriors.clear();
        }
        
    } // while loop
    nobleFile.close();
} //  main

/*
parameter: const string& nobleName, vector<Noble*> allNobles
return: size_t (index)
*/
size_t find_noble_index( const string& nobleName, vector<Noble*> allNobles){
    for (size_t i = 0; i < allNobles.size(); ++i) {
        if (allNobles[i]->getName() == nobleName){ 
            return i;
        }}
    return allNobles.size();
}

/*
parameter: const string& warriorName, vector<Noble*> allWarriors
return: size_t (index)
*/
size_t find_warrior_index( const string& warriorName, vector<Warrior*> allWarriors){
    for (size_t i = 0; i < allWarriors.size(); ++i) {
        if (allWarriors[i]->getName() == warriorName){ 
            return i;
        }}
    return allWarriors.size();
}