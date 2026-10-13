#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

// Implemetation

class Student {
public:
    QString name;
    int age;
};

class StudentSerializer {
public:
    static QJsonObject serialize(const Student& s) {
        QJsonObject obj;
        obj["name"] = s.name;
        obj["age"] = s.age;
        return obj;
    }

    static Student deserialize(const QJsonObject& obj) {
        Student s;
        s.name = obj["name"].toString();
        s.age = obj["age"].toInt();
        return s;
    }
};

// Usage
Student student{"John", 22};

QJsonObject json =
    StudentSerializer::serialize(student);

QJsonDocument doc(json);

QByteArray data = doc.toJson();

Student restored = StudentSerializer::deserialize(
        QJsonDocument::fromJson(data).object()
    );

// explanation
// Student represents the application's data
// StudentSerializer is responsible for converting it
// QJsonObject stores key-value pairs
// QJsonDocument converts the object to JSON bytes
// deserialize() reconstructs a Student