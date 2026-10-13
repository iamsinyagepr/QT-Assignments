#include "app.h"

#include <iostream>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>


App::App(QWidget *parent)
    : QWidget{parent},
    studentNumber(new QLineEdit()),
    studentNumberLabel(new QLabel("Student Number")),

    moduleCode(new QLineEdit()),
    moduleCodeLabel(new QLabel("Module Code")),

    marks(new QLineEdit()),
    marksLabel(new QLabel("Marks")),

    submitButton(new QPushButton("Add Student"))


{
    setupUI();

    QMessageBox* message = new QMessageBox(this);
    message->setIcon(QMessageBox::Critical);

    connect(submitButton, &QPushButton::clicked, this, [this, message]() {

        if(!studentNumber->hasAcceptableInput()) {
            // qCritical() << "Student number should be 4 digits.";

            message->setText("Student number should be 4 digits");
            message->show();

            studentNumber->focusWidget();
            std::cerr << "Student number should be 4 digits.\n" << std::flush;

            return;
        }

        if(!moduleCode->hasAcceptableInput()){
            std::cerr <<  "Module code is invalid.\n" << std::flush;

            message->setText("Module code is invalid.");
            message->show();
            moduleCode->focusWidget();
            return;
        }

        int year = moduleCode->text().at(3).digitValue();
        if(year > 3 || year < 1) {
            std::cerr <<  "Third value of module can only be 1, 2 or 3.\n" << std::flush;

            message->setText("4th character can only be 1, 2 or 3 for module year.");
            message->show();
            return;
        }

        if(!marks->hasAcceptableInput()) {
            std::cerr << "Marks should be between 0 and 100.\n" << std::flush;
            message->setText("Student marks can only be between 0 and 100");
            message->show();
            return;
        }

        QString st_num = studentNumber->text();
        studentNumber->clear();

        QString mod_cde = moduleCode->text();
        moduleCode->clear();

        QString mrks = marks->text();
        marks->clear();

        std::cout << QString("%1#%2#%3").arg(st_num, mod_cde, mrks).toStdString() << std::flush;

        message->setIcon(QMessageBox::Information);
        message->setText("Student infomation correct.");
        message->show();

    });
}

void App::setupUI() {

    QFormLayout* formLayout = new QFormLayout(this);

    // student number
    studentNumber->setInputMask("9999");
    formLayout->addRow(studentNumberLabel, studentNumber);

    formLayout->addRow(new QLabel("Add Module"));

    moduleCode->setInputMask(">AAA!999H;_"); //TODO: verify before submission
    formLayout->addRow(moduleCodeLabel, moduleCode);


    QRegularExpression rx("^(0?[1-9]|[1-9][0-9]|100)$");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    marks->setValidator(validator);
    formLayout->addRow(marksLabel, marks);

    formLayout->addWidget(submitButton);

}