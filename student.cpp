#include <string>
#include <iostream>
#include <exception>

#include "student.h"

Student::Student()
{
}

Student::Student(const Student& other)
    : _studentId(other.getStudentId()),
      _firstName(other.getFirstName()),
      _lastName(other.getLastName()),
      _degreeProgram(other.getDegreeProgram()),
      _courseDays(other._courseDays),
      _age(other.getAge())
{
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
    idx = NextToken(dataString, _studentId   , idx);
    idx = NextToken(dataString, _firstName   , idx);
    idx = NextToken(dataString, _lastName    , idx);
    idx = NextToken(dataString, _emailAddress, idx);
    
    std::string szAge;
    idx = NextToken(dataString, szAge, idx);
    _age = std::stoi(szAge);

    for(size_t i = 0; i < _courseDays.size(); ++i) {
        std::string szDays;
        idx = NextToken(dataString, szDays, idx);
        _courseDays[i] = std::stoi(szDays);
    }

    idx = NextToken(dataString, _degreeProgram, idx);
}

size_t Student::courses() const
{
    return _courseDays.size();
}

size_t Student::course_days(size_t courseIdx) const
{
    return _courseDays[courseIdx];
}

const std::string& Student::getStudentId() const
{
    return _studentId;
}

const std::string& Student::getFirstName() const
{
    return _firstName;
}

const std::string& Student::getLastName() const
{
    return _lastName;
}

const std::string& Student::getEmailAddress() const
{
    return _emailAddress;
}

int Student::getAge() const
{
    return _age;
}

const std::string& Student::getDegreeProgram() const
{
    return _degreeProgram;
}

void Student::setStudentId(const std::string& studentId)
{
    _studentId = studentId;
}

void Student::setFirstName(const std::string& firstName)
{
    _firstName = firstName;
}

void Student::setLastName(const std::string& lastName)
{
    _lastName = lastName;
}

void Student::setEmailAddress(const std::string& emailAddress)
{
    _emailAddress = emailAddress;
}

void Student::setAge(int age)
{
    _age = age;
}

void Student::setDegreeProgram(const std::string& degreeProgram)
{
    _degreeProgram = degreeProgram;
}

std::ostream& operator <<(std::ostream& out, const Student& student)
{
    out << student.getStudentId()    << ',';
    out << student.getFirstName()    << ',';
    out << student.getLastName()     << ',';
    out << student.getEmailAddress() << ',';
    out << student.getAge()          << ',';
    for(int i = 0; i < student.courses(); ++i) {
        out << student.course_days(i) << ',';
    }
    out << student.getDegreeProgram();
    return out;
}

void Student::print() const
{
    std::cout << *this << std::endl;
}