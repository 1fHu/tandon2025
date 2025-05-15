#include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;
struct Polynomial::Node {
    int data;
    Node* next = nullptr;
};
Polynomial::Polynomial() : degree(0), header(new Node{0}) {}

Polynomial::Polynomial(const vector<int>& coeffs) {
    Node* nextNode = nullptr;
    size_t start = 0;
    while (start < coeffs.size() - 1 && coeffs[start] == 0) ++start;

    for (size_t i = coeffs.size(); i > start; --i) {
        degree++;
        Node* newNode = new Node{coeffs[i - 1]};
        newNode->next = nextNode;
        nextNode = newNode;
    }
    header = nextNode;
}

Polynomial::Polynomial(const Polynomial& rhs) : degree(rhs.degree) {
    header = new Node{rhs.header->data};
    Node* curr = header;
    for (Node* p = rhs.header->next; p; p = p->next) {
        curr->next = new Node{p->data};
        curr = curr->next;
    }
}

Polynomial::~Polynomial() {
    while (header) {
        Node* temp = header;
        header = header->next;
        delete temp;
    }
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    if (this != &rhs){
        degree = rhs.degree;
        
        while (header != nullptr){
            Node* nextD  = header->next; 
            delete header; 
            header = nextD;
        }
        
        header = new Node{rhs.header->data};
        Node* currPtr = header;
        Node* nextPtr = rhs.header->next;
        while (nextPtr != nullptr){  
            currPtr->next = new Node{nextPtr->data};
            nextPtr = nextPtr->next;
            currPtr = currPtr->next;
        }
    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    if (rhs.degree > degree) {
        int diff = rhs.degree - degree;
        Node* newHead = nullptr;
        Node* tail = nullptr;
        for (int i = 0; i < diff; ++i) {
            Node* zeroNode = new Node{0};
            if (!newHead) {
                newHead = zeroNode;
                tail = zeroNode;
            } else {
                tail->next = zeroNode;
                tail = tail->next;
            }
        }
        tail->next = header;
        header = newHead;
        degree = rhs.degree;

    }

    // Now add corresponding coefficients from rhs to *this
    Node* currL = header;
    Node* currR = rhs.header;
    int diff = degree - rhs.degree;
    // Skip diff nodes in this to align degrees
    while (diff-- > 0 && currL) {
        currL = currL->next;
    }

    // Add coefficients
    while (currL && currR) {
        currL->data += currR->data;
        currL = currL->next;
        currR = currR->next;
    }
    // Cleanup leading zeros if any
    while (header && header->data == 0 && degree > 0) {
        Node* temp = header;
        header = header->next;
        delete temp;
        --degree;
    }
    return *this;
}
int Polynomial::evaluate(int num) {
    int result = 0;
    Node* curr = header;
    while (curr != nullptr) {
        result = result * num + curr->data;
        curr = curr->next;
    }
    return result;
}

ostream& operator<<(ostream& os, const Polynomial& rhs) {
    Polynomial::Node* beginPtr = rhs.header;
    int currDeg = rhs.degree;
    bool hasPrint = false;
    while (beginPtr!= nullptr){
        int currData = beginPtr->data;
        // skip all 0 data node except only one zero

        if (currData == 0 && rhs.degree != 0){
            beginPtr = beginPtr->next;
            currDeg--;
            continue;
        }
        // print + if needed
        if (hasPrint && currData > 0){

            os << '+';
            
        } 
        // when degree = 0, print 1 and -1;
        // when degree > 0, print - for -1 only.
        if (currDeg == 0){
            os << currData;
        }
        else{
            if (currData == 1 ) {}
            else if (currData == -1){
                os << '-';
                
            }
            else if (currData != 1){
                os << currData;
                
            }
            hasPrint = true;
        }
        // print x
        if (currDeg > 1){
            os << "x^" << currDeg;
        }
        else if (currDeg == 1){
            os << 'x';
        }
        currDeg--;
        beginPtr = beginPtr->next;
    }
    return os;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(rhs);
    result += lhs;
    return result;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (rhs.degree != lhs.degree) return false; 
    Polynomial::Node* rhsN = rhs.header;
    Polynomial::Node* lhsN = lhs.header;
    while (lhsN != nullptr){
        if (lhsN->data != rhsN->data){
            return false;
        }
        lhsN = lhsN->next;
        rhsN = rhsN->next;
    }
    return true;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}
