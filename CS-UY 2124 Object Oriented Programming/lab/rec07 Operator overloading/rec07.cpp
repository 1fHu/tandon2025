
/*
  rec07.cpp
  CS2124
  Simon Hu
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);


// Put your Rational class here.
class Rational {
    // op<< as a friend
    friend ostream& operator<<(ostream& os, const Rational& rhs){
        os << rhs.numerator << '/' << rhs.denominator;
        return os;
    }

    // op>> as a friend
    friend istream& operator>>(istream& in, Rational& rhs){
        int iniNumerator;
        int iniDenominator;
        char slash;
        in >> iniNumerator >> slash >> iniDenominator;

        if (slash != '/'){
            cout << "wrong input" <<endl;
            return in;
        }
        rhs.numerator = iniNumerator;
        rhs.denominator = iniDenominator;
        rhs.normalize();
    
        return in;
    }

    // op== as a friend
    friend bool operator==(const Rational& lhs, const Rational& rhs);

    //op< as a friend
    friend bool operator<(const Rational& lhs, const Rational& rhs);

public: 
    Rational (int aNumerator = 0, int aDenominator = 1) 
    : numerator (aNumerator), denominator(aDenominator) {
        normalize();
    }

    Rational& operator+=(const Rational& rhs){
        int finalNumerator = numerator * rhs.denominator + 
        rhs.numerator * denominator;

        int finalDenomiator = denominator * rhs.denominator;

        numerator = finalNumerator;
        denominator = finalDenomiator;
        normalize();
        return *this;
    }

    
    // pre-increment ++r
    Rational& operator++(){
        numerator += denominator;
        
        return *this;
    }

    // post-increment r++
    Rational operator++(int dummy){
        Rational result (*this);
        numerator += denominator;
        // normalize();
        return result;
    }

    // operator bool()
    explicit operator bool() const {
        return !(numerator == 0);
    }

private:
    int numerator;
    int denominator;
    void normalize(){
        int negative = 1;
        if ((numerator < 0) && (denominator < 0)){
            numerator *= -1;
            denominator *= -1;
        }
        else if ( denominator < 0){
            negative *= -1;
            denominator *= -1;
        }
        else if (numerator < 0){
            negative *= -1;
            numerator *= -1;
        }

        int gcd = greatestCommonDivisor(numerator, denominator);

        numerator /= gcd;
        numerator *= negative;
        denominator /= gcd;
    }
};

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& lhs);
Rational operator--(Rational& lhs, int dummy);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    
    cout << "a += b: " << (a += b) << endl;	// Implement += as a member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but NOT as a friend
    cout << "a + one: " << (a + one) << endl;
    
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    //
    // PLEASE CHECK OUT NOW
    //
    
    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why SHOULDN'T it compile?
    // cout << "a-- -- = " << (a-- --) << endl;
    // cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
    /**/
} // main

// parameter: x, y be positive integer
// return: non-zero
int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
} // greatestCommonDivisor

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result (lhs); // copy lhs
    result += rhs;
    return result;
}

bool operator==(const Rational& lhs, const Rational& rhs){
    return  (lhs.denominator == rhs.denominator 
        && lhs.numerator == rhs.numerator);
}

bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator * rhs.denominator < 
        lhs.denominator * rhs.numerator);
}

// pre decrement --r
Rational& operator--(Rational& lhs){
    return (lhs += -1);
}

// post decrement r --
Rational operator--(Rational& lhs, int dummy){
    Rational result = lhs;
    lhs += -1;
    return result;
}

bool operator<=(const Rational& lhs, const Rational& rhs){
    return ((lhs < rhs) || (lhs == rhs));
} 

bool operator>(const Rational& lhs, const Rational& rhs){
    return !(lhs <= rhs);
}
bool operator>=(const Rational& lhs, const Rational& rhs){
    return !(lhs < rhs);
}