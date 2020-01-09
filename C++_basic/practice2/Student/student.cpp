#include "student.h"

int Student::_number = 0;
double Student::_total = 0.0;

Student::Student(string stu_id, string stu_name, double stu_score)
    :_id(stu_id), _name(stu_name)
{
    _score = stu_score;
    _number++;
    _total += _score;
    cout << "adding a new student..." << endl;
}

Student::~Student()
{
    _number--;
    _total -= _score;
    cout << "delete a student." << endl;
}

void Student::setScore(int stu_score)
{
    _total -= _score;
    _score = stu_score;
    _total += _score;
}

double Student::average()
{
    double avrg = _total / _number;
    cout << "average: " << avrg << endl;
    return avrg;
}
