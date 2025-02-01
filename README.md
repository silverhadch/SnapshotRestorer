# Snapshot Restorer

A simple tool for openSUSE that automatically detects if you have booted into a BTRFS snapshot and prompts you to restore it. This application runs on boot and will allow you to quickly restore a snapshot with a simple "Yes/No" prompt.

## Features

- Automatically detects if the system has booted into a snapshot using `grep` on `/proc/cmdline`.
- Prompts the user to restore the snapshot with a confirmation message.
- Provides a graphical interface with a `Yes/No` prompt.
- Works specifically for openSUSE systems with BTRFS snapshots.
- Runs the rollback command (`snapper rollback`) when the user accepts to restore the snapshot.

## Installation

To install and set up the `SnapshotRestorer` application, follow these steps:

### Clone the Repository and Install

1. Clone this repository:

```bash
git clone https://github.com/silverhadch/SnapshotRestorer.git
```

2. Navigate to the project directory:

```bash
cd SnapshotRestorer
```

3. Execute the install script to build and install the application:

```bash
./install.sh
```

This will:
- Install the necessary dependencies automatically.
- Compile the `SnapshotRestorer` application.
- Install the binary into `/usr/bin`.
- Install the `.desktop` file into `/usr/share/applications`.
- And make an Systemwide Autostart.

### Usage

Once installed, the application will automatically detect if the system is booted into a snapshot. If a snapshot is detected, you will be prompted with the option to restore it.

1. Upon boot, if the system detects a snapshot, you will see a graphical prompt asking you whether you'd like to restore the snapshot.
2. If you choose "Yes", the snapshot restore process will begin, and the snapshot will be rolled back using the `snapper rollback` command.

### Uninstall

To uninstall the application, you can remove the binary and the `.desktop` file manually:

```bash
sudo rm /usr/bin/SnapshotRestorer
sudo rm /usr/share/applications/snapper-boot-restorer.desktop
sudo rm /etc/xdg/autostart/snapper-boot-restorer.desktop
```

### License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0). See the [LICENSE](LICENSE) file for more details.

## Contributing

Feel free to fork this repository and contribute by submitting pull requests. If you encounter any bugs or have suggestions, please open an issue in the issue tracker.

## Acknowledgments

- **openSUSE**: For providing a great platform to develop and test the tool.
- **BTRFS**: For providing snapshots as a way to protect data and simplify rollback functionality.
- **Garuda Linux Snapper Tools**: This project is inspired by Garuda Linux's Snapper Tools, which offer similar snapshot restore functionality when booting into snapshots.

## Contact

If you have any questions or need help with the tool, feel free to open an issue in the repository, or reach out via the contact information in the issue tracker.

