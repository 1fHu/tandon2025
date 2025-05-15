This file contains real exam questions in 2025 spring final Exam: 

question 1: 
who has great contrubution to computer science / algorithm and computation?

answer: Alan Turing


one MCQ:
what is the result of following code: 

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


Small Code writing summary:
STL
Using iterator in vector class
write an iterator for any class 
template algorithm

Recursion

Node add/drop


Final question: 
Write a musical school code 

class School 
class Instructor (abstract class)
class GuitarInstructor : public Instructor
class StringInstructor : public Instructor

School hires Instructor
Instructor can play sound (output operator)

