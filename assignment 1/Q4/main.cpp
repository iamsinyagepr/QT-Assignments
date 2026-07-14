#include <QApplication>
#include "App.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    App window;
    window.show();

    return app.exec();
}
