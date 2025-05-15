#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft
{
class Lord;

class Protector{
    friend std::ostream& operator<<(std::ostream& os,
         const Protector& rhs);
public: 
    Protector (const std::string& name, double strength);

    double getStrength() const;
    Lord* getLord () const; 

    const std::string& getName() const;

    void setLord (Lord* newLord);
    void changeStrength( double strengthRatio);



    virtual void defend() const = 0; 
    void runaway();
private:
    std::string name; 
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
};

class Archer : public Warrior {
public: 
using Warrior::Warrior; 
    void defend() const override;
};

class Swordsman : public Warrior {
public: 
using Warrior::Warrior;
    void defend() const override;
};
}

#endif