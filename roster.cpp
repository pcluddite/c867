#include <algorithm>

#include "roster.h"

static const int INITIAL_CAPACITY = 10;

Roster::Roster()
    : capacity(INITIAL_CAPACITY), size(0)
{
    classRosterArray = new Student*[capacity];
}

Roster::Roster(const Roster& other)
    : capacity(other.count()), size(other.count())
{
    classRosterArray = new Student*[capacity];
    for(size_t i = 0; i < other.size; ++i) {
        classRosterArray[i] = new Student(*(other.classRosterArray[i]));
    }
}

Roster::Roster(const std::initializer_list<Student>& students)
    : capacity(students.size()), size(students.size())
{
    classRosterArray = new Student*[capacity];
    size_t i = 0;
    for(auto it = students.begin(); it != students.end(); ++it) {
        classRosterArray[i++] = new Student(*it);
    }
}

Roster::~Roster()
{
    for(size_t i = 0; i < size; ++i) {
        delete classRosterArray[i];
    }
    delete[] classRosterArray;
}

void Roster::ensure_capacity(size_t newSize)
{
    while (newSize >= capacity) {
        Student** newArray = new Student*[capacity * 2];
        std::copy(classRosterArray, classRosterArray + capacity, newArray);
        delete[] classRosterArray;
        capacity *= 2;
        classRosterArray = newArray;
    }
}

void Roster::add(Student* lpStudent)
{
    ensure_capacity(++size);
    classRosterArray[size - 1] = lpStudent;
}

void Roster::add(const std::string& studentID, const std::string& firstName, const std::string& lastName,
                 const std::string& emailAddress, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3,
                 DegreeProgram degreeprogram)
{
    Student* lpStudent = new Student(studentID, firstName, lastName, emailAddress, age,
                                     { daysInCourse1, daysInCourse2, daysInCourse3 },
                                     degreeprogram);
    add(lpStudent);
}

void Roster::add(const Student& student)
{
    add(new Student(student));
}

void Roster::remove(const std::string& studentID)
{
    for(size_t i = 0; i < size; ++i) {
        if (classRosterArray[i]->getStudentId() == studentID) {
            delete classRosterArray[i];
            for(size_t j = i + 1; i < size; ++j) {
                classRosterArray[j - 1] = classRosterArray[j];
            }
            --size;
            break;
        }
    }
}

size_t Roster::count() const
{
    return size;
}

const Student& Roster::operator[](size_t index) const
{
    return *classRosterArray[index];
}

const Student* Roster::find(const std::string& studentId) const
{
    for(size_t i = 0; i < size; ++i) {
        if (classRosterArray[i]->getStudentId() == studentId) {
            return classRosterArray[i];
        }
    }
    return nullptr;
}

void Roster::trim_excess()
{
    if (size < capacity) {
        Student** newArray = new Student*[size];
        std::copy(classRosterArray, classRosterArray + size, newArray);
        delete[] classRosterArray;
        capacity = size;
        classRosterArray = newArray;
    }
}

void Roster::printAll() const
{
    for(size_t i = 0; i < size; ++i) {
        std::cout << *classRosterArray[i] << std::endl;
    }
}

void Roster::printAverageDaysInCourse(const std::string& studentID) const
{
    const Student* lpStudent = find(studentID);
    double avg = 0;
    if (lpStudent != nullptr) {
        long int sum = 0;
        for (int i = 0; i < lpStudent->courses(); ++i) {
            sum += lpStudent->course_days(i);
        }
        avg = sum / (double)lpStudent->courses();
    }
    std::cout << avg << std::endl;
}

void Roster::printInvalidEmails() const
{
    for(size_t i = 0; i < size; ++i) {
        if (!classRosterArray[i]->isValidEmail()) {
            std::cout << classRosterArray[i]->getEmailAddress() << std::endl;
        }
    }
}

void Roster::printByDegreeProgram(DegreeProgram degreeProgram) const
{
    for(size_t i = 0; i < size; ++i) {
        if (classRosterArray[i]->getDegreeProgram() == degreeProgram) {
            std::cout << *classRosterArray[i] << std::endl;
        }
    }
}