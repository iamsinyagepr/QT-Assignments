#ifndef HELPERS_H
#define HELPERS_H

#pragma once
#include <QString>
#include <QStringList>

#include <QPainter>
#include <QRect>
#include <QColor>

inline QString S_CIRCLE = QStringLiteral("CIRCLE");
inline QString S_SQUARE = QStringLiteral("SQUARE");
inline QString S_ELLIPSE = QStringLiteral("ELLIPSE");
inline QString S_RECTANGLE = QStringLiteral("RECTANGLE");

inline QStringList SHAPES_LIST = {S_CIRCLE, S_SQUARE, S_ELLIPSE, S_RECTANGLE};

enum COLORS {
    YELLOW,
    RED,
    BLUE,
    GREEN,
    BLACK
};

enum SHAPES {
    CIRCLE,
    SQUARE,
    ELLIPSE,
    RECTANGLE
};

inline QColor getColor(int index) {
    switch(index) {
    case 0:
        return Qt::yellow;
    case 1:
        return Qt::red;
    case 2:
        return Qt::blue;
    case 3:
        return Qt::green;
    default:
        return Qt::black;
    }
}

inline std::vector<int> getXY(QPainter* painter, int width, int height) {
    QRect rect = painter->viewport();

    int canvasWidth = rect.width();
    int canvasHeight = rect.height();

    int x = (canvasWidth - width) / 2;
    int y = (canvasHeight - height) / 2;

    return { x, y };
}

#endif // HELPERS_H
