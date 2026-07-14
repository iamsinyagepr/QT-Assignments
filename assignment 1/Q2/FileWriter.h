#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QMetaObject>
#include <QMetaProperty>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QFile>
#include <QTextStream>

class FileWriter {
private:
    QString filename;
    QObjectList* list;

public:
    FileWriter(QObjectList* m_list, QString fname): filename(fname), list(m_list) {};
    ~FileWriter() = default;

    int write() {

        if(!list || list->isEmpty()) return 0;

        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for writting";
            return 0;
        }

        int written_items = 0;
        QTextStream out(&file);

        for (QObject *obj: *list) {

            if(!obj) continue;

            const QMetaObject *meta = obj->metaObject();
            out << meta->className() << "\n";

            // List all Properties
            for(int i = 0; i < meta->propertyCount(); ++i) {

                QMetaProperty property = meta->property(i);

                QString propertyName = property.name();

                QVariant value = obj->property(propertyName.toStdString().c_str());
                // const char* className = property.enclosingMetaObject()->className();

                if(propertyName == "objectName") continue;

                out << propertyName << " : " << value.toString() << "\n";

            }

            out << "\n";
            ++written_items;

        };

        file.close();

        return written_items;
    }
};

#endif // FILEWRITER_H
