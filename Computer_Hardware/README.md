# Computer Hardware #

## Configuration Guides ##


## [Raspberry Pi 4 Ubuntu Server - A Guide by James Chambers](https://jamesachambers.com/raspberry-pi-4-ubuntu-server-desktop-18-04-3-image-unofficial/) ##
This guide was used to install Ubuntu Server on the Raspberry Pi 4 so that ROS did not need to be compipled when installing.   

## [Develop on SSD - NVIDIA Jetson TX Dev Kits](https://youtu.be/ZpQgRdg8RmA) ##
The guide listed below was used to configure the TX2 to boot from an SSD. 

*Note: Only follow the guide up 4:57. Do not follow the steps after this time.*
   

## Creating/Restoring Backups Using a Linux Computer ##
### Creating a Backup ###
1. Connect the Micro SD card from the Raspberry Pi or the SSD from the TX2 to the computer where the backup will be made. 
1. Unmount the Micro SD card or the SSD from the OS - this can be done in the disk manager. 
1. Use the following command after substituting the path to the Micro SD card or the SSD and specifing a name for the compressed backup of the drive.
```
	sudo dd if=/dev/r[INSERT_DISK_HERE(disk2)] BS=32m | gzip > /[INSERT_PATH_AND_BACKUP_NAME_HERE].gz
```
### Restoring a Backup ###
1. To write the backup to a Micro SD card or SSD, first connect the drive to the computer and unmount the disk. 
1. Use the following command after substituting the name of the drive to be written to and the name of the backup file.  
```
	gzip -dc /[INSERT_PATH_AND_BACKUP_NAME_HERE].gz | sudo dd of=/dev/r[INSERT_DISK_HERE(disk3)] BS=32m
```

## [DOWNLOAD: Raspberry Pi 4B - Ubuntu Server Backup](https://drive.google.com/uc?export=download&confirm=n3Q3&id=1xh1nTMyLx9h_HU1v4K-zJbxssuq-ram7) ##
*Note: This backup must be restored to a Micro SD Card with a capacity greater than or equal to 64GB*

## [DOWNLOAD: Jetson TX2 - NVIDIA Jetpack Backup](https://drive.google.com/uc?id=1ChVVHlB_Lbe0hwe4Fh0JUX25fiE8jmSy&export=download) ##
*Note: This backup must be restored to an SSD with a capacity greater than or equal to 500GB*
