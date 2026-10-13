#ifndef STUDENTSERIALIZER_H
#define STUDENTSERIALIZER_H

#include "student.h"

#include <QDomDocument>
#include <QDomElement>

class StudentSerializer
{

private:
    QDomDocument doc;
    QDomElement root;

public:
    StudentSerializer();

    void saveToXML();
    void writeXML(Student* student /*new student data*/);
    void writeXML(Student* student /*student data*/, int index /*student index*/);
    QList<Student*> *readXML();
};

#endif // STUDENTSERIALIZER_H
