#ifndef _STUDENT_H

#define _STUDENT_H

#include <string>
#include <array>

const int DEFAULT_COURSE_COUNT = 3;

class Student
{
    private:
        std::array<int, DEFAULT_COURSE_COUNT> _courseDays;
    public:
        std::string StudentId;
        std::string FirstName;
        std::string LastName;
        std::string EmailAddress;
        int Age;
        std::string DegreeProgram;
    
        Student();
        Student(const Student& other);
        explicit Student(const std::string& dataString);

        size_t courses() const;
        size_t course_days(size_t courseIdx) const;
};

std::ostream& operator <<(std::ostream& out, const Student& student);

#endif