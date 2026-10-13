#ifndef MODULE_H
#define MODULE_H

#include <QString>
#include <QList>
#include <QVariant>

class Module {

private:
    QString code;
    double marks;
public:
    Module();
    Module(QString m_code, double m_marks);

    QList<QVariant> getModule();

    void setCode(QString m_code);
    void setMarks(double m_marks);

};

#endif // MODULE_H
