#include "shape.h"

Shape::Shape(QObject *parent) : QObject{parent} {}

QString Shape::getClassName() { return className; }
