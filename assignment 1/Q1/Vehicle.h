#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QString>


class Vehicle : public QObject {
    Q_OBJECT
private:
    QString model;
    int year;

public:

    explicit Vehicle(
        const QString &m_model = "Default Model",
        const int &m_year = 2026,
        QObject *parent = nullptr
        ) : QObject(parent), model(m_model), year(m_year) { }


    // getters
    int getYear() const {return year;};
    QString getModel() const {  return model;};

    // setters
    void setModel(const QString &m_model){ model = m_model; };
    void setYear(const int &m_year){ year = m_year; };


    // virtual functions
    virtual int getNumberOfPassangers() = 0;
    virtual double getPassangerCapacity() = 0;
    virtual QString displayVehicleInfo() = 0;

    // vehicle deconstructor
    virtual ~Vehicle() = default;

};

class PassangerVehicle : public Vehicle {
private:
    int number_of_passangers;

public:

    PassangerVehicle(
        const QString &m_model,
        const int &m_year,
        int m_passangers,
        QObject *parent
        ) : Vehicle(m_model, m_year, parent), number_of_passangers(m_passangers) {};

    PassangerVehicle(QObject *parent): Vehicle("Passanger Vehicle", 2026, parent), number_of_passangers(16) {}

    double getPassangerCapacity() override { return 0.0; }
    int getNumberOfPassangers() override {
        return number_of_passangers;
    };

    QString displayVehicleInfo() override {
        return QString("MODEL: %1   YEAR: %2    PASSANGERS: %3")
        .arg(getModel(), QString::number(getYear()), QString::number(number_of_passangers));
    }
};


class TransportVehicle : public Vehicle {
private:
    double passanger_capacity;
public:

    TransportVehicle(
        const QString &m_model,
        const int &m_year,
        const double &m_capacity,
        QObject *parent
        ) :
        Vehicle(m_model, m_year, parent),
        passanger_capacity(m_capacity) {};

    TransportVehicle(QObject *parent): Vehicle("Transport Vehicle", 2000, parent), passanger_capacity(200.0) { }

    // override functions
    int getNumberOfPassangers() override { return 0; }
    double getPassangerCapacity() override {
        return passanger_capacity;
    }

    QString displayVehicleInfo() override {
        return QString("MODEL: %1   YEAR: %2    CAPACITY: %3kg")
        .arg(getModel(), QString::number(getYear()), QString::number(passanger_capacity));
    }

};

#endif // VEHICLE_H
