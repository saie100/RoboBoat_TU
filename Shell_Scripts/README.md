# General Use of the Shell Scripts #

All of the boat's core tasks are started & stopped from the RPi 4. The ROS master node is run on the RPi 4. ROS nodes are launched on the TX2 through commands sent over SSH.

SSH keys are generated that allow the RPi 4 to send commands to the TX2 over SSH without having to enter a password for each command sent. See [this guide](https://www.linuxbabe.com/linux-server/setup-passwordless-ssh-login) for instructions on how to generate an SSH key pair for password-less ssh.

---
## Starting and stopping the boat's software ##
1. Supply power to the boat (battery or wall power). The RPi 4 will turn on automatically when power is supplied, but the power button on the TX2 needs to be pressed to turn it on.
1. Connect power to the emergency system and turn on the Emergency Receiver by switching the two switches on the wire harness that connects the bottom of the boat to the top of the boat to the on position.
1. SSH into *ubuntu* account the RPi 4 at 10.19.122.101
```
ssh ubuntu@10.19.122.101
```
1. Once logged in, navigate to this directory on the RPi 4
```
cd RoboBoat_TU/Shell_Scripts/
```
1. Start the boat using the `noGUI` version of the starting shell script
```
./Startboat-noGUI.sh
```
1. After the boat is started, it can be stopped by pressing the **Enter** key when in the terminal window. It is important to stop the boat this and NOT to simply terminate the shell script process (**Ctrl+C**) as this will not stop the LIDAR's motor.

---
## Starting and stopping the boat's software for debugging ##
1. Login to the RPi 4's XRDP session at 10.19.122.101 using the Microsoft Remote Desktop ([Windows](https://www.microsoft.com/en-us/p/microsoft-remote-desktop/9wzdncrfj3ps?activetab=pivot:overviewtab)/[Mac](https://apps.apple.com/us/app/microsoft-remote-desktop/id1295203466?mt=12))
1. Once logged in, navigate to this directory on the RPi 4
```
cd RoboBoat_TU/Shell_Scripts/
```
1. Start the boat using the `GUI` version of the starting shell script. A new terminal window will be created with tabs corresponding to each of the processes that were started on the boat that can be monitored while debugging.
```
./Startboat-GUI.sh
```
1. After the boat is started, it can be stopped using another shell script
```
./killboat.sh
```

---
## Creating rosbag recordings ##
1. Over SSH
  1. After the boat is started, open a new terminal window or a new SSH session on the RPi 4.
  ```
  ssh ubuntu@10.19.122.101
  ```
  1. Navigate to this directory on the RPi 4
  ```
  cd RoboBoat_TU/Shell_Scripts/
  ```
  1. Start recording a new rosbag file that will be saved in the `~/rosbag_files` directory on the TX2.
  ```
  ./start-rosbag.sh
  ```
  1. To stop the recording, terminate the process by pressing **Ctrl+C**. Always remember to stop the rosbag recording before stopping the ROS system.
1. In the GUI
  1. Open a new terminal window or tab
  1. Navigate to this directory on the RPi 4
  ```
  cd RoboBoat_TU/Shell_Scripts/
  ```
  1. Start recording a new rosbag file that will be saved in the `~/rosbag_files` directory on the TX2.
  ```
  ./start-rosbag.sh
  ```
  1. To stop the recording, terminate the process by pressing **Ctrl+C**. Always remember to stop the rosbag recording before stopping the ROS system.
