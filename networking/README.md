
# Network Configuration Information #
## Network Hardware IPs ##
| Device             | Location      | Function                                          | IP            |
| :----------------- |:-------------:| :------------------------------------------------ | :------------:|
| [TP-Link AC1750](https://www.tp-link.com/us/home-networking/wifi-router/archer-a7/) | On-board | Main router for the boat | `192.168.1.1`|
| [GL.iNet GL-AR750](https://www.gl-inet.com/products/gl-ar750/) | On-board | Provide internet connection to `tusecurewireless` | `192.168.0.1` |
| [TP-Link AC1200](https://www.tp-link.com/us/home-networking/wifi-router/archer-a5/) | Shore-side | Create shore-side wireless bridged network | `192.168.1.2` |

## Reserved IPs ##
| Hostname             | Interface     | IP              |
| :------------------- |:-------------:| :--------------:|
| roboboat-Pi4         | Ethernet      | `192.168.1.101` |
| roboboat-Pi4         | WiFi          | `192.168.1.102` |
| Roboboat-TX2         | Ethernet      | `192.168.1.103` |
| Roboboat-TX2         | Wifi          | `192.168.1.104` |


# Network Maintenance & Additional Information #
## Restoring the Network ##
If the network is accidentally misconfigured, use the router's provided [backup files](RouterBackups/) to restore functionality. 

## Connecting to the Internet ##
The GL.iNet GL-AR750 connects all network devices to the internet. Though its management portal, a connection to the `tusecurewireless` network can be established. Follow the instructions in the [Connect_to_tusecurewireless.md](Connect_to_tusecurewireless.md) file to establish an internet connection.

## Hardware Documentation ##
* TP-Link AC1750 (Archer A7): | [User Guide](RouterManuals/AC1750A7_UserGuide.pdf) | [Quick Installation Guide](RouterManuals/AC1750A7_QuickInstallationGuide.pdf) | [Datasheet](RouterManuals/AC1750A7_DataSheet.pdf) |
* TP-Link AC1200 (Archer A5): | [User Guide](RouterManuals/AC1200A5_UserGuide.pdf) | [Quick Installation Guide](RouterManuals/AC1200A5_QuickInstallationGuide.pdf) |
* GL.iNet GL-AR750: | [Docs Website](https://docs.gl-inet.com/en/3/setup/travel_ac_router/first-time_setup/) | [Docs Website - PDF Version](RouterManuals/GL-AR750_UserGuide.pdf) | 

