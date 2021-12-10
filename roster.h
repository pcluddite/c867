#ifndef _ROSTER_H

#define _ROSTER_H

#include <initializer_list>
#include <iostream>
#include <string>

#include "degree.h"
#include "student.h"

class Roster
{
    private:
        size_t capacity;
        size_t size;
        // not sure why we are using an "an array of pointers", but that's what the assignment calls for
        Student** classRosterArray;

        void ensure_capacity(size_t newSize);
    public:
        Roster();
        Roster(const Roster& other);

        Roster(const std::initializer_list<Student>& students);
        ~Roster();

        void add(const std::string& studentID, const std::string& firstName, const std::string& lastName,
                 const std::string& emailAddress, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3,
                 DegreeProgram degreeprogram);
        void add(const Student& student);
        void remove(const std::string& studentID);
        size_t count() const;

        const Student* find(const std::string& studentId) const;
        const Student& operator[](size_t index) const;

        void trim_excess();

        void printAll() const;
        void printAverageDaysInCourse(const std::string& studentID) const;
        void printInvalidEmails() const;
        void printByDegreeProgram(DegreeProgram degreeProgram) const;
};

std::ostream& operator <<(std::ostream& out, const Roster& roster);

#endif