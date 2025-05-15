#include "course.h"
#include "student.h"
#include <iostream>
#include <string>
using namespace std;
namespace Fantasy
{class Course;

Course :: Course(const string& courseName) : name(courseName){}
const string& Course::getName() const { return name; }

bool Course::addStudent(Student* sptr){
    for (Student* each : students){
        if (each == sptr){
            return false;
        }
    }
    students.push_back(sptr);
    return true;
}

void Course::removeStudentsFromCourse(){
    for (size_t i = 0; i < students.size(); i ++){
        
        students[i]->removedFromCourse(this);
        // cout <<"h";
    }
    students.clear();
}
ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name << ": ";
    if (rhs.students.size() == 0){
        os << "No students";
    }
    else{
        for (size_t i = 0; i < rhs.students.size(); ++i){
            os << rhs.students[i]->getName() << ' ';
        }
    }
    return os;
}}