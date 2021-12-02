#ifndef _STUDENT_H

#define _STUDENT_H

#include <string>
#include <array>

const int DEFAULT_COURSE_COUNT = 3;

class Student
{
    private:
        std::string _studentId;
        std::string _firstName;
        std::string _lastName;
        std::string _emailAddress;
        int _age;
        std::array<int, DEFAULT_COURSE_COUNT> _courseDays;
        std::string _degreeProgram;
    public:
    
        Student();
        Student(const Student& other);
        explicit Student(const std::string& dataString);

        size_t courses() const;
        size_t course_days(size_t courseIdx) const;

        const std::string& getStudentId() const;
        const std::string& getFirstName() const;
        const std::string& getLastName() const;
        const std::string& getEmailAddress() const;
        int getAge() const;
        const std::string& getDegreeProgram() const;

        void setStudentId(const std::string&);
        void setFirstName(const std::string&);
        void setLastName(const std::string&);
        void setEmailAddress(const std::string&);
        void setAge(int);
        void setDegreeProgram(const std::string&);

        void print() const;
};

std::ostream& operator <<(std::ostream& out, const Student& student);

#endif