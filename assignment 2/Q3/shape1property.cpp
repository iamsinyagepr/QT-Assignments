#include "shape1property.h"

Shape1Property::Shape1Property() {}

void Shape1Property::setSize(int m_size) {
    size = m_size;
}

void Shape1Property::setRadius(int m_radius) {
    radius = m_radius;
}

void Shape1Property::setProperty1(int m_property1) { property1 = m_property1; }
int Shape1Property::getProperty1() { return property1; }

// getters
int Shape1Property::getSize() { return size; }
int Shape1Property::getRadius() { return radius; }



void Shape1Property::setProperty2(int p2) {  Q_UNUSED(p2); }
int Shape1Property::getProperty2() { return 0; }

void Shape1Property::setWidth(int w) {  Q_UNUSED(w); }
int Shape1Property::getWidth() { return 0; }

void Shape1Property::setHeight(int h) {  Q_UNUSED(h); }
int Shape1Property::getHeight() { return 0; }
