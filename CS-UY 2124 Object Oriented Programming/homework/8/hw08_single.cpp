#include <string>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;


// --- CLASS: Noble --- 
class Protector; 
class Noble{

public: 
    Noble (const string& name); 
    virtual ~Noble() = default; // added virtual destructor
    virtual double getStrength() const = 0; 
    bool getLive() const;
    const string& getName() const;
    void battle(Noble& opponent);
    void smallBattle(Noble& winner, Noble& loser,
        double winnerStr, double loserStr);
    virtual void changeStrength (double strengthRatio) = 0;
    virtual void defend() const = 0;
private:
    string name; 
    bool alive;

};

class Lord : public Noble {
    friend ostream& operator<<(ostream& os, const Lord& rhs);
public:
    using Noble :: Noble; 

    size_t getHiredProInd(const string& name) const;

    bool hires( Protector& freeProt);
    bool fires( Protector& hiredProt);
    double getStrength() const override;
    bool removeWarrior (size_t proIndex); 
    void changeStrength (double strengthRatio) override;

    void defend() const override;
    bool removeProtectorByName(const string& protName);
private:
    vector<Protector*> allProt; 

};

class PersonWithStrengthToFight : public Noble {
    friend ostream& operator<<(ostream& os, const PersonWithStrengthToFight& rhs);
public: 
    PersonWithStrengthToFight (const string& name, double strength); 
    double getStrength() const override;
    void defend() const override;

    void changeStrength( double strengthRatio) override; 
private: 
    double strength;
};

// --- CLASS: Protector --- 
class Protector{
    friend ostream& operator<<(ostream& os, const Protector& rhs);
public: 
    Protector (const string& name, double strength);
    virtual ~Protector() = default; // added virtual destructor
    double getStrength() const;
    Lord* getLord () const; 

    const string& getName() const;

    void setLord (Lord* newLord);
    void changeStrength( double strengthRatio);

    virtual void defend() const = 0; 
    void runaway();
private:
    string name; 
    double strength; 
    Lord* lordPtr; 
};

class Wizard : public Protector {
public: 
    using Protector :: Protector; 
    void defend() const override ;

};

class Warrior : public Protector {
public: 
    using Protector :: Protector; 
    void defend() const override; 
protected:
    virtual string getBattleCry() const = 0;
};

class Archer : public Warrior {
public: 
    using Warrior::Warrior; 
protected:
    string getBattleCry() const override {
        return "TWANG!";
    }
   
};

class Swordsman : public Warrior {
public: 
    using Warrior::Warrior;
protected:
    string getBattleCry() const override {
        return "CLANG!";
    }
};

// ------- definition for class Noble -----

Noble::Noble(const string& name) : name(name), alive(true) {}

bool Noble :: getLive() const{
    return alive; 
}
const string&  Noble ::getName() const{
    return name;
}



void Noble::smallBattle(Noble& winner, Noble& loser, double winnerStr, double loserStr){

    if (loserStr != 0){
        double strengthRatio = (loserStr / winnerStr); // winnerStr never get 0 here
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
}

// ------- definition for class Protector -----
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

void Warrior::defend() const  {
    if (getStrength() > 0 && getLord() != nullptr) {
        
        cout << getBattleCry() << " " << getName()
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
}

bool Lord::removeProtectorByName(const string& protName) {
    size_t index = getHiredProInd(protName);
    return removeWarrior(index);
}

int main() {
// ---- test ----- 



    
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "==========\n";

    /* */
} // main
