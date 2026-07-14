#ifndef SHAPES_H
#define SHAPES_H

#include "shape.h"
#include "memento.h"

class Shapes {

public:
    Shapes();
    ~Shapes();

    void addShape(Shape *shape);
    void removeCurrent();
    Shape * getByIndex(int index);
    Shape * getNext();
    Shape * getPrevious();
    int getCurrentIndex();
    void setListIndex(int index);
    int getSize();

    void setMemento();
    void decodeXML(QString data);
    QString createMemento();
    Memento getMemento();

private:
    QList<Shape*> shapes;
    Memento caretaker;
    int listIndex;

};

#endif // SHAPES_H
