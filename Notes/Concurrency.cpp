// Concurrency means multiple tasks make progress during overlapping periods

// Parallelism means tasks execute simultaneously, such as on different CPU cores

// Concurrency does not always imply parallelism

/**
 * QThread - Manage threads and their event loops
 * QThreadPool - Reuse worker threads
 * QRunnable - Define tasks for thread pools
 * QtConcurrent - Higher-level concurrent operations
 * QMutex - Mutual exclusion
 * QReadWriteLock - Multiple readers or one writer
 * QSemaphore - Control access to limited resources
 * QWaitingCondition - Wait for a condition
 * QAtomicInteger - Atomic integer operations
 * QProcess - Launch and communicate with external process
 * */ 

 // Multithreading with QThread
 // A common implementation is to move a worker QObject into a thread

class Worker : public QObject {
    Q_OBJECT

public slots:
    void process() {
        for (int i = 0; i < 5; ++i) {
            qDebug() << "Working:" << i;
        }

        emit finished();
    }

signals:
    void finished();
};

// Thread Setup
QThread* thread = new QThread;
Worker* worker = new Worker;

worker->moveToThread(thread);

QObject::connect(
    thread, &QThread::started,
    worker, &Worker::process
);

QObject::connect(
    worker, &Worker::finished,
    thread, &QThread::quit
);

QObject::connect(
    worker, &Worker::finished,
    worker, &QObject::deleteLater
);

QObject::connect(
    thread, &QThread::finished,
    thread, &QObject::deleteLater
);

thread->start();

// The worker's procees() method executes in the worker thread when the signal is delivered though the appropriate connection

/**
 * \important
 * GUI widgets must be accessed  from the GUI thread.
 * Worker threads should communicate results through signals and slots or another safe mechanism
 */