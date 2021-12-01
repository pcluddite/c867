#include <string>
#include <iostream>
#include <exception>

#include "student.h"

Student::Student()
{
}

Student::Student(const Student& other)
    : StudentId(other.StudentId),
      FirstName(other.FirstName),
      LastName(other.LastName),
      DegreeProgram(other.DegreeProgram),
      _courseDays(other._courseDays)
{
    Age = other.Age;
}

static size_t NextToken(const std::string& szFull, std::string& token, size_t nStartIdx)
{
    size_t nEndIdx = szFull.find(',', nStartIdx);
    token = szFull.substr(nStartIdx, nEndIdx - nStartIdx);
    return nEndIdx + 1;
}

Student::Student(const std::string& dataString)
{
    int idx = 0;
    idx = NextToken(dataString, StudentId   , idx);
    idx = NextToken(dataString, FirstName   , idx);
    idx = NextToken(dataString, LastName    , idx);
    idx = NextToken(dataString, EmailAddress, idx);
    
    std::string szAge;
    idx = NextToken(dataString, szAge, idx);
    Age = std::stoi(szAge);

    for(size_t i = 0; i < _courseDays.size(); ++i) {
        std::string szDays;
        idx = NextToken(dataString, szDays, idx);
        _courseDays[i] = std::stoi(szDays);
    }

    idx = NextToken(dataString, DegreeProgram, idx);
}

size_t Student::courses() const
{
    return _courseDays.size();
}

size_t Student::course_days(size_t courseIdx) const
{
    return _courseDays[courseIdx];
}

std::ostream& operator <<(std::ostream& out, const Student& student)
{
    out << student.StudentId    << ',';
    out << student.FirstName    << ',';
    out << student.LastName     << ',';
    out << student.EmailAddress << ',';
    out << student.Age          << ',';
    for(int i = 0; i < student.courses(); ++i) {
        out << student.course_days(i) << ',';
    }
    out << student.DegreeProgram;
    return out;
}