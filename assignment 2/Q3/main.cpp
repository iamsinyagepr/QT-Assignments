#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QCoreApplication>

#include "app.h"


using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App ui;

    ui.setMinimumSize(600, 300);
    ui.show();

    return a.exec();
}