/*
  hw06.cpp
  Simon Hu
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Put your BigUnsigned class definition here.

/*
variable: vector<int>
*/

class BigUnsigned {
     friend ostream& operator<<(ostream& os, const BigUnsigned& rhs);
     friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
     friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);

public:
     // constructors
     BigUnsigned(int num = 0) {
          if (num == 0){
               numVec.push_back(0);
          }
          else{
               while (num != 0) {
                    numVec.push_back(num % 10);
                    num /= 10;
               }
          }
     }
     BigUnsigned(const string& numStr)  { // "000123abc123" "0" "0123"

     numVec.clear(); 

     size_t index = 0;
     size_t startIndex = 0;
     size_t endIndex = 0; 

     
     while (index < numStr.size() && (numStr[index] == ' ' || numStr[index] == '\t')) {
          ++index;
     }

     
     if (index == numStr.size()) {
          numVec.push_back(0);
          return;
     }

     
     while (index < numStr.size() && numStr[index] == '0') {
          ++index;
     }
     
     startIndex = index;

     
     while (index < numStr.size() && isdigit(numStr[index])) {
          ++index;
     }
     
     endIndex = index;

     
     if (startIndex == endIndex) {
          numVec.push_back(0);
          return;
     }

     
     for (size_t i = endIndex; i > startIndex; --i) {
          numVec.push_back(numStr[i - 1] - '0');
     }
     }
     BigUnsigned& operator+=(const BigUnsigned& other){
          size_t oneLength = numVec.size();
          size_t twoLength = other.numVec.size();
          int carry = 0;
          size_t maxLength = max(oneLength, twoLength);

          for (size_t i = 0; i < maxLength; ++i){
               int added = 0;  
               if (i == oneLength){
                    numVec.push_back(0);
               }
               if (i < twoLength){
                    added = other.numVec[i];
               }
               else{
                    added = 0;
               }

               int initVal = numVec[i] + added + carry;
               numVec[i] = initVal % 10;
               carry = initVal / 10;
          }

          if (carry) {
               numVec.push_back(1);
          }
          return *this;
     }

     // pre
     BigUnsigned& operator++(){
          BigUnsigned one(1);
          *this += one;
          return *this;
     }

     // post
     BigUnsigned operator++(int dummy){
          BigUnsigned result (*this);
          BigUnsigned one(1);
          *this += one;
          return result;
     }

     explicit operator bool() const {
          return !(numVec.empty() || (numVec[0]==0 && numVec.size()==1));
     }
private:
     vector<int> numVec;
};
// Any functions that are not members and not friends should have
// prototypes here.
// All non-member functions should have their definitions after main.


BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs);



int main()
{
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

     // BigUnsigned first("9934");
     // BigUnsigned second("123");
     // // first += second;
     // second += first;
     // // cout << first << endl;
     // cout << second << endl;

     
    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;
    
    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;
     
    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b 
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;
    
    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;
         
    
    BigUnsigned big("987654321000");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    // How does this work?
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
   
} // main

ostream& operator<<(ostream& os, const BigUnsigned& rhs){
     for (size_t i = rhs.numVec.size(); i > 0; --i){
          os << rhs.numVec[i-1];
     }
     return os;
}


BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs){
     BigUnsigned result (lhs);
     result += rhs;
     return result;
}

bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs){
     if (lhs.numVec.size() != rhs.numVec.size()){
          return false;
     }
     for (size_t i = 0; i < lhs.numVec.size(); ++i){
          if (lhs.numVec[i] != rhs.numVec[i]){
               return false;
          }
     }
     return true;
}

bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs){
     if (lhs.numVec.size() < rhs.numVec.size()){
          return true;
     }
     else if (lhs.numVec.size() > rhs.numVec.size())
     {
          return false;
     }
     
     for (size_t i = lhs.numVec.size(); i > 0; --i){
          if (lhs.numVec[i-1] > rhs.numVec[i-1]){
     
               return false;
          }
          if (i == 1 && lhs.numVec[i-1] == rhs.numVec[i-1]){
               return false;
          }
          
          
     }
     return true;
}

bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs){
     return !(lhs == rhs);
}
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs){
     return !(lhs <= rhs);
}
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs){
     return !(lhs < rhs);
}
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs){
     return ((lhs < rhs) || (lhs == rhs));
}