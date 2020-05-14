  ros = new ROSLIB.Ros({
  // Use the IP Address of the Raspberry Pi or the device hosting the webserver
  // Port 9090 is the port that rosbridge server uses to interface over the network
  url: 'ws://10.19.122.101:9090'
});

ros.on('connection', function() {
  document.getElementById("rosConnStatus").innerHTML = "Connected";
});
ros.on('error', function(error) {
  document.getElementById("rosConnStatus").innerHTML = "Error";
});
ros.on('close', function() {
  document.getElementById("rosConnStatus").innerHTML = "Closed";
});

ControlMode = new ROSLIB.Topic({
  ros: ros,
  name: '/status_light_manual_mode',
  messageType: 'std_msgs/Bool'
});

ard_LeftPWM_listener = new ROSLIB.Topic({
  ros: ros,
  name: '/Motor_leftPWM',
  messageType: 'std_msgs/Float32'
});

ard_RightPWM_listener = new ROSLIB.Topic({
  ros: ros,
  name: '/Motor_rightPWM',
  messageType: 'std_msgs/Float32'
});

BatteryListener = new ROSLIB.Topic({
  ros: ros,
  name: '/BatteryVoltage',
  messageType: 'std_msgs/String'
});

IMU_AbsOrientationListener = new ROSLIB.Topic({
  ros: ros,
  name: '/IMU_absoluteOrientation',
  messageType: 'geometry_msgs/Vector3Stamped'
});

IMU_LinearAccelerationListener = new ROSLIB.Topic({
  ros: ros,
  name: '/IMU_linearAcceleration',
  messageType: 'geometry_msgs/Vector3Stamped'
});

IMU_AngularVelocityListener = new ROSLIB.Topic({
  ros: ros,
  name: '/IMU_angularVelocity',
  messageType: 'geometry_msgs/Vector3Stamped'
});

IMU_MagnetometerListener = new ROSLIB.Topic({
  ros: ros,
  name: '/IMU_magVec',
  messageType: 'geometry_msgs/Vector3Stamped'
});

GPS_Coordinates = new ROSLIB.Topic({
  ros: ros,
  name: '/gps',
  messageType: 'sensor_msgs/NavSatFix'
});
