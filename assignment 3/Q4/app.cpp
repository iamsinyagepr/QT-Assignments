#include "app.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStringListModel>

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QVariant>
#include <QString>
#include <string>
#include <QLabel>



// get data from string
std::vector<std::string> getData(std::string src) {

    std::vector<std::string> data;
    char delimiter = '#';
    std::string temp = "";


    for(char c : src) {
        if(c == delimiter) {
            data.push_back(temp);
            temp = "";
            continue;
        }

        temp += c;
    };

    if(!temp.empty()) data.push_back(temp);

    return data;

}

App::App(QWidget *parent) :
    QWidget{parent},
    studentssListWidget(new QListWidget),
    modulesList(new QListWidget),
    addStudent(new QPushButton("Add Student")),
    process(new QProcess),
    studentWidget(new QWidget()),
    studentCount(new QLabel("Number Of Students: 0")),
    studentAvarage(new QLabel("Student Average: 0%")),
    serializer(StudentSerializer())
{

    //setup instance for reuse
    StudentList& instance = StudentList::getInstance();
    sn = instance.getStudentInstance();

    handleDataUpdate();

    setupUI();
    connectProcess();
}

void App::connectProcess() {


    QObject::connect(process, &QProcess::readyRead, [this]() {

        QByteArray outputData = process->readAllStandardOutput();
        std::vector<std::string> student = getData(outputData.toStdString());

        sn->addStudent(
            std::stoi(student.at(0)),
            QString::fromStdString(student.at(1)),
            std::stod(student.at(2))
        );

        handleDataUpdate();
    });

    QObject::connect(process, &QProcess::readyReadStandardError, [this]() {
        QByteArray errorData = process->readAllStandardError();
        qWarning().noquote() << "STDERR:" << errorData;
    });

    QObject::connect(process, &QProcess::finished, process, [this](int exitCode) {
        qDebug() << "Process finished with exit code:" << exitCode;
        process->close();
    });


}

void App::handleDataUpdate() {

    // handle student list
    studentssListWidget->clear();

    for(Student* student : *sn->getStudents()) {

        studentssListWidget->addItem(
            QString("%1 %2").arg(
                QString::number(student->getNumber()),
                student->graduate() ? ": (GRADUATE)" : ""
            )
        );
    }

    studentCount->setText(
        QString("Number Of Students: %1").arg(sn->getStudentCount())
        );

    connect(studentssListWidget, &QListWidget::currentItemChanged, this, [this]() {
        modulesList->clear();

        int current = studentssListWidget->currentRow();
        if(current < 0) {
            studentWidget->hide();
            return;
        }

        studentWidget->show();

        Student* student = sn->getStudent(current);
        studentAvarage->setText(
            QString("Student Average: %1\%").arg(student->average())
        );
        for(Module* module : student->getModules()) {

            QList<QVariant> data = module->getModule();
            modulesList->addItem(
                QString("%1 : %2\%")
                    .arg(data.at(0).toString(), data.at(1).toString())
            );
        }
    });

}

void App::setupUI() {

    QHBoxLayout* appLayout = new QHBoxLayout(this);

    QVBoxLayout* studentsLayout = new QVBoxLayout();

    studentsLayout->addWidget(addStudent); // add student button
    studentsLayout->addWidget(studentssListWidget); // student list
    studentsLayout->addWidget(studentCount); // student list size

    QVBoxLayout* studentLayout = new QVBoxLayout();
    studentLayout->addWidget(studentAvarage);
    studentLayout->addWidget(modulesList);
    studentWidget->setLayout(studentLayout);
    studentWidget->hide();
    // studentLayout->;

    appLayout->addLayout(studentsLayout);
    appLayout->addWidget(studentWidget);


    connect(addStudent, &QPushButton::clicked, this, [this]() {

        #ifdef Q_OS_WIN
            process->start("Q1.exe", QStringList() << "/c" << "dir");
        #else
            process->start("ls", QStringList() << "-la");
        #endif
    });

}

void App::closeEvent([[maybe_unused]] QCloseEvent *event) {
    qDebug() << "Application closed";
    sn->getSerializer()->saveToXML();
}