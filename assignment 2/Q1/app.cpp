#include "app.h"
#include "shape.h"
#include "painter.h"

#include <QObject>

#include <QComboBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QStringList>


App::App(QWidget *parent) : QWidget{parent},

    shapeSelector(new QComboBox),
    penColor(new QComboBox),
    fillColor(new QComboBox),

    penWidth(new QSpinBox),
    property1(new QSpinBox),
    property2(new QSpinBox),

    width(new QSpinBox),
    size(new QSpinBox),
    height(new QSpinBox),
    radius(new QSpinBox)

{
    setupGUI();
}

void App::setupGUI() {


    // app layout
    QHBoxLayout *app_layout(new QHBoxLayout(this));
    app_layout->setContentsMargins(10,10,10,10);

    Painter *painter(new Painter);
    Shape * shape = painter->getCurrentShape();

    QFormLayout *createNewForm(new QFormLayout());

    QStringList Shapes = {"CIRCLE", "SQUARE", "ELLIPSE", "RECTANGLE"};
    shapeSelector->addItems(Shapes);

    shapeSelector->setCurrentIndex(painter->currentShape);


    createNewForm->addRow(new QLabel("Choose Shape"), shapeSelector);
    connect(shapeSelector, &QComboBox::currentIndexChanged, this, [this, painter, createNewForm]() {

        int newIndex = shapeSelector->currentIndex();

        Shape* currentShape = painter->draw(newIndex);

        penWidth->setValue(currentShape->getPenWidth());
        property1->setValue(currentShape->getProperty1());



        if(newIndex <= 1) {
            size->setValue(currentShape->getSize());
            createNewForm->setRowVisible(5, false);
            createNewForm->setRowVisible(6, false);
            createNewForm->setRowVisible(7, false);
             createNewForm->setRowVisible(8, true);
        }
        if(newIndex > 1) {

            createNewForm->setRowVisible(5, true);
            createNewForm->setRowVisible(6, true);
            createNewForm->setRowVisible(7, true);
            createNewForm->setRowVisible(8, false);

            property2->setValue(currentShape->getProperty2());
            width->setValue(currentShape->getWidth());
            height->setValue(currentShape->getHeight());
        }
        painter->update();
    });

    QStringList Colors = {"Yellow", "Red", "Blue", "Green", "Black"};
    penColor->addItems(Colors);
    penColor->setCurrentIndex(shape->getPenColor());
    createNewForm->addRow(new QLabel("Choose Pen Color"), penColor);
    connect(penColor, &QComboBox::currentIndexChanged, this, [this, painter]() {
        painter->setPenColor(penColor->currentIndex());
    });


    fillColor->addItems(Colors);
    fillColor->setCurrentIndex(shape->getFillColor());
    createNewForm->addRow(new QLabel("Choose Fill Color"), fillColor);

    connect(fillColor, &QComboBox::currentIndexChanged, this, [this, painter]() {
        painter->setPenFill(fillColor->currentIndex());
    });

    penWidth->setValue(shape->getPenWidth());
    createNewForm->addRow(new QLabel("Set Pen Width"), penWidth);
    penWidth->setValue(painter->getCurrentShape()->getPenWidth());

    connect(penWidth, &QSpinBox::valueChanged, this, [this, painter]() {
        painter->setPenWidth(penWidth->value());
    });

    createNewForm->addRow(new QLabel("Property 1"), property1);
    connect(property1, &QSpinBox::valueChanged, this, [this, painter]() {
        painter->getCurrentShape()->setProperty1(property1->value());
    });

    createNewForm->addRow(new QLabel("Property 2"), property2);
    connect(property2, &QSpinBox::valueChanged, this, [this, painter]() {
        painter->getCurrentShape()->setProperty2(property2->value());
    });

    width->setRange(0, 9999);
    createNewForm->addRow(new QLabel("Width"), width);
    connect(width, &QSpinBox::valueChanged, this, [this, painter]() {
        painter->getCurrentShape()->setWidth(width->value());
        painter->update();
    });

    height->setRange(0, 9999);
    createNewForm->addRow(new QLabel("Height"), height);
    connect(height, &QSpinBox::valueChanged, this, [this, painter]() {
        painter->getCurrentShape()->setHeight(height->value());
        painter->update();
    });

    size->setRange(0, 9999);
    createNewForm->addRow(new QLabel("Size"), size);
    connect(size, &QSpinBox::valueChanged, this, [this, painter]() {
        painter->getCurrentShape()->setSize(size->value());
        painter->update();
    });

    app_layout->addWidget(painter);
    app_layout->addLayout(createNewForm);

    if(painter->currentShape <= 1)
    {
        size->setValue(shape->getSize());
        createNewForm->setRowVisible(5, false);
        createNewForm->setRowVisible(6, false);
        createNewForm->setRowVisible(7, false);
        createNewForm->setRowVisible(8, true);
    } else {
        createNewForm->setRowVisible(8, false);
        width->setValue(shape->getWidth());
        height->setValue(shape->getHeight());
    }
}


