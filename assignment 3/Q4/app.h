#ifndef APP_H
#define APP_H

#include <QWidget>
#include "studentlist.h"
#include "studentserializer.h"

class QPushButton;
class QListWidget;
class QProcess;
class QLabel;
class QWidget;

class App :  public QWidget
{
    Q_OBJECT
private:

    QListWidget* studentssListWidget;
    QListWidget* modulesList;
    QPushButton* addStudent;
    QProcess *process;
    // static StudentList students;

    StudentContainer* sn;

    QWidget* studentWidget;
    QLabel* studentCount;
    QLabel* studentAvarage;

    StudentSerializer serializer;

public:
    explicit App(QWidget *parent = nullptr);

    void setupUI();
    void handleDataUpdate();
    void connectProcess();


signals:

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // APP_H
