// Qt provides qobject_cast<T> for runtime-safe casting within the QObject hierarchy

class QObject;
class QPushButton;

QObject* object = new QPushButton("Save");

QPushButton* button =
    qobject_cast<QPushButton*>(object);

if (button) {
    button->setText("Submit");
}

// if the object is not compatibke with the requested type, qobject_cast returns nullptr

/**
 * static_cast -> Compile-time checked conversion where appropriate
 * dynamic_cast -> RTTI-based runtime polymorphic casting
 * 
 * qobject_cast -> Qt meta-object-based casting for QObject types
 * -> does not require RTTI to be enabled, but the target QObject class generally needs appropriate meta-object support
 */