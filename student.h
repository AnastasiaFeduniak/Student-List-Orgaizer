#ifndef STUDENT_H
#define STUDENT_H
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student
{
private:
    string surname;
    string name;
    string cathedra;
    string group;
    double avgMark;
    int semester;
    int year;
public:
    ~Student();
    Student();
    Student(string surname, string name, string cathedra, string group, double avgMark, int semester, int year);
    Student(const Student& copy);
    string getSurname() const;
    void setSurname(string tmp);
    string getName() const;
    void setName(string tmp);
    string getCathedra();
    void setCathedra(string tmp);
    string getGroup() const;
    void setGroup(string tmp);
    double getAvgMark() const;
    void setAvgMark(double tmp);
    int getSemester() const;
    void setSemester(int tmp);
    int getYear() const;
    void setYear(int tmp);
    void show();
    friend istream& operator >> (istream& in, Student& inS)
    {
        char tmp;
        in >> inS.surname >> tmp >> inS.name >> tmp >> inS.cathedra >> tmp >>\
        inS.group >> tmp >> inS.avgMark >> tmp >> inS.semester >> tmp >> inS.year;
        return in;
    }
    friend ostream& operator << (ostream& out, const Student& outS)
    {
        out << outS.surname << " | " << outS.name << " | " << outS.cathedra << " | " << outS.group << " | " <<outS.avgMark
            << " | " << outS.semester << " | " << outS.year << endl;
        return out;
    }
    Student& operator=(const Student& source);
};
#endif // STUDENT_H
