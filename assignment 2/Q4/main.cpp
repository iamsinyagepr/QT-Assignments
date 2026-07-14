#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QCoreApplication>

#include "app.h"


using namespace std;

/*
    Memento pattens used in shapes to backup the shape list and index
    also made modifications to how the shapes are added because it was conflicting with backup
    only a single point of backup available and is replaced
    on restore the list widget is cleared then repopulated
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App ui;

    ui.setMinimumSize(700, 300);
    ui.show();

    return a.exec();
}