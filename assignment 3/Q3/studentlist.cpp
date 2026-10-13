#include "studentlist.h"

StudentContainer* StudentList::onlyInstance = nullptr; // Global initialization to null

StudentList& StudentList::getInstance()  {

    static StudentList instance;
    return instance;

}

StudentList::StudentList() {
    QList<Student*>* rawList = new QList<Student*>();
    onlyInstance = new StudentContainer(rawList);
}

StudentContainer* StudentList::getStudentInstance() {
    return onlyInstance;
}

StudentContainer::StudentContainer(QList<Student*>* list) : students(list) {
    qDebug() << list;
}
StudentContainer::~StudentContainer() {
    if (students) {
        qDeleteAll(*students);
        delete students;
    }
}

void StudentContainer::addStudent(int sn, QString code, double marks)
{

    int exists = verifyStudent(sn);


    if(exists < 0) {
        Student* student = new Student(sn);
        student->addModule(code, marks);
        students->append(student);
        return;
    }


    Student* student = students->at(exists);
    student->addModule(code, marks);
    // student->addModule();

}

QList<Student*>* StudentContainer::getStudents() const {
    return students;
}

Student* StudentContainer::getStudent(int index) const
{
    return students->at(index);
}

int StudentContainer::verifyStudent(int studentNumber) const {

    int i = -1;
    for (Student* student : *students) {
        ++i;
        if(student->getNumber() == studentNumber) {
            return i;
        }
    }
    return  -1;
}

int StudentContainer::getStudentCount() const {
    return students->size();
}