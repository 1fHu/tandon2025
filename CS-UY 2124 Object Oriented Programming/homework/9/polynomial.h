#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

class Polynomial{
    struct Node;
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public: 
    Polynomial();
    Polynomial(const std::vector<int>& num);
    Polynomial(const Polynomial& rhs);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& rhs);
    Polynomial& operator+=(const Polynomial& rhs);
    int evaluate(int num);
private: 
    int degree = -1;
    Node* header;    
};
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
bool operator==(const Polynomial& lhs, const Polynomial& rhs); 
bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

#endif