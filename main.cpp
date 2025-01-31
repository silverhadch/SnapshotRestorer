#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

bool isSnapshotBooted() {
    // Read /proc/cmdline to detect if a snapshot is in use
    QFile file("/proc/cmdline");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    QString cmdline = in.readAll();

    // Check if there's a snapshot present in the cmdline
    QRegularExpression re("/@/.snapshots/([0-9]+)/snapshot");
    QRegularExpressionMatch match = re.match(cmdline);
    return match.hasMatch();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Only proceed if the system has booted into a snapshot
    if (isSnapshotBooted()) {
        // Extract snapshot ID from /proc/cmdline
        QFile file("/proc/cmdline");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        QString cmdline = in.readAll();

        // Updated regex to match snapshot ID with multiple digits
        QRegularExpression re("/@/.snapshots/([0-9]+)/snapshot");
        QRegularExpressionMatch match = re.match(cmdline);
        QString snapshotId = match.captured(1); // Capture the snapshot ID

        if (!snapshotId.isEmpty()) {
            // Prompt to restore snapshot
            QMessageBox msgBox;
            msgBox.setWindowTitle("Snapshot Restore");
            msgBox.setText("You have booted into a snapshot. Do you want to restore it?");
            msgBox.setInformativeText("Snapshot ID: " + snapshotId);
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);

            int ret = msgBox.exec();

            if (ret == QMessageBox::Yes) {
                // If user clicks Yes, perform rollback using pkexec
                QProcess::execute("pkexec", QStringList() << "snapper" << "rollback" << snapshotId);
                // Show success message
                QMessageBox::information(nullptr, "Snapshot Restored", "Snapshot restored successfully!");
            }
        }
    }

    return a.exec();
}

