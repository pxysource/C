#include "student.h"

int main()
{
    Student s1("1", "pxy");
    s1.setScore (95);
    Student s2("2", "zhangshan");
    s2.setScore (90);
    {
        //定义局部的对象，离开这个代码块，就被析构
        Student s3("3", "lisi", 88);
        s1.average();
        s2.average();
        s3.average();
    }

    s1.average();
    s2.average();

    return 0;
}
