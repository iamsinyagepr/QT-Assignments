#include "app.h"
#include "painter.h"
#include "helpers.h"
// #include "loadXML.h"
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


#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QCoreApplication>

const QString READ_FILEPATH = ":/shapes.xml" ;

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

    loadShapes(); // load ui before setup to avoid out of range index search for initial shape
    setupGUI();
}

void App::loadXML() {

    QFile file(READ_FILEPATH);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << READ_FILEPATH;
        return;
    }

    QDomDocument doc;
    QString errorMsg;

    // Call the updated signature
    QDomDocument::ParseResult result = doc.setContent(&file);

    // qDebug() << "initial check";
    if (!result) {
        qDebug() << "XML Parse Error:" << result.errorMessage
                 << "at line" << result.errorLine
                 << "column" << result.errorColumn;
        file.close();
        return;
    }

    // Get the root element
    QDomElement root = doc.documentElement();

    // Traverse child elements
    QDomNodeList items = root.elementsByTagName("shape");
    // qDebug() << "Loaded...";
    for (int i = 0; i < items.count(); ++i) {

        QDomNode node = items.at(i);

        if (!node.isElement()) continue;

        QDomElement element = node.toElement();

        QString type = element.attribute("type").toUpper();
        int penWidth = element.attribute("pw").toUInt(nullptr, 10);
        QString penColor = element.attribute("pc");
        QString fillColor = element.attribute("fc");
        int property1 = element.attribute("p1").toUInt(nullptr, 10);
        int property2 = element.attribute("p2").toUInt(nullptr, 10);

        // qDebug() << type << S_CIRCLE;

        if(type == S_CIRCLE) {

            shapes->addShape(new Circle(
                penWidth,
                getColorInt(penColor),
                getColorInt(fillColor),
                property1
                ));
        };

        if(type == S_SQUARE) {
            shapes->addShape(new Square(
                penWidth,
                getColorInt(penColor),
                getColorInt(fillColor),
                property1
            ));
        };

        if(type == S_ELLIPSE) {
            shapes->addShape(new Ellipse(
                penWidth,
                getColorInt(penColor),
                getColorInt(fillColor),
                property1,
                property2
                ));
        };

        if(type == S_RECTANGLE) {
            shapes->addShape(new Rectangle(
                penWidth,
                getColorInt(penColor),
                getColorInt(fillColor),
                property1,
                property2
                ));
        }

    }
}

void App::updateXML() {

    const QString WRITE_FILEPATH = QCoreApplication::applicationDirPath() + "/shapes.xml";
    QFile file(WRITE_FILEPATH);
    // Open the file for writing text
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << WRITE_FILEPATH;
        return;
    }

    QDomDocument doc;

    // 1. Create the XML processing instruction (optional but recommended)
    QDomProcessingInstruction header = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(header);

    // 2. Create the Root element
    QDomElement root = doc.createElement("shapes");
    doc.appendChild(root);

    for(int i = 0; i < shapes->getSize(); i++) {

        Shape* shape = shapes->getByIndex(i);

        QDomElement XMLShape = doc.createElement("shape");
        XMLShape.setAttribute("type", shape->getClassName().toCaseFolded());
        XMLShape.setAttribute("pw", QString::number(shape->getPenWidth()));
        XMLShape.setAttribute("pc", getColor(shape->getPenColor()).name());
        XMLShape.setAttribute("fc", getColor(shape->getFillColor()).name());
        XMLShape.setAttribute("p1", QString::number(shape->getProperty1()));
        XMLShape.setAttribute("p2", QString::number(shape->getProperty2()));

        // Append child to root
        root.appendChild(XMLShape);
    }

    // 5. Write the XML structure to the file
    QTextStream stream(&file);
    // The second argument (4) sets the indentation level for clean, readable formatting
    doc.save(stream, 4);

    file.close();
    qDebug() << "XML file successfully written to:" << WRITE_FILEPATH;
}

void App::loadShapes() {
    loadXML(); // loads shapes from xml file
    shapes->setListIndex(0); // reset list index
    for(int i = 0; i < shapes->getSize(); i++) {
        listWidget->addItem(
            QString("%1 : %2").arg(i+1).arg(shapes->getByIndex(i)->getClassName())
        );
    }

    // set pagenation
    pagenation->setText(
        QString("%1 of %2")
            .arg(1)
            .arg(shapes->getSize())
        );

    // select first item
    listWidget->setCurrentRow(0);
}

void App::setupGUI() {


    // app layout
    QHBoxLayout *app_layout(new QHBoxLayout(this));
    app_layout->setContentsMargins(10,10,10,10);

    // painter lapout
    QVBoxLayout *painterLayout(new QVBoxLayout());
    Painter *painter(new Painter);

    // get initial shape
    // Shape * shape = painter->getCurrentShape(); replace with shape from loaded shapes
    Shape* shape = shapes->getByIndex(0);
    painter->draw(shape);


    QVBoxLayout *shapeFormLayout(new QVBoxLayout());
    QFormLayout *createNewForm(new QFormLayout());


    shapeSelector->addItems(SHAPES_LIST);
    shapeSelector->setCurrentIndex(0);


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
        // painter->update();
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
    connect(property1, &QSpinBox::valueChanged, this, [this, painter]() {
        painter->getCurrentShape()->setProperty1(property1->value());
    });

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

        // qDebug() << maxItems;

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

        updateXML();

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


