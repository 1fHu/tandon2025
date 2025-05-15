/*
  rec08_start.cpp
  Starter Code for required functionality

  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.
  
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;


class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
}; // Course



class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
}; // Student

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string&);
    // Creates a new student, if none with that name
    bool addStudent(const string&);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
}; // Registrar





int main()
{

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main

// Courses
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
}