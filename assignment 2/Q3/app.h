#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QObject>
#include "shapes.h"

class QComboBox;
class QSpinBox;
class QPaintEvent;
class QPushButton;
class QLabel;
class QListWidget;

class App : public QWidget
{
    Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);

    void setupGUI();
    void loadShapes();
    void loadXML();
    void updateXML();
    // ~App();
    // QWidget* painterParent;
    // QPainter* painter;
    QListWidget *listWidget;
    Shapes* shapes;

    QComboBox* shapeSelector;
    QComboBox* penColor;
    QComboBox* fillColor;

    QSpinBox* penWidth;
    QSpinBox* property1;
    QSpinBox* property2;

    QSpinBox* width;
    QSpinBox* size;
    QSpinBox* height;
    QSpinBox* radius;

    QPushButton* addShape;
    QPushButton* nextShape;
    QPushButton* prevShape;
    QLabel* pagenation;


};


#endif // APP_H
