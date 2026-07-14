#ifndef SHAPES_H
#define SHAPES_H

#include "shape.h"

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
private:
    QList<Shape*> shapes;
    int listIndex;

};

#endif // SHAPES_H
