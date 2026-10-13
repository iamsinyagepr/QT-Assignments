#ifndef STUDENT_H
#define STUDENT_H

#include "module.h"
#include <QList>

class Student
{

private:

    int studentNumber;
    QList<Module*> modules;

public:
    Student(int sn) {
        studentNumber = sn;
        modules =  QList<Module*>();
    }

    void setStudentNumber(int sn);
    double average() const;
    bool graduate() const;
    int getNumber() const;
    int checkModule(QString code) const;
    void addModule(QString code, double marks);
    QList<Module*> getModules() const;

};


#endif // STUDENT_H
