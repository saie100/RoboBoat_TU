# XRDP Setup on the Jetson TX2 with Jetpack 4.3

Disclaimer: We are still not exactly sure how this works, but the solution presented below is the result of combining multiple other solutions we found though Google. 

1. Install a new desktop environment (xfce4 in this demo). We were not able to get this to work with the pre-installed desktop environment.
```
sudo apt update
sudo apt install xfce4 xfce4-goodies xorg dbus-x11 x11-xserver-utils
```

2. Install XRDP and add the `xrdp` user to the `ssl-cert` group.
```
sudo apt install xrdp
sudo adduser xrdp ssl-cert
```

3. Configure XDRP to use the xfce4 desktop environment we installed in Step 1.
   * Add `exec startxfce4` to the end of the `/etc/xrdp/xrdp.ini` file.
   * `echo xfce4-session > ~/.xsession`

4. Restart XRDP
```
sudo systemctl restart xrdp
```

Now attempt to log into XRDP for the first time!

