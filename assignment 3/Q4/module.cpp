#include "module.h"

Module::Module() {}

Module::Module(QString m_code, double m_marks) {
    code = m_code;
    marks = m_marks;
    // qDebug() << m_code << " " << m_marks;
}

QList<QVariant> Module::getModule() {

    QList<QVariant> values;
    values.append(code); values.append(marks);

    return values;
}

void Module::setCode(QString m_code) {
    code = m_code;
}

void Module::setMarks(double m_marks) {
    marks = m_marks;
}