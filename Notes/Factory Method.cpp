class Document {
public:
    virtual ~Document() = default;
    virtual void open() = 0;
};

class PdfDocument : public Document {
public:
    void open() override {
        qDebug() << "Opening PDF";
    }
};

class Application {
public:
    virtual ~Application() = default;

    virtual std::unique_ptr<Document>
    createDocument() const = 0;

    void openDocument() const {
        auto doc = createDocument();
        doc->open();
    }
};

class PdfApplication : public Application {
public:
    std::unique_ptr<Document>
    createDocument() const override {
        return std::make_unique<PdfDocument>();
    }
};