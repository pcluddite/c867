#ifndef _STUDENT_H

#define _STUDENT_H

#include <string>
#include <array>

#include "degree.h"

const size_t COURSE_COUNT = 3;

typedef std::array<int, COURSE_COUNT> COURSE_ARRAY;

class Student
{
    private:
        std::string _studentId;
        std::string _firstName;
        std::string _lastName;
        std::string _emailAddress;
        int _age;
        COURSE_ARRAY _courseDays;
        DegreeProgram _degreeProgram;
    public:
    
        Student() noexcept;
        Student(const Student& other) noexcept;
        Student(Student&& other) noexcept;
        explicit Student(const std::string& studentId, const std::string& firstName,
                         const std::string& lastName, const std::string& emailAddress,
                         int age, const COURSE_ARRAY& courseDays,
                         DegreeProgram degreeProgram) noexcept;
        explicit Student(const std::string& dataString);

        size_t courses() const;
        size_t course_days(size_t courseIdx) const;

        const std::string& getStudentId() const;
        const std::string& getFirstName() const;
        const std::string& getLastName() const;
        const std::string& getEmailAddress() const;
        const COURSE_ARRAY& getCourseDaysArray() const;
        int getAge() const;
        DegreeProgram getDegreeProgram() const;

        void setStudentId(const std::string&);
        void setFirstName(const std::string&);
        void setLastName(const std::string&);
        void setEmailAddress(const std::string&);
        void setCourseDaysArray(const COURSE_ARRAY&);
        void setAge(int);
        void setDegreeProgram(DegreeProgram);

        bool isValidEmail() const;

        void print() const;

        Student& operator =(const Student&) noexcept;
};

std::ostream& operator <<(std::ostream& out, const Student& student);

#endif