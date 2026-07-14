#include "app.h"
#include "painter.h"
#include "helpers.h"
#include "helpers.h"
#include <QObject>

#include <QPushButton>
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
#include <QListWidget>


App::App(QWidget *parent) : QWidget{parent},
    listWidget(new QListWidget),
    shapes(new Shapes()),
    shapeSelector(new QComboBox),
    penColor(new QComboBox),
    fillColor(new QComboBox),

    penWidth(new QSpinBox),
    property1(new QSpinBox),
    property2(new QSpinBox),

    width(new QSpinBox),
    size(new QSpinBox),
    height(new QSpinBox),
    radius(new QSpinBox),

    addShape(new QPushButton("Add Shape")),
    nextShape(new QPushButton("Next Shape")),
    prevShape(new QPushButton("Prev Shape")),
    pagenation(new QLabel("0 of 0"))

{
    setupGUI();
}

void App::setupGUI() {


    // app layout
    QHBoxLayout *app_layout(new QHBoxLayout(this));
    app_layout->setContentsMargins(10,10,10,10);

    // painter lapout
    QVBoxLayout *painterLayout(new QVBoxLayout());
    Painter *painter(new Painter);

    // get initial shape
    Shape * shape = painter->getCurrentShape();


    QVBoxLayout *shapeFormLayout(new QVBoxLayout());
    QFormLayout *createNewForm(new QFormLayout());


    shapeSelector->addItems(SHAPES_LIST);
    shapeSelector->setCurrentIndex(painter->currentShape);


    createNewForm->addRow(new QLabel("Choose Shape"), shapeSelector);
    connect(shapeSelector, &QComboBox::currentIndexChanged, this, [this, painter, createNewForm]() {
        int index = shapeSelector->currentIndex();
        painter->setCurrentShape(index);

        Shape* currentShape = painter->getCurrentShape();

        if(index <= 1) {
            size->setValue(currentShape->getSize());
            createNewForm->setRowVisible(5, false);
            createNewForm->setRowVisible(6, false);
            createNewForm->setRowVisible(7, false);
            createNewForm->setRowVisible(8, true);
        }
        if(index > 1) {

            createNewForm->setRowVisible(5, true);
            createNewForm->setRowVisible(6, true);
            createNewForm->setRowVisible(7, true);
            createNewForm->setRowVisible(8, false);

            property2->setValue(currentShape->getProperty2());
            width->setValue(currentShape->getWidth());
            height->setValue(currentShape->getHeight());
        }
    });

    QStringList Colors = {"Yellow", "Red", "Blue", "Green", "Black"};
    penColor->addItems(Colors);
    penColor->setCurrentIndex(shape->getPenColor());
    createNewForm->addRow(new QLabel("Choose Pen Color"), penColor);


    fillColor->addItems(Colors);
    fillColor->setCurrentIndex(shape->getFillColor());
    createNewForm->addRow(new QLabel("Choose Fill Color"), fillColor);

    penWidth->setValue(shape->getPenWidth());
    createNewForm->addRow(new QLabel("Set Pen Width"), penWidth);
    penWidth->setValue(painter->getCurrentShape()->getPenWidth());

    createNewForm->addRow(new QLabel("Property 1"), property1);

    createNewForm->addRow(new QLabel("Property 2"), property2);

    width->setRange(0, 9999);
    createNewForm->addRow(new QLabel("Width"), width);


    height->setRange(0, 9999);
    createNewForm->addRow(new QLabel("Height"), height);

    size->setRange(0, 9999);
    createNewForm->addRow(new QLabel("Size"), size);


    QHBoxLayout *navigation(new QHBoxLayout);

    navigation->addWidget(prevShape);
    connect(prevShape, &QPushButton::clicked, this, [painter, this]() {

        int currentRow = shapes->getCurrentIndex();
        // qDebug() << currentRow;
        int maxItems = shapes->getSize();

        if((maxItems - 1) <= 0 || currentRow == 0) return;

        painter->draw(shapes->getPrevious());
        pagenation->setText(
            QString("%1 of %2")
                .arg(currentRow)
                .arg(maxItems)
            );

        listWidget->setCurrentRow(currentRow-1);
    });

    navigation->addWidget(pagenation);

    navigation->addWidget(nextShape);
    connect(nextShape, &QPushButton::clicked, this, [painter, this]() {

        int currentRow = shapes->getCurrentIndex() + 1;
        int maxItems = shapes->getSize();

        if(
            maxItems == 0 ||
            currentRow == maxItems
        ) return;


        painter->draw(shapes->getNext());
        // painter->update();
        pagenation->setText(
            QString("%1 of %2")
                .arg(currentRow+1)
                .arg(maxItems)
            );

        listWidget->setCurrentRow(currentRow);
    });

    painterLayout->addWidget(painter);
    painterLayout->addLayout(navigation);

    app_layout->addLayout(painterLayout);

    connect(listWidget, &QListWidget::itemSelectionChanged, this, [painter, this]() {

        int index = listWidget->currentRow();
        shapes->setListIndex(index);
        painter->draw(shapes->getByIndex(index));

        pagenation->setText(
            QString("%1 of %2")
                .arg(index+1)
                .arg(shapes->getSize())
            );

    });
    listWidget->setFixedWidth(150);
    app_layout->addWidget(listWidget);

    shapeFormLayout->addLayout(createNewForm);

    connect(addShape, &QPushButton::clicked, this, [painter, this]() {


        int shape = shapes->getSize();
        int shapeIndex = shapeSelector->currentIndex();

        painter->setCurrentShape(shapeIndex);
        painter->setPenColor(penColor->currentIndex());
        painter->setPenFill(fillColor->currentIndex());
        painter->setPenWidth(penWidth->value());
        painter->getCurrentShape()->setProperty1(property1->value());
        painter->getCurrentShape()->setProperty2(property2->value());
        painter->getCurrentShape()->setHeight(height->value());
        painter->getCurrentShape()->setSize(size->value());
        painter->getCurrentShape()->setWidth(width->value());

        // painter->draw();
        Shape* newShape = painter->getCurrentShape();
        shapes->addShape(newShape);


        listWidget->addItem(
            QString("%1 : %2")
                .arg(shape+1)
                .arg(newShape->getClassName())
            );

        listWidget->setCurrentRow(shape);

        pagenation->setText(
            QString("%1 of %2")
                .arg(shape)
                .arg(shape)
            );
    });
    shapeFormLayout->addWidget(addShape);
    app_layout->addLayout(shapeFormLayout);

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


