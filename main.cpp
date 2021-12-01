#include <string>
#include <iostream>

#include "student.h"

static const std::string studentData[] = {
    "A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
    "A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
    "A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
    "A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
    "A5,Timothy,Baxendale,tbaxend@wgu.edu,25,28,29,30,SOFTWARE"
};

int main(int argc, char** argv)
{
    for(const std::string& studentRow : studentData) {
        Student s(studentRow);
        std::cout << s << std::endl;
    }
    return 0;
}