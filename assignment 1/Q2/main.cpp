
#include <QCoreApplication>
#include <QDebug>
#include <QObject>

#include "Vehicle.h"
#include "FileWriter.h"

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
    QObjectList list;

    for (Vehicle* vehicle : vehicleList) {
        list.append(vehicle);
    }


    FileWriter *writer = new FileWriter(&list, QString("vehicles.txt"));

    int number_of_items = writer->write();
    qDebug() << "Number of files: " << number_of_items;

    delete writer;

    return a.exec();
}
