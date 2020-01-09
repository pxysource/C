#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student
{
private:
    const string _id;
    const string _name;
    double _score;
    static int _number;
    static double _total;
public:
    Student (string stu_id, string stu_name, double stu_score=0.0);
    ~Student ();
    const string id () const {return _id;}
    const string name () const {return _name;}
    double score () const {return _score;}
    void setScore (int stu_score=0);
    static double average ();
};

#endif // STUDENT_H
