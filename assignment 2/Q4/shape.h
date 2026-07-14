#ifndef SHAPE_H
#define SHAPE_H


#include <QObject>
#include <QDebug>
#include <QColor>
#include <QPen>
#include <QBrush>

class Shape : public QObject
{
    Q_OBJECT

private:
    int penWidth = 5;
    int penColor = 0;
    int fillColor = 1;
    QString className;

public:
    explicit Shape(QObject *parent = nullptr);


    // setters
    void setPenWidth(int m_penWidth) { penWidth = m_penWidth ; }
    void setPenColor(int m_penColor) { penColor = m_penColor; }
    void setFillColor(int m_fillColor) { fillColor = m_fillColor; }

    //getters
    int getPenWidth() { return penWidth; }
    int getPenColor() { return penColor; }
    int getFillColor() { return fillColor; }


    // virtual functions
    virtual void draw(QPainter *painter) = 0;
    virtual void setProperty1(int p1) = 0;
    virtual void setProperty2(int p2) = 0;
    virtual int getProperty1() = 0;
    virtual int getProperty2() = 0;

    virtual int getSize() = 0;
    virtual void setSize(int size) = 0;

    virtual int getWidth() = 0;
    virtual void setWidth(int w) = 0;

    virtual int getHeight() = 0;
    virtual void setHeight(int h) = 0;

    virtual QString getClassName() = 0;

signals:

};


#endif // SHAPE_H
