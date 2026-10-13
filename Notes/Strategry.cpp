// Purpose: Define interchangeable algorithms behind a common interface.

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void pay(double amount) = 0;
};

class CardPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        qDebug() << "Card:" << amount;
    }
};

class CashPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        qDebug() << "Cash:" << amount;
    }
};

class Checkout {
private:
    PaymentStrategy* strategy;

public:
    explicit Checkout(PaymentStrategy* s)
        : strategy(s) {}

    void process(double amount) {
        strategy->pay(amount);
    }
};


// USAGE
CardPayment card;
CashPayment cash;

Checkout checkout(&card);
checkout.process(100);

Checkout anotherCheckout(&cash);
anotherCheckout.process(100);