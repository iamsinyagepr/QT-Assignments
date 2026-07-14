#include "memento.h"
#include <QDateTime>

Memento::Memento() {}

QStringList Memento::getState() {
    return state;
}

QString Memento::setState(QStringList s) {
    state = s;

    QDateTime now = QDateTime::currentDateTime();
    lastBackupAt = now.toString("yyyy-MM-dd HH:mm:ss");
    return lastBackupAt;
}