/*
Simon Hu
warrior fight
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
One Warrior struct has its name in string type
and strength in int type.
*/
struct Warrior
{
    string name;
    int strength;
};


void addWarrior(const string& newName, const int& strength, 
                vector<Warrior>& allWarrior);
void changeWarrior(const string& currentName, const int& newStrength, 
                    vector<Warrior>& allWarrior);
void showStatus(const vector<Warrior>& allWarrior);
void doBattle(const string& nameOne, const string& nameTwo, 
                vector<Warrior>& allWarrior);


int main(){
    ifstream warriorStream("Warriors.txt");
    string firstWord;
    vector<Warrior> allWarrior;

    while (warriorStream >> firstWord)
    {
        if (firstWord == "Warrior"){
            string name;
            int strength;
            warriorStream >> name >> strength;
            addWarrior(name, strength, allWarrior);
        }
        else if (firstWord == "Status")
        {
            showStatus(allWarrior);
        }
        else if (firstWord == "Battle")
        {
            string nameOne;
            string nameTwo;
            warriorStream >> nameOne >> nameTwo;
            cout << nameOne << " battles " << nameTwo << endl;
            doBattle(nameOne, nameTwo, allWarrior);
        }
    }
}

/*
store the name and strength of a warrior
parameter: const string reference name, 
            const int reference strength,
            vector of struct Warrior reference
return: None
*/
void addWarrior(const string& newName, const int& strength, 
                vector<Warrior>& allWarrior){
    // check unique name
    for (size_t i = 0; i < allWarrior.size(); ++i){
        if (allWarrior[i].name == newName){
            cout << newName <<" already exists, unable to add." << endl;
            return;
        }
    }
    Warrior oneNewWarrior;
    oneNewWarrior.name = newName;
    oneNewWarrior.strength = strength;
    allWarrior.push_back(oneNewWarrior);
}

/*
revise strength of a warrior when needed
parameter: const string reference name, 
            const int reference strength,
            vector of struct Warrior reference
return: None
*/
void changeWarrior(const string& currentName, const int& newStrength, 
                    vector<Warrior>& allWarrior){
    //find index and then change
    for (size_t i = 0; i < allWarrior.size(); ++i ){
        if (allWarrior[i].name == currentName){
            allWarrior[i].strength = newStrength;
            return;
        }
    }
}

/*
show current status of all Warriors
parameter: const vector<Warrior>& allWarrior
return: None
*/
void showStatus(const vector<Warrior>& allWarrior){
    int numbers = allWarrior.size();
    cout << "There are: " << numbers << " warriors" << endl;
    for (size_t i = 0; i < numbers; ++i ){
        cout << "Warrior: " 
            << allWarrior[i].name 
            << ", strength: "
            << allWarrior[i].strength << endl;
    }
}

/*
show index of one warrior in vector of all warriors
parameter: const string reference name, vector<Warrior> reference allWarrior
return: size_t (index)
*/
size_t findPlace(const string& name, vector<Warrior>& allWarrior){
    for (size_t i = 0; i < allWarrior.size(); ++i){
        if (allWarrior[i].name == name){
            return i;
        }
    }
    return -1; // size_t cannot return -1. 
}


/*
do each battle with given two warriors
parameter: const string reference nameOne, const string reference nameTwo, 
            vector<Warrior> reference allWarrior
return: None
*/
void doBattle(const string& nameOne, const string& nameTwo, 
                vector<Warrior>& allWarrior){
    // check existance and strength
    int placeOne = findPlace(nameOne, allWarrior);
    int placeTwo = findPlace(nameTwo, allWarrior);
    if (placeOne == -1 || placeTwo == -1){
        cout << "There is no battle since warriors are not all defined." << endl;
        return;
    }

    int strengthOne = allWarrior[placeOne].strength;
    int strengthTwo = allWarrior[placeTwo].strength;

    // six cases
    if (strengthOne == 0 && strengthTwo == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (strengthTwo == 0){
            cout << "He's dead, " << nameOne << endl;
    }
    else if (strengthOne == 0){
            cout << "He's dead, " << nameTwo << endl;
    }
    else if (strengthOne > strengthTwo){
        changeWarrior(nameOne, (strengthOne- strengthTwo), allWarrior);
        changeWarrior(nameTwo, 0, allWarrior);
        cout << nameOne << " defeats " << nameTwo << endl;
    }
    else if (strengthOne < strengthTwo){
        
        changeWarrior(nameTwo, (strengthTwo- strengthOne), allWarrior);
        changeWarrior(nameOne, 0, allWarrior);
        cout << nameTwo << " defeats " << nameOne << endl;
    }
    else if (strengthOne == strengthTwo)
    {
        changeWarrior(nameTwo, 0, allWarrior);
        changeWarrior(nameOne, 0, allWarrior);
        cout << "Mutual Annihilation: " << nameOne<< " and " << nameTwo 
        <<" die at each other's hands" << endl;
    }
}
    
