#include "student.h"


Student::Student() : surname(""), name(""), cathedra(""), group(""),
    avgMark(0), semester(0), year(0) {};
Student::~Student(){}
Student::Student(string surname, string name, string cathedra, string group, double avgMark, int semester, int year) : surname(surname), name(name), cathedra(cathedra), group(group),
    avgMark(avgMark), semester(semester), year(year) {};
Student::Student(const Student& copy)
{
    surname = copy.surname;
    name = copy.name;
    cathedra = copy.cathedra;
    group = copy.group;
    avgMark = copy.avgMark;
    semester = copy.semester;
    year = copy.year;
}
string Student::getSurname() const
{
    return surname;
}
void Student::setSurname(string tmp)
{
    surname = tmp;
}
string Student::getName() const
{
    return name;
}

void Student::setName(string tmp)
{
    name = tmp;
}
string Student::getCathedra()
{
    return cathedra;
}
void Student::setCathedra(string tmp)
{
    cathedra = tmp;
}
string Student::getGroup() const
{
    return group;
}
void Student::setGroup(string tmp)
{
    group = tmp;
}
double Student::getAvgMark() const
{
    return avgMark;
}
void Student::setAvgMark(double tmp)
{
    avgMark = tmp;
}
int Student::getSemester() const
{
    return semester;
}
void Student::setSemester(int tmp)
{
    semester = tmp;
}
int Student::getYear() const
{
    return year;
}
void Student::setYear(int tmp)
{
    year = tmp;
}

void Student::show()
{
    cout << "surname: " << surname << endl << "name: " << name << endl << "cathedra: "\
         << cathedra << endl << "group:" << group << endl << "avgMark: " << avgMark << endl << "semester: " << semester << endl << "year: " << year << endl;
}

Student& Student::operator=(const Student& source){
    name = source.name;
    surname = source.surname;
    year = source.year;
    semester = source.semester;
    group = source.group;
    cathedra = source.cathedra;
    avgMark = source.avgMark;
    return *this;
}

