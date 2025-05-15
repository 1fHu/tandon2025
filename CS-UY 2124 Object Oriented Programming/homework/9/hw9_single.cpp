// single linked list 

#include <iostream>
#include <vector>
using namespace std; 


class Polynomial{
    struct Node{
        int data;
        Node* next = nullptr; 
    };
    friend ostream& operator<<(ostream& os, const Polynomial& rhs);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public: 
    Polynomial(){
        header = new Node{0};
        degree = 0;
    }

    Polynomial(const vector<int>& num){
        Node* nextNode = nullptr;
        size_t start = 0;
        // Skip leading zeros but leave at least one
        while (start < num.size() - 1 && num[start] == 0) {
            ++start;
        }
    
        for (size_t i = num.size(); i > start; --i){
            degree += 1;
            Node* newNode = new Node{num[i-1]};
            newNode->next = nextNode;
            nextNode = newNode;
        }
        header = nextNode;
    }

    // copy control
    Polynomial(const Polynomial& rhs){
        degree = rhs.degree;
        header = new Node{rhs.header->data};
        Node* currPtr = header;
        Node* nextPtr = rhs.header->next;
        while (nextPtr != nullptr){  
            currPtr->next = new Node{nextPtr->data};
            nextPtr = nextPtr->next;
            currPtr = currPtr->next;
        }
    }

    ~Polynomial(){
        Node* nextD = header;
        while (header != nullptr){
            nextD  = header->next; 
            delete header; 
            header = nextD;
        }
    }

    Polynomial& operator=(const Polynomial& rhs){
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

    // operator overload
    Polynomial& operator+=(const Polynomial& rhs){
        // If rhs has higher degree, prepend zero nodes to this list
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

    int evaluate(int num) {
        int result = 0;
        Node* curr = header;
        while (curr != nullptr) {
            result = result * num + curr->data;
            curr = curr->next;
        }
        return result;
    }

private: 
    int degree = -1;
    Node* header;
};

ostream& operator<<(ostream& os, const Polynomial& rhs){
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

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial aPoly (rhs);
    aPoly += lhs;
    return aPoly;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs); 

bool operator==(const Polynomial& lhs, const Polynomial& rhs){
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

bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}

void doNothing(Polynomial temp) {}

int main()
{    
    //test constructor
    Polynomial p0;                       // 0
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    cout << "displaying polynomials\n"
         << "p0: " << p0 << endl
         << "p1: " << p1 << endl
         << "p2: " << p2 << endl
         << "p3: " << p3 << endl
         << "p4: " << p4 << endl
         << "has_a_zero: " << has_a_zero << endl;

    // test copy constructor - the statement below uses the copy constructor
    // to initialize copy_of_p4 with the same values as poly4
    Polynomial copy_of_p4(p4);
    cout << "copy_of_p4: " << copy_of_p4 << endl;
        
    cout << "p2 + p3: " << (p2+p3) << endl
         << "p2 + p4: " << (p2+p4) << endl
         << "p4 + p2: " << (p4+p2) << endl;
    Polynomial result_of_p2_plus_p3(p2+p3);
    cout << "result_of_p2_plus_p3: " << result_of_p2_plus_p3 << endl;

    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  

    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
        
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()

    cout << "p8: " << p8 << endl
         << "p9: " << p9 << endl
         << "p10: " << p10 << endl;

    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
    
} // main
