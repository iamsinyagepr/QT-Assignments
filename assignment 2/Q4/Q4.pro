TEMPLATE = app

QT += core gui widgets xml

CONFIG += c++11

HEADERS += \
    app.h \
    circle.h \
    ellipse.h \
    helpers.h \
    memento.h \
    painter.h \
    rectangle.h \
    shape.h \
    shape1property.h \
    shape2property.h \
    shapes.h \
    square.h

SOURCES += \
    app.cpp \
    circle.cpp \
    ellipse.cpp \
    main.cpp \
    memento.cpp \
    painter.cpp \
    rectangle.cpp \
    shape.cpp \
    shape1property.cpp \
    shape2property.cpp \
    shapes.cpp \
    square.cpp

DISTFILES +=

RESOURCES += \
    resources.qrc

