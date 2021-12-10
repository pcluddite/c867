#include <algorithm>
#include <iostream>

#include "roster.h"

static const int INITIAL_CAPACITY = 2;

// creates an array of pointers that are laid out in memory contiguously
template<class T>
static T** init_contiguous_array_ptr(size_t len)
{
    // initialize an array of pointers
    T** lpPtrArr = new T*[len];

    // initialize an array of T objects
    T* lpArr = new T[len];

    // loop through the array of T objects and assign the pointer to
    // each element to the lpPtrArr array
    for (size_t idx = 0; idx < len; ++idx) {
        lpPtrArr[idx] = &lpArr[idx];
    }

    // return the array of pointers
    return lpPtrArr;
}

// copies the elements from one contiguous array to another
template<class T>
static void copy_contiguous_array_ptr(T** lpSrc, T** lpDest, size_t size)
{
    std::copy(*lpSrc, lpSrc[size - 1] + 1, *lpDest);
}

Roster::Roster()
    : capacity(INITIAL_CAPACITY), size(0)
{
    classRosterArray = init_contiguous_array_ptr<Student>(capacity);
}

Roster::Roster(const Roster& other)
    : size(other.size)
{
    if (other.size == 0) {
        capacity = INITIAL_CAPACITY;
        classRosterArray = init_contiguous_array_ptr<Student>(capacity);
    }
    else {
        capacity = other.size;
        classRosterArray = init_contiguous_array_ptr<Student>(capacity);
        copy_contiguous_array_ptr(other.classRosterArray, classRosterArray, other.size);
    }
}

Roster::Roster(const std::initializer_list<Student>& students)
    : capacity(students.size()), size(students.size())
{
    classRosterArray = init_contiguous_array_ptr<Student>(capacity);
    std::copy(students.begin(), students.end(), *classRosterArray);
}

Roster::~Roster()
{
    destroy_roster();
}

void Roster::ensure_capacity(size_t newSize)
{
    if (newSize >= capacity) {
        capacity = newSize * 2;
        Student** newArray = init_contiguous_array_ptr<Student>(capacity);
        copy_contiguous_array_ptr(classRosterArray, newArray, size);
        destroy_roster();
        classRosterArray = newArray;
    }
}

void Roster::destroy_roster()
{
    // memory was initilized as 2 arrays, which both need to be destroyed.
    // the first element of classRosterArray should point to an array of
    // Student objects. The classRosterArray pointer itself points to the
    // pointer of that contiguous block
    delete[] *classRosterArray;
    delete[] classRosterArray;
    classRosterArray = nullptr;
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
                std::move(classRosterArray[i + 1], classRosterArray[size - 1] + 1, classRosterArray[i]);
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
        copy_contiguous_array_ptr(classRosterArray, newArray, size);
        destroy_roster();
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
    if (lpStudent == nullptr) {
        std::cout << "NA" << std::endl;
    }
    else {
        double avg = 0;
        size_t sum = 0;
        for (int i = 0; i < lpStudent->courses(); ++i) {
            sum += lpStudent->course_days(i);
        }
        avg = sum / (double)lpStudent->courses();
        std::cout << avg << std::endl;
    }
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