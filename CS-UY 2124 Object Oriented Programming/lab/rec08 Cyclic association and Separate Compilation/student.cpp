#include "student.h"
#include "course.h"
#include <iostream>
#include <string>
using namespace std;

namespace Fantasy
{class Course;

// Students
Student :: Student(const string& name) : name(name) {}
const string& Student :: getName() const { return name; }

bool Student :: addCourse(Course* cptr){
    for (Course* each : courses){
        if (each == cptr){
            return false;
        }
    }
    courses.push_back(cptr);
    return true;
}

// Student method needed by Course::removeStudentsFromCourse
void Student :: removedFromCourse(Course* enrolledCourse){
    for (size_t i = 0; i < courses.size(); ++i){
        if (courses[i] == enrolledCourse){
            for (size_t j = i; j < courses.size() - 1; ++j){
                courses[j] = courses[j+1];  
            }
            courses.pop_back();
            break;
        }
    }
}
ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.name << ": "; 
    if (rhs.courses.size() == 0){
        os << "No Courses";
    }
    else{
        for (size_t i = 0; i < rhs.courses.size(); ++i){
            os << rhs.courses[i]->getName() << ' ';
        }
    }
    return os;
}}