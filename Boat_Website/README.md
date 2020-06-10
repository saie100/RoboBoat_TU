
# Overview of the Boat's Control Interface #

## JavaScript Libraries ##
1. [roslibjs](http://wiki.ros.org/roslibjs) - Allows ROS to be accessed and interacted with from a browser.
1. [Chart.js](https://www.chartjs.org/) - Provides JavaScript charting for displaying sensor data.
1. [Mapbox GL JS](https://docs.mapbox.com/mapbox-gl-js/api/) - Provides JavaScript map generation for displaying GPS sensor data recorded on the boat.
1. [xeogl](https://xeogl.org/) - A WebGL 3D visualization engine with support for displaying and animating 3D models.

---
## Custom JavaScript Code ##
1. [ros_setup.js](src/ros_setup.js)
1. [ros_handlers.js](src/ros_handlers.js)
1. [gamepad_control](src/gamepad_control.js)
1. [chart_create.js](src/chart_create.js)
1. [chart_update.js](src/chart_update.js)
1. [OrientationAnimation.js](src/OrientationAnimation.js)

--- 
## Controlling the boat from the website ##
The image at the bottom of this page shows the final version of the boat's website. 

The [Logitech F310 Controller](https://www.logitechg.com/en-us/products/gamepads/f310-gamepad.html) is used to manually drive the boat.

Steps to activate manual control:
1. Connect the Logitech F310 to the computer that is on the boat's website
1. Press any button on the controller - this will "wake up" the website and let it know that a controller is connected
1. Without pressing either of the joysticks, press the the "**Start**" button on the controller to zero the controller axis. 
1. The left and right motors on the boat can now be controlled independently using the left and right joystics on the F310. The axis can be re-zeroed at any point by pressing the "**Start**" button on the controller again.  


![](../Images/FullBoat/Website_Screenshot.png)
