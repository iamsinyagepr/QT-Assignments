#ifndef MEMENTO_H
#define MEMENTO_H

#include <QStringList>

class Memento
{
private:
    friend class Shapes;

    Memento();

    QStringList state;
    QString lastBackupAt;

    QStringList getState();
    QString setState(QStringList state);

    void setLastBackupAt(QString lastBackupTime);
};

#endif // MEMENTO_H
