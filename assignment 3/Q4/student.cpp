#include "student.h"
#include "module.h"

void Student::setStudentNumber(int sn)
{ studentNumber = sn; }

double Student::average() const
{

    double av = 0;

    for (int i = 0; i < modules.size(); i++)
    {
        Module* module = modules.at(i);
        av += module->getModule().at(1).toDouble();
    }

    return av/modules.size();
}

bool Student::graduate() const
{
    //if the student has passed 5 modules
    //of which at most 2 are 1st year
    // modules and at least 1 is a 3rd year module
    int year1ModulesPassed = 0;
    int year3ModulesPassed = 0;
    int passedModules = 0;

    for(Module* mod : modules) {
        QList<QVariant> data = mod->getModule();
        QString code = data.at(0).toString();
        double marks = data.at(1).toDouble();


        bool passed =  marks > 49;
        if(passed) passedModules++;

        if(code.at(3) == '1' && passed) {
            year1ModulesPassed++;
        }

        if(code.at(3) == '3' && passed) {
            year3ModulesPassed++;
        }
    }

    bool passed5modules = passedModules >= 5;
    bool atMost2FirstYear =  year1ModulesPassed <= 2 && year1ModulesPassed > 0;
    bool atLeast1ThirdYear = year3ModulesPassed >= 1;

    return passed5modules && atMost2FirstYear && atLeast1ThirdYear;
}

int Student::getNumber() const
{ return studentNumber; }

int Student::checkModule(QString code) const
{
    int index = 0;

    for(Module* module : modules) {
        if(module->getModule().at(0).toString() == code) return index;
         ++index;
    }

    return -1;
}

void Student::addModule(QString code, double marks)
{

    int exists = checkModule(code);

    if(exists < 0) {
        modules.append(new Module(code, marks));
        return;
    }

    Module* module = modules.at(exists);
    module->setMarks(marks);
}

QList<Module*> Student::getModules() const
{ return modules; }