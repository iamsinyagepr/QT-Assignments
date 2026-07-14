#ifndef SHAPE2PROPERTY_H
#define SHAPE2PROPERTY_H

#include "shape1property.h"
#include <QObject>

class QPainter;

class Shape2Property : public Shape1Property
{

private:

    int property2 = 0;
    int width = 200;
    int height = 100;

public:
    Shape2Property();
    virtual int getProperty2();
    virtual void setProperty2(int property2);
    // getters

    virtual int getWidth();
    virtual int getHeight();

    //settert
    virtual void setWidth(int m_width);
    virtual void setHeight(int m_height);




    virtual void draw(QPainter *painter) = 0;

};

#endif // SHAPE2PROPERTY_H
