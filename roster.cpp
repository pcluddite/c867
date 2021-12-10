#include <algorithm>

#include "roster.h"

static const int INITIAL_CAPACITY = 10;

template<class T>
static T** init_contiguous_array_ptr(size_t len)
{
    T** lpPtrArr = new T*[len];
    T* lpArr = new T[len];
    for (size_t idx = 0; idx < len; ++idx) {
        lpPtrArr[idx] = &lpArr[idx];
    }
    return lpPtrArr;
}

Roster::Roster()
    : capacity(INITIAL_CAPACITY), size(0)
{
    classRosterArray = init_contiguous_array_ptr<Student>(capacity);
}

Roster::Roster(const Roster& other)
    : capacity(other.size), size(other.size)
{
    classRosterArray = init_contiguous_array_ptr<Student>(capacity);
    std::copy(other.classRosterArray[0], other.classRosterArray[other.size], *classRosterArray);
}

Roster::Roster(const std::initializer_list<Student>& students)
    : capacity(students.size()), size(students.size())
{
    classRosterArray = init_contiguous_array_ptr<Student>(capacity);
    std::copy(students.begin(), students.end(), *classRosterArray);
}

Roster::~Roster()
{
    delete[] *classRosterArray;
    delete[] classRosterArray;
}

void Roster::ensure_capacity(size_t newSize)
{
    while (newSize >= capacity) {
        Student** newArray = init_contiguous_array_ptr<Student>(capacity * 2);
        std::copy(*classRosterArray, classRosterArray[capacity], *newArray);
        delete[] *classRosterArray;
        delete[] classRosterArray;
        capacity *= 2;
        classRosterArray = newArray;
    }
}

void Roster::add(const std::string& studentID, const std::string& firstName, const std::string& lastName,
                 const std::string& emailAddress, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3,
                 DegreeProgram degreeprogram)
{
    add(Student(studentID, firstName, lastName, emailAddress, age, { daysInCourse1, daysInCourse2, daysInCourse3 }, degreeprogram));
}

void Roster::add(const Student& student)
{
    ensure_capacity(size);
    *classRosterArray[size++] = student;
}

void Roster::remove(const std::string& studentID)
{
    for(size_t i = 0; i < size; ++i) {
        if (classRosterArray[i]->getStudentId() == studentID) {
            if (i + 1 < size)
                std::move(classRosterArray[i + 1], classRosterArray[size], classRosterArray[i]);
            --size;
            return;
        }
    }
    std::cout << "No student with id " << studentID << " was found" << std::endl;
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
        Student** newArray = init_contiguous_array_ptr<Student>(size);
        std::copy(*classRosterArray, classRosterArray[size], *newArray);
        delete[] *classRosterArray;
        delete[] classRosterArray;
        capacity = size;
        classRosterArray = newArray;
    }
}

void Roster::printAll() const
{
    for(size_t i = 0; i < size; ++i) {
        classRosterArray[i]->print();
    }
}

void Roster::printAverageDaysInCourse(const std::string& studentID) const
{
    const Student* lpStudent = find(studentID);
    double avg = 0;
    if (lpStudent != nullptr) {
        size_t sum = 0;
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