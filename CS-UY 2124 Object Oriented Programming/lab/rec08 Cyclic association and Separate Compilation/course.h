#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
namespace Fantasy
{class Student;

class Course {
    friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const std::string& courseName);
    const std::string& getName() const;
    bool addStudent(Student*);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse(); 

private:
    std::string name;
    std::vector<Student*> students;
}; // Course
}


#endif