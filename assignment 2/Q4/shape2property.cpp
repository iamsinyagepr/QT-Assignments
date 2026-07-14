#include "shape2property.h"

Shape2Property::Shape2Property() {}

int Shape2Property::getWidth() { return width; }
int Shape2Property::getHeight() { return height; }

//settert
void Shape2Property::setWidth(int m_width) { width = m_width; }
void Shape2Property::setHeight(int m_height) { height = m_height; }

void Shape2Property::setProperty2(int m_property2) { property2 = m_property2; }

// getters
int Shape2Property::getProperty2() { return property2; }