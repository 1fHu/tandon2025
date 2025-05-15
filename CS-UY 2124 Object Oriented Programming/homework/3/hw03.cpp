/*
Simon Hu
warrior with weapon
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
Warriors class
member variables: string name, Weapon wWeapon(warrior's weapon)
Three getter functions and one change inside weapon strength function

One inner Weapon class:
    member variables: string nameWeapon, int strength
    Two getter functions and one function to change the strength

*/
class Warrior{
private:
    class Weapon{
    private:
        // member variables:
        string nameWeapon;
        int strength;

        friend ostream& operator<<(ostream& os, const Weapon& rhs);
    
    public:
        // constructor
        Weapon(const string& name, int strength) 
            : nameWeapon(name), strength(strength) {}
        
        // getter functions
        const string& getName() const { return nameWeapon;}
        int getNum() const { return strength;}

        // get weapon strength 
        void changeStrength(int newStrength) {
            strength = newStrength;
        }
    
    };

    // private member variables:
    string name;
    Weapon wWeapon;

    friend ostream& operator<<(ostream& os, const Weapon& rhs); 
    friend ostream& operator<<(ostream& os, const Warrior& rhs); 

public: 
    // constructor
    Warrior(const string& name, const string& nameW, int strength)
        : name(name), wWeapon(nameW, strength) {}
    
    // getter functions
    const string& getWeaponName() const {
        return wWeapon.getName();
    }
    int getStrength() const {
        return wWeapon.getNum();
    }
    const string& getName() const { return name;}
    
    // get weapon strength 
    void changeWeaponStrength(int newStrength) {
        wWeapon.changeStrength(newStrength);
    }

    bool doBattle(Warrior& opponent){
        // cout << name << " battles " << opponent.name << endl;
        if (wWeapon.getNum() == 0 && opponent.getStrength() == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (wWeapon.getNum() == 0)
        {
            cout << "He's dead, " << opponent.name << endl;
        }
        else if (opponent.getStrength() == 0)
        {
            cout << "He's dead, " << name << endl;
        }
        else if (wWeapon.getNum() > opponent.getStrength())
        {   
            int finalStrength = wWeapon.getNum() - opponent.getStrength();
            wWeapon.changeStrength(finalStrength);
            opponent.changeWeaponStrength(0);
            cout << name << " defeats " << opponent.name << endl;
        }
        else if (wWeapon.getNum() < opponent.getStrength())
        {   
            int finalStrength = opponent.getStrength() - wWeapon.getNum();
            opponent.changeWeaponStrength(finalStrength);
            wWeapon.changeStrength(0);
            cout << opponent.name << " defeats " << name << endl;
        }
        else { // equal strength 
            wWeapon.changeStrength(0);
            opponent.changeWeaponStrength(0);
            cout << "Mutual Annihilation: " << name << " and " 
                << opponent.name << " die at each other's hands" << endl;
        }
        return true;
        
        
    }
    
};

ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << "Warrior: " << rhs.name  << ", weapon: " 
        << rhs.wWeapon;
    return os;
}

ostream& operator<<(ostream& os, const Warrior::Weapon& rhs) {
    os << rhs.nameWeapon  << ", " << rhs.strength;
    return os;
}


void changeWarrior(const string& currentName, const int& newStrength, 
    vector<Warrior>& allWarrior);
void addWarrior(const string& nameN,const string& nameW, const int& strength, 
    vector<Warrior>& allWarrior);
void showStatus(const vector<Warrior>& allWarrior);



int main(){
    ifstream warriorStream("Warriors.txt");
    if (!warriorStream){
        cout << "failed to open Warriors.txt" << endl;
        exit(1);
    }

    string firstWord;
    vector<Warrior> allWarrior;

    while (warriorStream >> firstWord)
    {
        if (firstWord == "Warrior"){
            string nameN;
            string nameW;
            int strength;
            warriorStream >> nameN >> nameW >> strength;
    
            addWarrior(nameN, nameW, strength, allWarrior);
            
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

            // check name existance
            bool actualBattle = false;
            for (Warrior& oneWarrior : allWarrior){
                for (Warrior& secondWarrior : allWarrior){
                    if (oneWarrior.getName() == nameOne && secondWarrior.getName() == nameTwo){
                        actualBattle = oneWarrior.doBattle(secondWarrior);
                    }
                }
            }
            
            if (actualBattle == false){
                cout << "There is no battle since warriors are not all defined." << endl;
            }

        }
    }
    warriorStream.close();
}




/*
store the name and strength of a warrior
parameter: const string reference warrior name, 
            const string reference weapon name, 
            const int reference weapon strength,
            vector<Warrior> reference allWarrior,
return: None
*/
void addWarrior(const string& nameN,const string& nameW, const int& strength, 
    vector<Warrior>& allWarrior){
    // check unique name
    for (const Warrior& oneWarrior : allWarrior){ // use inside object (each one warrior) directly
        if (oneWarrior.getName() == nameN){
            cout << nameN <<" already exists, unable to add." << endl;
            return;
        }
    }
    allWarrior.emplace_back(nameN, nameW, strength);
}



/*
show current status of all Warriors
parameter: const vector<Warrior>& allWarrior
return: None
*/
void showStatus(const vector<Warrior>& allWarrior){
    size_t numbers = allWarrior.size();
    cout << "There are: " << numbers << " warriors" << endl;
    for (size_t i = 0; i < numbers; ++i ){
        cout << allWarrior[i] << endl;
    }
}

