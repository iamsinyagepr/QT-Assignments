// Purpose: Create families of related objects without specifying their concrete classes to client code.

class Button {
public:
    virtual ~Button() = default;
    virtual void draw() = 0;
};

class LightButton : public Button {
public:
    void draw() override {
        qDebug() << "Light button";
    }
};

class DarkButton : public Button {
public:
    void draw() override {
        qDebug() << "Dark button";
    }
};

class UIFactory {
public:
    virtual ~UIFactory() = default;

    virtual std::unique_ptr<Button>
    createButton() = 0;
};

class DarkFactory : public UIFactory {
public:
    std::unique_ptr<Button>
    createButton() override {
        return std::make_unique<DarkButton>();
    }
};