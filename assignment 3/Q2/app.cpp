#include "app.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStringListModel>

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>

App::App(QWidget *parent) :
    QWidget{parent},
    marksList(new QListWidget),
    submitButton(new QPushButton("Add Student"))
{
    setupUI();
}

void App::setupUI() {

    QProcess *process = new QProcess(this);

    // data
    QStringList list;

    QObject::connect(process, &QProcess::readyRead, [process, this]() {
        QByteArray outputData = process->readAllStandardOutput();
        marksList->addItem(outputData);
    });

    QObject::connect(process, &QProcess::readyReadStandardError, [process]() {
        QByteArray errorData = process->readAllStandardError();
        qWarning().noquote() << "STDERR:" << errorData;
    });

    QObject::connect(process, &QProcess::finished, process, [process](int exitCode) {
        qDebug() << "Process finished with exit code:" << exitCode;
        process->close();
    });

    connect(submitButton, &QPushButton::clicked, this, [process]() {

        #ifdef Q_OS_WIN
            process->start("Q1.exe", QStringList() << "/c" << "dir");
        #else
            process->start("ls", QStringList() << "-la");
        #endif
    });


    QVBoxLayout* appLayout = new QVBoxLayout(this);
    appLayout->addWidget(marksList);
    appLayout->addWidget(submitButton);

}
