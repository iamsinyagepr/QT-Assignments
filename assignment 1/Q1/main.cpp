#include <QCoreApplication>
#include <QDebug>
#include <QObject>

#include "Vehicle.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // parent object for Parent-child Facility
    QObject *parent = new QObject();

    //creating passanger vehicles
    // - Passanger vehicle without values
    new PassangerVehicle(parent);
    // - Passanger vehicles with values
    new PassangerVehicle("Second Car", 2006, 20, parent);

    //creating transport vehicles
    // - Transport vehicle without values
    new TransportVehicle(parent);
    // - Transport Vehicle with values
    new TransportVehicle("Fourth Car", 2015, 150.0, parent);

    //conversion of parent object to list
    const QList<Vehicle*> vehicleList = parent->findChildren<Vehicle*>();

    for (Vehicle* vehicle : vehicleList) {
        qDebug() << vehicle->displayVehicleInfo().toStdString();
    }

    // delete parent object
    delete parent;

    return a.exec();
}