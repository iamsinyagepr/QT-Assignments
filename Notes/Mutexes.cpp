//  A mutex protects a critical section.
// QMutextLocker automatically releases the mutext when the locker goes out of scope

QMutex mutex;
int counter = 0;

void increment() {
    QMutexLocker lock(&mutex);
    ++counter;
}

