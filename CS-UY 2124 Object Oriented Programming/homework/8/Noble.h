#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft
{
class Protector; 

class Noble{
public: 
    Noble (const std::string& name); 

    virtual double getStrength() const = 0; 
    bool getLive() const;
    const std::string& getName() const;
    void battle(Noble& opponent);
    void smallBattle(Noble& winner, Noble& loser,
        double winnerStr, double loserStr);
    virtual void changeStrength (double strengthRatio) = 0;
    virtual void defend() const = 0;
private:
    std::string name; 
    bool alive;

};

class Lord : public Noble {
    friend std::ostream& operator<<(std::ostream& os, const Lord& rhs);
public:
    using Noble :: Noble; 

    size_t getHiredProInd(const std::string& name) const;

    bool hires( Protector& freeProt);
    bool fires( Protector& hiredProt);
    double getStrength() const override;
    bool removeWarrior (size_t proIndex); 
    void changeStrength (double strengthRatio) override;

    void defend() const override;
    bool removeProtectorByName(const std::string& protName);
private:
    std::vector<Protector*> allProt; 

};

class PersonWithStrengthToFight : public Noble {
    friend std::ostream& operator<<(std::ostream& os,
         const PersonWithStrengthToFight& rhs);
public: 
    PersonWithStrengthToFight (const std::string& name, double strength); 
    double getStrength() const override;
    void defend() const override;

    void changeStrength( double strengthRatio) override; 
private: 
    double strength;
};
}
#endif