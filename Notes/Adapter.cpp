// Purpose: Convert an existing interface into another interface expected by client code.

class OldPrinter {
public:
    void oldPrint() {
        qDebug() << "Old printing API";
    }
};

class Printer {
public:
    virtual ~Printer() = default;
    virtual void print() = 0;
};

class PrinterAdapter : public Printer {
private:
    OldPrinter* oldPrinter;

public:
    explicit PrinterAdapter(OldPrinter* p)
        : oldPrinter(p) {}

    void print() override {
        oldPrinter->oldPrint();
    }
};