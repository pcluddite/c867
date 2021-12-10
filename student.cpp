#include <string>
#include <iostream>
#include <exception>

#include "student.h"

Student::Student() noexcept
    : _studentId(""),
      _firstName(""),
      _lastName(""),
      _emailAddress(""),
      _degreeProgram(),
      _courseDays({0, 0, 0}),
      _age(0)
{
}

Student::Student(const Student& other) noexcept
    : _studentId(other.getStudentId()),
      _firstName(other.getFirstName()),
      _lastName(other.getLastName()),
      _emailAddress(other.getEmailAddress()),
      _degreeProgram(other.getDegreeProgram()),
      _courseDays(other._courseDays),
      _age(other.getAge())
{
}

Student::Student(Student&& other) noexcept
    : _studentId(std::move(other._studentId)),
      _firstName(std::move(other._firstName)),
      _lastName(std::move(other._lastName)),
      _emailAddress(std::move(other._emailAddress)),
      _degreeProgram(std::exchange(other._degreeProgram, DegreeProgram::NONE)),
      _courseDays(std::move(other._courseDays)),
      _age(std::exchange(other._age, 0))
{
}

Student::Student(const std::string& studentId, const std::string& firstName,
                 const std::string& lastName, const std::string& emailAddress,
                 int age, const std::array<int,DEFAULT_COURSE_COUNT>& courseDays,
                 DegreeProgram degreeProgram) noexcept
    : _studentId(studentId),
      _firstName(firstName),
      _lastName(lastName),
      _emailAddress(emailAddress),
      _age(age),
      _courseDays(courseDays),
      _degreeProgram(degreeProgram)
{   
}

static size_t NextToken(const std::string& szFull, std::string& token, size_t nStartIdx)
{
    size_t nEndIdx = szFull.find(',', nStartIdx);
    token = szFull.substr(nStartIdx, nEndIdx - nStartIdx);
    return nEndIdx + 1;
}

Student::Student(const std::string& dataString)
    : _degreeProgram(DegreeProgram::NONE)
{
    size_t idx = 0;
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

    std::string szDegreeProgram;
    idx = NextToken(dataString, szDegreeProgram, idx);
    if (szDegreeProgram == "SECURITY") {
        _degreeProgram = DegreeProgram::SECURITY;
    }
    else if (szDegreeProgram == "NETWORK") {
        _degreeProgram = DegreeProgram::NETWORK;
    }
    else if (szDegreeProgram == "SOFTWARE") {
        _degreeProgram = DegreeProgram::SOFTWARE;
    }
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

DegreeProgram Student::getDegreeProgram() const
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

void Student::setDegreeProgram(DegreeProgram degreeProgram)
{
    _degreeProgram = degreeProgram;
}

bool Student::isValidEmail() const
{
    int atCount = 0, dotCount = 0, spaceCount = 0;
    for(auto it = _emailAddress.begin(); it != _emailAddress.end(); ++it) {
        if (*it == '@') {
            ++atCount;
        }
        else if (*it == '.') {
            ++dotCount;
        }
        else if (*it == ' ') {
            ++spaceCount;
        }
    }
    return atCount == 1 && dotCount > 0 && spaceCount == 0;
}

void Student::print() const
{
    std::cout << *this << std::endl;
}

Student& Student::operator=(const Student& other) noexcept
{
    if (&other == this)
        return *this;
    _studentId     = other._studentId;
    _firstName     = other._firstName;
    _lastName      = other._lastName;
    _emailAddress  = other._emailAddress;
    _age           = other._age;
    _courseDays    = other._courseDays;
    _degreeProgram = other._degreeProgram;
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Student& student)
{
    out << student.getStudentId() << '\t';
    out << "First Name: " << student.getFirstName()    << '\t';
    out << "Last Name: "  << student.getLastName()     << '\t';
    out << "Age: "        << student.getAge()          << '\t';
    out << "daysInCourse: {";
    for(size_t i = 0; i < student.courses(); ++i) {
        out << ' ' << student.course_days(i);
        if (i < student.courses() - 1) {
            out << ',';
        }
    }
    out << " }\t";
    out << "Degree Program: ";
    switch(student.getDegreeProgram()) {
        case DegreeProgram::SECURITY: out << "Security"; break;
        case DegreeProgram::NETWORK:  out << "Network";  break;
        case DegreeProgram::SOFTWARE: out << "Software"; break;
        default: out << "N/A"; break;
    }
    return out;
}