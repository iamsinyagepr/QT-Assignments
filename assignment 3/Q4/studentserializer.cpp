#include "studentserializer.h"
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>

const QString& filePath = "students.xml";


StudentSerializer::StudentSerializer() {
    root = doc.createElement("StudentList");
    doc.appendChild(root);
}


QDomElement createXMLStudent(QDomDocument &doc, Student *student) {

    QDomElement item = doc.createElement("student");

    QDomElement studentNumber = doc.createElement("number");
    studentNumber.appendChild(
        doc.createTextNode(QString::number(student->getNumber()))
        );


    QDomElement modules = doc.createElement("modules");
    // modules
    for (Module* module : student->getModules()) {

        QList<QVariant> moduleData = module->getModule();

        QDomElement mod = doc.createElement("module");

        QDomElement code = doc.createElement("code");
        code.appendChild(
            doc.createTextNode(moduleData.at(0).toString())
            );

        QDomElement mark = doc.createElement("mark");
        mark.appendChild(
            doc.createTextNode(moduleData.at(1).toString())
            );

        mod.appendChild(code);
        mod.appendChild(mark);

        modules.appendChild(mod);
    }

    item.appendChild(studentNumber);
    item.appendChild(modules);

    return item;
};



void StudentSerializer::writeXML(Student *student, int index)
{
    QDomElement root = doc.documentElement();
    QDomNodeList items = root.elementsByTagName("student");

    if (index >= 0 && index < items.count()) {
        QDomNode node = items.at(index);
        qDebug() << "Replacing child at index:" << index;

        // Replace on the actual root element
        root.replaceChild(createXMLStudent(doc, student), node);
        qDebug() << doc.toString(4);
    } else {
        qWarning() << "Index out of bounds for XML replacement:" << index;
    }
}

void StudentSerializer::writeXML(Student *student)
{
    QDomElement root = doc.documentElement();
    root.appendChild(createXMLStudent(doc, student));
    qDebug() << "Added new child";
}

void StudentSerializer::saveToXML()
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << doc.toString(4);
        file.close();
        qDebug() << "saved";
    } else {
        qWarning() << "Failed to open file for writing";
    }
}

QList<Student*>* StudentSerializer::readXML()
{
    QList<Student*> *students = new QList<Student*>();


    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file.";
        return students;
    }

    const QDomDocument::ParseResult result = doc.setContent(&file);

    if (!result) {
        qDebug() << "Failed to parse XML:" << result.errorMessage
                 << "at line" << result.errorLine
                 << "column" << result.errorColumn;
        return students;
    }

    file.close();

    QDomElement domElement = doc.documentElement();

    QDomNodeList items = domElement.elementsByTagName("student");

    for (int i = 0; i < items.count(); ++i) {
        QDomNode studentNode = items.at(i);
        QDomElement studentElement = studentNode.toElement();

        QDomElement studentNumber = studentElement.firstChildElement("number");


        Student *student = new Student(studentNumber.text().toInt());



        QDomNodeList moduleNodes = studentElement.elementsByTagName("module");
        for (int j = 0; j < moduleNodes.count(); ++j) {
            QDomElement moduleElement = moduleNodes.at(j).toElement();

            // Extract child text values
            QString code = moduleElement.firstChildElement("code").text();
            double mark = moduleElement.firstChildElement("mark").text().toDouble();

            student->addModule(code, mark);

        }

        students->append(student);
    }


    return students;
}

