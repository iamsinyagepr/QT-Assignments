#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "student.h"
#include <QList>

class StudentContainer
{

private:
    QList<Student*>* students;

public:

    StudentContainer(QList<Student*>* list);
    ~StudentContainer();

    void addStudent(int studentNumber, QString code, double marks);

    QList<Student*>* getStudents() const;
    Student* getStudent(int index) const;

    int verifyStudent(int studentNumber) const;
    int getStudentCount() const;


};

class StudentList {
private:
    static StudentContainer* onlyInstance;
    StudentList();

public:
    StudentList(const StudentList&) = delete;
    StudentList& operator=(const StudentList&) = delete;


    static StudentList& getInstance();
    StudentContainer* getStudentInstance();
};

#endif // STUDENTLIST_H
