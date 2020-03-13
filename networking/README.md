## Network Hardware IPs ##

| Device             | Location      | Function                                          | IP            |
| :----------------- |:-------------:| :------------------------------------------------ | :------------:|
| [TP-Link AC1750](https://www.tp-link.com/us/home-networking/wifi-router/archer-c7/) | On-board | Main router for the boat | `192.168.1.1`|
| [GL.iNet GL-AR750](https://www.gl-inet.com/products/gl-ar750/) | On-board | Provide internet connection to `tusecurewireless` | `192.168.0.1` |
| [TP-Link AC1200](https://www.tp-link.com/us/home-networking/wifi-router/archer-a5/) | Shore-Side | Create shore-side wireless bridged network | `192.168.1.2` |


## Reserved IPs ##

| Hostname             | Interface     | IP              |
| :------------------- |:-------------:| :--------------:|
| roboboat-Pi4         | Ethernet      | `192.168.1.101` |
| roboboat-Pi4         | WiFi          | `192.168.1.102` |
| Roboboat-TX2         | Ethernet      | `192.168.1.103` |
| Roboboat-TX2         | Wifi          | `192.168.1.104` |



## Hardware Documentation ##
* TP-Link AC1750: [User Guide](/RouterManuals/GL-AR750_UserGuide.pdf)
