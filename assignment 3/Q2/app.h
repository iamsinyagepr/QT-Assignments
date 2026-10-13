#ifndef APP_H
#define APP_H

#include <QWidget>

class QPushButton;
class QListWidget;

class App :  public QWidget
{
    Q_OBJECT
private:

    QListWidget* marksList;
    QPushButton* submitButton;

public:
    explicit App(QWidget *parent = nullptr);

    void setupUI();



signals:
};

#endif // APP_H
