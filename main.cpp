#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QRegularExpression>
#include <QProcess>
#include <QSharedMemory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Prevent multiple instances
    QSharedMemory sharedMemory;
    sharedMemory.setKey("SnapshotRestorerInstance");

    if (!sharedMemory.create(1)) {
        // Another instance is already running
        return 0;
    }

    // Check if booted into a snapshot
    QFile cmdlineFile("/proc/cmdline");
    if (cmdlineFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString cmdline = cmdlineFile.readAll();
        QRegularExpression re(R"(/\.snapshots/(\d+)/snapshot)");
        QRegularExpressionMatch match = re.match(cmdline);

        if (match.hasMatch()) {
            QString snapshotId = match.captured(1);

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Snapshot Detected",
                                          "You are booted into snapshot #" + snapshotId +
                                          ". Do you want to restore it?",
                                          QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                QProcess process;
                process.start("pkexec", {"snapper", "rollback", snapshotId});
                process.waitForFinished();

                // Display output from the snapper rollback command
                QString output = process.readAllStandardOutput();
                QString errorOutput = process.readAllStandardError();

                QMessageBox::information(nullptr, "Snapshot Restored", 
                                         output.isEmpty() ? errorOutput : output);
            }
        }
    }

    return 0;
}

