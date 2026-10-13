#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "student.h"
#include "studentserializer.h"
#include <QList>

class StudentContainer
{

private:
    StudentSerializer* serializer;
    QList<Student*>* students;
public:

    StudentContainer();
    ~StudentContainer();



    void addStudent(int studentNumber, QString code, double marks);

    QList<Student*>* getStudents() const;
    Student* getStudent(int index) const;
    StudentSerializer* getSerializer() ;

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
