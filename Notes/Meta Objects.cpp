// - Contains information describing an object or class

// ordinary object data describes the application's subject matter while metadata describes the program's own structure

// metadata
/**
 * Class name
 * properties
 * methods
 * signals
 * slots
 * enumerations
 * inheritance relationships
 */

// reflection allows software to inspect and sometimes interact with this structure dynamically

// # QT's meta-object system
// Qt provides a meta-object system based on

// QObject
// Q_OBJECT macro
// Meta-Object Compiler (moc)
// QMeta Object

// * moc processes supported declarations and generates code containig metadata and supporting functionality

#include <QObject>
#include <QString>

class Person : public QObject {
    Q_OBJECT

    Q_PROPERTY(
        QString name
        READ name
        WRITE setName
        NOTIFY nameChanged
    )

public:
    explicit Person(QObject* parent = nullptr)
        : QObject(parent) {}

    QString name() const {
        return m_name;
    }

    void setName(const QString& value) {
        if (m_name == value)
            return;

        m_name = value;
        emit nameChanged(m_name);
    }

signals:
    void nameChanged(const QString& name);

private:
    QString m_name;
};

/**
 * Q_OBJECTS -> enables the class's own Qt meta-object information
 * Q_PROPERTY declares a property accessible though Qt's property system
 * READ name identifies the getter
 * WRITE setName identifies the setter
 * NOTIFY nameChanged identifies the change notification signal
 * 
 * NOTIFY signal is important for reactive property bindings
 */

 // ## Inspecting metadata at runtime

Person person;

const QMetaObject* meta =
    person.metaObject(); // retreives metadata

qDebug() << meta->className(); // identifies the class
qDebug() << meta->propertyCount(); // counts properties known to the meta-object, including inherited ones

for (
    int i = meta->propertyOffset(); // identifies where properties introduces by the current class begin
     i < meta->propertyCount();
     ++i
) {

    QMetaProperty property =
        meta->property(i);

    qDebug() << property.name();
}

// This is reflective programming because the code discovers properties at runtime rather than accessing each property directly



// ## Dynamic propery access
Person person;

person.setProperty("name", "Alice"); // Reflective
// person.setName("Alice") - Direct

QVariant value =
    person.property("name");

qDebug() << value.toString();

// The reflective version uses a property name as data, making it useful in generic editors, configuration systems, serializers and UI builders