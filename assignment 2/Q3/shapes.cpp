#include "shapes.h"
#include "helpers.h"
#include "circle.h"
#include "ellipse.h"
#include "rectangle.h"
#include "square.h"

void clone(Shape* shape1, Shape * shape2) {
    shape1->setPenWidth(shape2->getPenWidth());
    shape1->setPenColor(shape2->getPenColor());
    shape1->setFillColor(shape2->getFillColor());
}

Shapes::Shapes() {
}

Shapes::~Shapes() {
    qDeleteAll(shapes);
    shapes.clear();
}

void Shapes::addShape(Shape* shape) {

    QString dataType = shape->getClassName();

    if(dataType == S_CIRCLE) {
        Circle* circle = new Circle();
        clone(circle, shape);
        shapes << circle;
        // delete circle;
    };

    if(dataType == S_SQUARE) {
        Square* square = new Square();
        clone(square, shape);
        shapes << square;
    };

    if(dataType == S_ELLIPSE) {
        Ellipse* ellipse = new Ellipse();
        clone(ellipse, shape);
        shapes << ellipse;
    };

    if(dataType == S_RECTANGLE) {
        Rectangle* rect = new Rectangle();
        clone(rect, shape);
        shapes << rect;
    }

    listIndex += 1;
}

void Shapes::setListIndex(int index){ listIndex = index; }

Shape * Shapes::getByIndex(int index) {
    return shapes.at(index);
}

void Shapes::removeCurrent() {
    shapes.removeAt(listIndex);
}

int Shapes::getCurrentIndex() {
    return listIndex;
}

int Shapes::getSize() {
    return shapes.size();
}

Shape* Shapes::getNext() {
    if((shapes.size() - 1) < listIndex) return shapes.at(listIndex);
    if((shapes.size()-1) == listIndex) return nullptr;
    listIndex += 1;
    return shapes.at(listIndex);
}


Shape* Shapes::getPrevious() {
    if(shapes.isEmpty()) return nullptr;
    if(listIndex == 0) return shapes[0];

    listIndex -= 1;
    return shapes.at(listIndex);
}