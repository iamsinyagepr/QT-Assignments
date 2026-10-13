// XML stands for Extensible Markup Language 

// RULES:
// Exactly one root element
// Properly nested elements
// Matching opening and closing tags
// Quoted attribute values
// Escaping special characters where required

// DOM and Streaming
/**
 * DOM
 * - Buils an in memory document tree
 * - Convenient random access
 * - Convenient modification
 * - QDomDocument
 */

 /**
  * Streaming
  * - Processes XML sequentially
  * - Efficient memory usage
  * - Suitable for large files
  * - QXmlStreamReader and QXmlStreamWriter
  */

// Generating XML using DOM
#include <QDomDocument>
#include <QFile>

QDomDocument doc("students");

QDomElement root = doc.createElement("students");
doc.appendChild(root);

QDomElement student = doc.createElement("student");

student.setAttribute("id", "1");

QDomElement name = doc.createElement("name");

name.appendChild(
    doc.createTextNode("Alice")
);

student.appendChild(name);
root.appendChild(student);

QFile file("students.xml");

if (file.open(QIODevice::WriteOnly)) {
    file.write(doc.toByteArray(2));
}





// Parsing XML using DOM
QFile file("students.xml");

if (!file.open(QIODevice::ReadOnly))
    return;

QDomDocument doc;

if (!doc.setContent(&file))
    return;

QDomElement root = doc.documentElement();

QDomNodeList students = root.elementsByTagName("student");

for (int i = 0; i < students.count(); ++i) {

    QDomElement student = students.at(i).toElement();
    QString name = student.firstChildElement("name").text();

    qDebug() << name;
}




//  QXmlStreamWriter
QFile file("students.xml");

if (file.open(QIODevice::WriteOnly)) {
    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();

    writer.writeStartElement("students");

    writer.writeStartElement("student");
    writer.writeAttribute("id", "1");

    writer.writeTextElement("name", "Alice");

    writer.writeEndElement();
    writer.writeEndElement();

    writer.writeEndDocument();
}



// QXmlStreamReader
QFile file("students.xml");

if (!file.open(QIODevice::ReadOnly))
    return;

QXmlStreamReader reader(&file);

while (!reader.atEnd()) {
    reader.readNext();

    if (
        reader.isStartElement() &&
        reader.name() == QLatin1String("name")
    ) {

        QString name = reader.readElementText();

        qDebug() << name;
    }
}

if (reader.hasError()) {
    qDebug() << reader.errorString();
}