#ifndef SHAPE1PROPERTY_H
#define SHAPE1PROPERTY_H

#include "shape.h"

class QPainter;

class Shape1Property : public Shape
{
private:

    int property1 = 0;
    int radius = 50;
    int size = 100;

public:
    Shape1Property();

    // getters
    virtual int getProperty1();
    virtual void setProperty1(int property1);

    virtual int getSize();
    virtual int getRadius();


    // setters
    virtual void setSize(int m_size);
    virtual void setRadius(int rad);

    virtual void setProperty2(int p2) override;
    virtual int getProperty2() override;


    virtual int getWidth() override;
    virtual void setWidth(int w) override;

    virtual int getHeight() override;
    virtual void setHeight(int h) override;


    // virtual functions
    virtual void draw(QPainter *painter) = 0;
};

#endif // SHAPE1PROPERTY_H
