#include <iostream>
#include <vector>
using namespace std;

class Base {
public: 

private:

};

class Derived : public Base{
public: 

private: 

};

int main(){
    Base baseVar; 
    Derived deriVar;
    Base* basePtr = nullptr;
    Derived* derivePtr = nullptr;

    baseVar = deriVar;
    // deriVar = baseVar; 
    basePtr = derivePtr;
    // derivePtr = basePtr; // not working

    basePtr = &baseVar;
    derivePtr = &deriVar;
    basePtr = &deriVar;
    // derivePtr = &baseVar;    
    
}