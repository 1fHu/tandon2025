/*
  rec05.cpp
  Simon Hu
  Remember that the file you are to submit should be named rec05.cpp.
  And YOUR NAME should appear up here in the comment.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;



class Section {
private: 
  class TimeSlot{
    string labDate;
    int beginTime;
  public: 
    TimeSlot (const string& dateLab, int timeLab) 
     : labDate(dateLab), beginTime(timeLab) {}

    friend ostream& operator<<(ostream& os, const TimeSlot& rhs);

    
  };
  
  class StudentRecord{
    string name;
    vector<int> record;
    
  public:
    StudentRecord(const string& stuName) : name(stuName), record(14,-1) {}
    const string& getName() const {return name;} 
    friend ostream& operator<<(ostream& os, const StudentRecord& rhs);

    void editGrade(int grade, int week){
      record[week] = grade; 
    }
  };
  
public: 
friend ostream& operator<<(ostream& os, const Section& rhs);
friend ostream& operator<<(ostream& os, const TimeSlot& rhs);
friend ostream& operator<<(ostream& os, const StudentRecord& rhs);

// constructor
  Section(const string& labSection, const string& labDate, int number)
   : labSection(labSection), timeSlot(labDate,number) {}

  const string& getSection() const { return labSection;}

  void addStudent(const string& stuName){
    StudentRecord* stuPtr = new StudentRecord(stuName);
    allStudent.push_back( stuPtr );
  }

  void setStudentGrade(const string& stuName, int grade, int week){
    for ( StudentRecord* eachStudentptr : allStudent){
      if (eachStudentptr->getName() == stuName){ // find student
        eachStudentptr->editGrade(grade, week);
      }
    }
  }
  // copy control
  ~Section(){
    cout << "Section " << labSection << " is being deleted" << endl;
    for (StudentRecord* oneStudentptr : allStudent){
      cout << "Deleting " << oneStudentptr->getName() << endl;
      delete oneStudentptr;
    }
  }

  Section (const Section& anotherSection): labSection(labSection), timeSlot(anotherSection.timeSlot){
    for (const StudentRecord* otherStudentptr : anotherSection.allStudent){
      StudentRecord* new_record = new StudentRecord (*otherStudentptr);
      allStudent.push_back(new_record);
    }
  }

private:
  TimeSlot timeSlot;
  string labSection;
  vector<StudentRecord*> allStudent;

};


class LabWorker {
  public: 
  LabWorker (const string& wName) : workerName(wName) {}

  friend ostream& operator<<(ostream& os, const LabWorker& rhs);
  const string& getName() const { return workerName;} 

  void addSection(Section& oneSection){
    workedSection = &oneSection;
  }

  void addGrade(const string& stuName, int grade, int week){
    week -= 1;
    if (workedSection != nullptr){
      workedSection->setStudentGrade(stuName, grade, week);}
  }
  private:
  string workerName;
  Section* workedSection = nullptr;
};

// Test code
void doNothing(Section sec) { cout << sec << endl; }

ostream& operator<<(ostream& os, const Section& rhs){

  os << "Section: " << rhs.labSection << ", Time slot: ["
  << rhs.timeSlot << "], Students: " ;
  if (rhs.allStudent.size() == 0){
    os << "None" << endl;
  }
  else {
    os << endl;
    for (size_t i =0; i < rhs.allStudent.size(); ++i){
      os << *rhs.allStudent[i] << endl; // each student
    }
}
  return os;
}

ostream& operator<<(ostream& os, const Section::TimeSlot& rhs){
  os << "Day: " << rhs.labDate << ", Start time: ";  
  
    if (rhs.beginTime < 12)
    {
      os<< rhs.beginTime << "am";
    }
    else{
      return os << (rhs.beginTime - 12) << "pm";
    }   
  return os;
}

ostream& operator<<(ostream& os, const LabWorker& rhs){
  os << rhs.workerName; 
  if (rhs.workedSection == nullptr){
    os << " does not have a section";
  }
  else{
    os << " has " << *rhs.workedSection;
  }

  return os;
}

ostream& operator<<(ostream& os, const Section::StudentRecord& rhs){
  os << "Name: " << rhs.name << ", Grades: ";
  for (size_t i = 0; i < rhs.record.size(); ++i){
    os << rhs.record[i] << ' ';
  }
  
  return os;
}


int main()
{

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;

} // main
