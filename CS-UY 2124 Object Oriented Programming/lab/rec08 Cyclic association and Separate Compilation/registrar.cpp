#include "registrar.h"
#include "course.h"
#include "student.h"

#include <iostream>
#include <string>
using namespace std;

namespace Fantasy{
    class Registrar;
// Registrar
Registrar :: Registrar(){}


bool Registrar :: addCourse(const string& newCourse){
    if (findCourse(newCourse) != courses.size()){ // found, already added
        return false;
    }
    Course* cptr = new Course(newCourse);
    courses.push_back(cptr);
    return true;
}

bool Registrar :: addStudent(const string& newStudent){
    if (findStudent(newStudent) != students.size()){
        return false;
    }
    Student* sptr = new Student(newStudent);
    students.push_back(sptr);
    return true;
}

// If the student and the course exist, then enroll the student.
bool Registrar :: enrollStudentInCourse(const string& studentName,
    const string& courseName){
    if (findStudent(studentName) == students.size() || 
    findCourse(courseName) == courses.size()){
        return false;
    }
    courses[findCourse(courseName)]->addStudent(students[findStudent(studentName)]);
    students[findStudent(studentName)]->addCourse(courses[findCourse(courseName)]);
    return true;
    }

// Unenroll the students from the course and remove the course
// from the Registrar.
bool Registrar :: cancelCourse(const string& courseName){
    size_t index = findCourse(courseName);
    if (index == courses.size()){
        return false;
    }
    cout << index;
    courses[index]->removeStudentsFromCourse();
    
    delete courses[index];
    courses[index] = nullptr;
    
    for (size_t j = index; j < courses.size() - 1; ++j){
        courses[j] = courses[j+1];
    }
    courses.pop_back();
    
    return true; 
}

// Get rid of everything!!!
void Registrar :: purge(){
    for (Course* courPtr : courses){
        delete courPtr;
    } 
    for (Student* stuPtr : students){
        delete stuPtr;
    }
    courses.clear();
    students.clear();

}



size_t Registrar :: findStudent(const string& stuName) const{
    for (size_t i = 0; i < students.size(); i++){
        if (students[i]->getName() == stuName){
            return i;
        }
    }
    return students.size();
}
size_t Registrar :: findCourse(const string& courName) const{
    for (size_t j = 0; j < courses.size(); j++){
        if (courses[j]->getName() == courName){
            return j;
        }
    }
    return courses.size();
}

ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Registrar's Report" << endl;
    os << "Courses: \n";
    for (Course* each : rhs.courses){
        os << *each << endl;
    }
    os << "Students: \n";
    for (Student* each1 : rhs.students){
        os << *each1 << endl;
    }
    
    return os;
}}