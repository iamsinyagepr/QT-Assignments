#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QObject>

class QComboBox;
class QSpinBox;
class QPaintEvent;


class App : public QWidget
{
    Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);

    void setupGUI();
    // ~App();
    // QWidget* painterParent;
    // QPainter* painter;

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


};


#endif // APP_H
