#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <QObject>

class XMLLoader : public QObject
{
    Q_OBJECT
public:
    explicit XMLLoader(QObject *parent = nullptr);

signals:
};

#endif // XMLLOADER_H
