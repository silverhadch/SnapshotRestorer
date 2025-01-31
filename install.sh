#!/bin/bash

# Set the installation paths
INSTALL_DIR_BIN="/usr/bin"
INSTALL_DIR_APPS="/usr/share/applications"
DESKTOP_FILE="/usr/share/applications/snapper-boot-restorer.desktop"

# Step 1: Install dependencies
echo "Installing dependencies..."
sudo zypper refresh
sudo zypper install -y libqt5-qtbase-devel pkexec cmake make gcc

# Step 2: Compile the SnapshotRestorer application
echo "Compiling SnapshotRestorer..."
mkdir -p build
cd build
cmake ..
make

# Step 3: Install the compiled binary to /usr/bin
echo "Installing SnapshotRestorer binary to $INSTALL_DIR_BIN..."
sudo cp SnapshotRestorer $INSTALL_DIR_BIN/

# Step 4: Install the .desktop file to /usr/share/applications
echo "Creating and installing the .desktop file..."
sudo tee $DESKTOP_FILE << EOF
[Desktop Entry]
Version=1.0
Name=Snapshot Restorer
Comment=Restore a snapshot if detected on boot
Exec=sh -c "grep -q '.snapshots' /proc/cmdline && sleep 3 && /usr/bin/SnapshotRestorer"
Icon=timeshift
Terminal=false
Type=Application
X-GNOME-Autostart-enabled=true
X-KDE-autostart-after=panel
EOF

# Step 5: Ensure everything is executable
echo "Making sure everything is executable..."
sudo chmod +x $INSTALL_DIR_BIN/SnapshotRestorer
sudo chmod +x $DESKTOP_FILE

sudo cp $DESKTOP_FILE /etc/xdg/autostart/

# Step 6: Clean up
echo "Cleaning up build directory..."
cd ..
rm -rf build

# Done
echo "Installation complete! You can now run SnapshotRestorer."

