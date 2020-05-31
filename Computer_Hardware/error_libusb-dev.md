# TX2 libusb Error #

The following error may occur when attempting to launch the ZED developer tools, such as ZED Explorer:

```
[ERROR] [1580159126.137504584]: Failed to load nodelet [/zed/zed_node] of type [zed_wrapper/ZEDWrapperNodelet] even after refreshing the cache: Failed to load library /home/roboboat/catkin_ws/devel/lib//libZEDWrapper.so. Make sure that you are calling the PLUGINLIB_EXPORT_CLASS macro in the library code, and that names are consistent between this macro and your XML. Error string: Could not load library (Poco exception = libusb-0.1.so.4: cannot open shared object file: No such file or directory)
[ERROR] [1580159126.137717192]: The error before refreshing the cache was: Failed to load library /home/roboboat/catkin_ws/devel/lib//libZEDWrapper.so. Make sure that you are calling the PLUGINLIB_EXPORT_CLASS macro in the library code, and that names are consistent between this macro and your XML. Error string: Could not load library (Poco exception = libusb-0.1.so.4: cannot open shared object file: No such file or directory)
```

## The Solution ##

Install ***libusb***:

```
sudo apt-get install libusb-dev
```
