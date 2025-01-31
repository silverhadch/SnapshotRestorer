#include <QApplication>
#include <QMessageBox>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

QString getSnapshotId() {
    QFile file("/proc/cmdline");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString cmdline = in.readAll();
        file.close();

        QRegExp snapshotPattern("/@/.snapshots/(\\d+)/snapshot");
        if (snapshotPattern.indexIn(cmdline) != -1) {
            QString snapshotId = snapshotPattern.cap(1);
            return snapshotId.trimmed();
        }
    }
    return "";
}

void promptForRollback(const QString &snapshotId) {
    int reply = QMessageBox::question(nullptr, "Restore Snapshot",
                                       "Do you want to restore snapshot ID: " + snapshotId + "?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Execute the rollback command and capture its output
        QProcess process;
        process.start("pkexec", QStringList() << "snapper" << "rollback" << snapshotId);
        process.waitForFinished();

        // Get the output of the command
        QString output = process.readAllStandardOutput() + "\n" + process.readAllStandardError();

        // Show a message box with the result
        QMessageBox::information(nullptr, "Snapshot Restored", "Snapshot " + snapshotId + " restored successfully.\n\n" + output);
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString snapshotId = getSnapshotId();
    if (!snapshotId.isEmpty()) {
        promptForRollback(snapshotId);
    } else {
        QMessageBox::warning(nullptr, "No Snapshot Found", "No snapshot found to restore.");
    }

    return app.exec();
}

