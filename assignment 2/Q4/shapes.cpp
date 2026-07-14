#include "shapes.h"
#include "helpers.h"
#include "circle.h"
#include "ellipse.h"
#include "rectangle.h"
#include "square.h"

#include <QDomDocument>
#include <QDomElement>
#include <QCoreApplication>
#include <QDateTime>

void clone(Shape* shape1, Shape * shape2) {
    shape1->setPenWidth(shape2->getPenWidth());
    shape1->setPenColor(shape2->getPenColor());
    shape1->setFillColor(shape2->getFillColor());
}

Shapes::Shapes() {}
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
Shape * Shapes::getByIndex(int index) { return shapes.at(index); }
void Shapes::removeCurrent() { shapes.removeAt(listIndex); }
int Shapes::getCurrentIndex() { return listIndex; }
int Shapes::getSize() { return shapes.size(); }

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

Memento Shapes::getMemento() {
    return caretaker;
}


void Shapes::decodeXML(QString xmlData) {

    QDomDocument doc;
    QString errorMsg;

    // Call the updated signature
    QDomDocument::ParseResult result = doc.setContent(xmlData);

    // qDebug() << "initial check";
    if (!result) {
        qDebug() << "XML Parse Error:" << result.errorMessage
                 << "at line" << result.errorLine
                 << "column" << result.errorColumn;
        return;
    }

    // Get the root element
    QDomElement root = doc.documentElement();
    // qDebug() << root.text();

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

            addShape(new Circle(
                penWidth,
                getColorInt(penColor),
                getColorInt(fillColor),
                property1
                ));
        };

        if(type == S_SQUARE) {
            addShape(new Square(
                penWidth,
                getColorInt(penColor),
                getColorInt(fillColor),
                property1
                ));
        };

        if(type == S_ELLIPSE) {
            addShape(new Ellipse(
                penWidth,
                getColorInt(penColor),
                getColorInt(fillColor),
                property1,
                property2
                ));
        };

        if(type == S_RECTANGLE) {
            addShape(new Rectangle(
                penWidth,
                getColorInt(penColor),
                getColorInt(fillColor),
                property1,
                property2
                ));
        }

    }

    QDomElement index = root.lastChildElement("index");

    if (!index.isNull()) {

        QString value = index.attribute("value");
        listIndex = value.toInt(nullptr);
    }
}


void Shapes::setMemento() {

    shapes.clear();
    QString xmlResults = "<shapes>";
    QStringList state = getMemento().getState();

    for (QString value : state) {
        xmlResults.append(value);
    }

    xmlResults.append("</shapes>");
    // qDebug() << xmlResults;

    decodeXML(xmlResults);
}

QString Shapes::createMemento(){

    QStringList state;
    // Memento memento;

    // backs up all shapes
    for(int i = 0; i < shapes.size(); i++) {

        Shape* shape = shapes.at(i);
        QString className = shape->getClassName();

        /*
            converts the string to capitalized
        */
        className = className.toLower();
        className[0] = className[0].toUpper();

        QString xmlshape = QString("<shape type=\"%1\" pw=\"%2\" pc=\"%3\" fc=\"%4\" p1=\"%5\" p2=\"%6\" />")
            .arg(className)
            .arg(shape->getPenWidth())
            .arg(shape->getPenColor())
            .arg(shape->getFillColor())
            .arg(shape->getProperty1())
            .arg(shape->getProperty2())
        ;

        state << xmlshape;
    }

    // backs up list index
    state <<  QString("<index value=\"%1\" />").arg(listIndex);
    qDebug() << state;

    return caretaker.setState(state);
}