#ifndef APP_H
#define APP_H

#include <QWidget>

class QLineEdit;
class QLabel;
class QPushButton;


class App :  public QWidget
{
    Q_OBJECT
private:
    QLineEdit* studentNumber;
    QLabel* studentNumberLabel;

    QLineEdit* moduleCode;
    QLabel* moduleCodeLabel;

    QLineEdit* marks;
    QLabel* marksLabel;

    QPushButton* submitButton;

public:
    explicit App(QWidget *parent = nullptr);

    void setupUI();

signals:
};

#endif // APP_H
