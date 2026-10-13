// Purpose: Provide a simplified interface to a complex subsystem.

class Database {
public:
    void connect() {
        qDebug() << "Database connected";
    }
};

class Logger {
public:
    void start() {
        qDebug() << "Logger started";
    }
};

class ApplicationFacade {
private:
    Database database;
    Logger logger;

public:
    void initialize() {
        logger.start();
        database.connect();
    }
};

// USAGE:
ApplicationFacade app;
app.initialize();

// Instead of directly coordinating several subsystems, the client uses one simplified method