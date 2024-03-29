#include <string>
#include <iostream>

#include "roster.h"
#include "student.h"

static const std::string studentData[] = {
    "A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
    "A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
    "A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
    "A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
    "865484,Timothy,Baxendale,tbaxend@wgu.edu,25,28,29,30,SOFTWARE"
};

int main(int argc, char** argv)
{
    std::cout << "Scripting and Programming - Applications - C867" << std::endl;
    std::cout << "Written in C++" << std::endl;
    std::cout << "Student ID# 000865484\tTimothy Baxendale" << std::endl;

    Roster classRoster;
    for(const std::string& studentString : studentData) {
        classRoster.add(Student(studentString));
    }

    std::cout << std::endl << "====>         Student Data         <====" << std::endl;
    classRoster.printAll();

    std::cout << std::endl << "====>          Bad Emails          <====" << std::endl;
    classRoster.printInvalidEmails();

    std::cout << std::endl << "====>    Average Days in Course    <====" << std::endl;
    //loop through classRosterArray and for each element:
    for(int i = 0; i < classRoster.count(); ++i) {
        classRoster.printAverageDaysInCourse(classRoster[i].getStudentId());
    }
    
    std::cout << std::endl << "====> Students in Software Program <====" << std::endl;
    classRoster.printByDegreeProgram(DegreeProgram::SOFTWARE);
    classRoster.remove("A3");

    std::cout << std::endl << "====>  Student Roster without A3   <====" << std::endl;
    classRoster.printAll();

    std::cout << std::endl << "====>       Remove A3 Again        <====" << std::endl;
    classRoster.remove("A3");
    //expected: the above line should print a message saying such a student with this ID was not found.

    return 0;
}