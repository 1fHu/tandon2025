#include <iostream>
#include <string>
#include <vector> 
using namespace std;


// real exam question


class Base {
public:
    virtual void eat() const = 0; 
};

class Derived : public Base {
public:
    Derived() { eat(); }
    void eat() const override {
        cout << "Derived eat"; 
    }
};

class sun1 : public Derived{
public:
    sun1(){}
    void eat() const override {
        cout << "Sun 1 eat ";
    }
};

class sun2 : public Derived{
public:
    sun2(){}
    void eat() const override{
        cout << "Sun 2 eat ";
    }
};

int main(){
    Derived one;
    sun1 two;
    sun2 three;
}


/// my practice since here


// template <typename T, typename U>
// int count (T start, T stop, U cond)


// int main(){
// double sum = 0.0;
// for (vector<double>::iterator it = myList.begin(); it != myList.end(); ++it) {
//     sum += *it;
// }
// cout << "The sum of the elements in myList is: " << sum << endl;
// }



/*
void baseThree(int n){
    if (n < 3) {
        cout << n; 
        return;
    }
    baseThree(n / 3);
    cout << (n % 3); 
    return;
}

int main(){
    baseThree(125); 
}


class Performer{
private: 
    string name; 
    bool hireC = false; 
public: 
    virtual void perform() const = 0; 
    // Performer(){}
    Performer(const string& name) : name (name) { }
    bool isHired(){ return hireC; }
    void hired() { hireC = !hireC; }
    string getName() const { return name; }
};

class Company{
public:
    void hire(Performer& per){
        if (per.isHired() == false) {
            performers.push_back(&per);
            per.hired();
        }
    }
    void showtime() const {
        for (const Performer* each : performers){
            each->perform();
        }
    }
private: 
    vector<Performer*> performers;
};

class Actor : public Performer{
    public: 
    void perform()const override{
        cout << "I am " << getName() << ". " 
        << sound << endl; 
    }
    Actor(const string& name, const string& sound)
     : Performer(name), sound(sound){}
    private: 
    string sound;
};

class Mime : public Performer{
public: 
    void perform() const override  {
        cout << "(Silence)" << endl;
    }
    Mime(const string& name): Performer(name){}
};

int main(){
    Company troupe;
    Company otherTroupe;

    Actor frog("Froggie", "Hiya, kids!");
    Mime red("Red Skelton");
    Actor bogie("Humphrey Bogart", "Play it again.");

    troupe.hire(frog);
    otherTroupe.hire(frog); // Nothing happens. Froggie was already hired.
    troupe.hire(red);
    troupe.hire(bogie);
    troupe.showtime();
}
    */
/*
class Base {
public:
virtual void foo(Base b) { cout << "Base::foo(Base)\n"; }
};
class Derived: public Base {
public:
void foo(Derived d) { cout << "Derived::foo(Derived)\n"; }
};
int main() {
    Derived der;
    Base base = der; // line A
    base.foo(der); // line B
    der.foo(der); // line C
}

*/


/*

class Base {
public:
    virtual void speak() const { cout << "Base"; }
};

class Derived : public Base {
public:
    void speak() const override { cout << "Derived"; }
};

int main() {
    Base b;
    Derived d;
    Base& ref = d;
    ref.speak();

    cout << endl; 
    Base ref2 = d;
    ref2.speak();
}



// int main(){
//     const int abc = 10;
//     int bcd = abc;
// }




class P1 {
public:
    void whoAmI() { cout << "P1"; }
};

class P2 {
public:
    void whoAmI() { cout << "P2"; }
};

class Child : public P2, public P1 {
// solve: 
// public:
//     void whoAmI() { 
//         P1::whoAmI(); // Explicitly call P1's whoAmI
//     }
};

int main() {
    Child c;
    c.whoAmI(); // Now it will print "P1"
}



class Pet {
public:
    Pet(string name) : name(name){}
    void display() { cout << name <<' '; }
protected:
    void setName(string name){this -> name = name; }; // Accessible by derived classes
private:
    string name; // Not directly accessible outside

};

class Cat : public Pet {
public:
    Cat(string name) : Pet(name) {}
};

class Dog : public Pet {
public:
    Dog() : Pet("ruff") {}

    // void setCatName(Cat& rhs) {
    //     rhs.setName("Mehitabel");   
    // }

    void setDogName(Dog& rhs) {
        rhs.setName("Fido");        
    }
};



int main(){
    Cat felix("Felix");      
    Dog fido;                
    Dog rover;               
    
    // fido.setCatName(felix);  
    felix.display();         

    fido.setDogName(fido);   
    fido.display();          
}
    */