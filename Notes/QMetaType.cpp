// ## provides runtime information about registered C++ types
// it is important when Qt needs to manipulate values without knowing their exact C++ type at compile time

// Examples include QVariant, queued signal-slot arguments and generic property systems
#include <QMetaType>
#include <QDebug>

int id = QMetaType::fromType<int>().id();

qDebug() << id;



// A custome type
struct Employee {
    QString name;
    int salary;
};

Q_DECLARE_METATYPE(Employee)
/**
 * Q_DECLARE_METATYPE
 * - makes the type available to Qt's template-based metatype facilities
 * - Runtime named-based lookups and some queued or dynamic operations can additionally require registration with qRegisterMetaType<T>()
 */


//using QVariant
Employee employee{"Alice", 25000};

QVariant value =
    QVariant::fromValue(employee);

Employee restored =
    value.value<Employee>();

