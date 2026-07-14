#include <QApplication>
#include <QDebug>
#include <QMainWindow>

#include "app.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    App ui;

    ui.setMinimumWidth(600);

    ui.show();

    return a.exec();
}