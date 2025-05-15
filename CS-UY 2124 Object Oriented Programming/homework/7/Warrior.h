#ifndef WARRIOR_H
#define WARRIOR_H

#include<iostream>
#include<string>

namespace WarriorCraft

{

class Noble;

class Warrior{
    friend std::ostream& operator<<(std::ostream& os, const Warrior& rhs);
public:
    Warrior (const std::string& name, double strength);
    
    const std::string& getName() const;
    double getStrength() const;
    bool isHired() const;
    bool getLive() const;

    void changeStatus();

    void changeStrength( double strengthRatio);
    void setHisNoble (Noble* newNoble);

    bool runaway();

private: 
    std::string name;
    double strength = 0;
    bool status = false;
    Noble* hisNoble = nullptr;
}; // Warrior

}

#endif