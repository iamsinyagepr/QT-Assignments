// QProcess launches a separate operating system process
/**
 * waitForFinished() blocks the calling thread so it should generally be avoided in a responsive GUI thread, instead connect to finished and readyReadStandardOutput() for asynchronous operation.
 */



QProcess process;

process.start(
    "python3",
    QStringList{"script.py"}
);

if (process.waitForStarted()) {
    process.waitForFinished();

    QByteArray output =
        process.readAllStandardOutput();

    qDebug() << output;
}

/**
 * QThread is for threads; QProcess is for seperate programs/processes; QMutex protexts shared state
 * 
 * QThread
 * - executes within the same process
 * - Threads share process memory
 * - Lower isolation
 * - Shared-state synchronisation may be required
 * 
 * QProcess
 * - Starts another process
 * - Processes have seperate address spaces
 * - Greater isolation
 * - Inter-process communication may be required
 */