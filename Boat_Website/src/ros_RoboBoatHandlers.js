var ros = new ROSLIB.Ros({
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

ard_LeftPWM_listener = new ROSLIB.Topic({
  ros: ros,
  name: '/Motor_LeftPWM',
  messageType: 'std_msgs/Float32'
});

ard_RightPWM_listener = new ROSLIB.Topic({
  ros: ros,
  name: '/Motor_RightPWM',
  messageType: 'std_msgs/Float32'
});

var BatteryListener = new ROSLIB.Topic({
  ros: ros,
  name: '/BatteryVoltage',
  messageType: 'std_msgs/String'
});

var IMU_AbsOrientationListener = new ROSLIB.Topic({
  ros: ros,
  name: '/IMU_absoluteOrientation',
  messageType: 'geometry_msgs/Vector3'
});

var IMU_AccelerationListener = new ROSLIB.Topic({
  ros: ros,
  name: '/IMU_linearAcceleration',
  messageType: 'geometry_msgs/Vector3'
});

var GPS_Coordinates = new ROSLIB.Topic({
  ros: ros,
  name: '/gps',
  messageType: 'sensor_msgs/NavSatFix'
});

BatteryListener.subscribe(function(message) {
  console.log('Received message on ' + BatteryListener.name + ': ' + message.data);
  document.getElementById("BatteryReading").innerHTML = message.data;
});

IMU_AbsOrientationListener.subscribe(function(message) {
  if (IMU_Cnt == 0) {
    X_zero = message.x;
    Y_zero = message.y;
    Z_zero = message.z;
  }

  orientation_deg = [message.x - X_zero, message.y - Y_zero, message.z - Z_zero];
  var rotation = BoatModel.rotation;

  rotation[0] = orientation_deg[0] - 90;
  rotation[1] = orientation_deg[1];
  rotation[2] = orientation_deg[2];
  BoatModel.rotation = rotation;

  updateChart(Chart_OrientationDeg, orientation_deg, IMU_Cnt);
  IMU_Cnt++;
});

IMU_AccelerationListener.subscribe(function(message) {
  accel = [message.x, message.y, message.z];

  updateChart(Chart_Acceleration, accel, IMU_Accel_Cnt)
  IMU_Accel_Cnt++;
});

function updateChart(chart, newData, count){
  if (IMU_Accel_Cnt < MAX_PLOT_IDX) {
    chart.data.labels.push(IMU_Accel_Cnt);
    chart.data.datasets.forEach((dataset, index) => {
      dataset.data.push(newData[index]);
    });
  } else {
    chart.data.labels.push(IMU_Accel_Cnt);
    chart.data.datasets.forEach((dataset, index) => {
      dataset.data.push(newData[index]);
      dataset.data.splice(0, 1); // remove first data point
    });
    chart.data.labels.splice(0, 1);
  }

  chart.update(0);
}

GPS_Coordinates.subscribe(function(message) {
  //console.log('Received message on ' + GPS_Coordinates.name + ': ' + message.status.status);

  GPS_fix = message.status.status; //< Have a fix? (1/0 - true/false)
  GPS_fixquality = message.status.service; //< Fix quality (0, 1, 2 = Invalid, GPS, DGPS)
  GPS_latitude = message.latitude;
  GPS_longitude = -message.longitude;
  GPS_altitude = message.altitude;

  document.getElementById("GPS_latitude").innerHTML = GPS_latitude;
  document.getElementById("GPS_longitude").innerHTML = GPS_longitude;
  document.getElementById("GPS_altitude").innerHTML = GPS_altitude;

  console.log("GPS_fix" + GPS_fix);

  if (GPS_fix == 1 && GPS_fixquality != 0) { // If there is a valid connection (GPS_fixquality != 0), update map
    map.setCenter([GPS_longitude, GPS_latitude]);
    marker.remove();
    marker = new mapboxgl.Marker({
      color: `rgb(0, 255, 0)`
    }).setLngLat([GPS_longitude, GPS_latitude]).addTo(map);
  } else {
    tmp = marker.getLngLat()
    marker.remove();
    marker = new mapboxgl.Marker({
      color: `rgb(255, 0, 0)`
    }).setLngLat(tmp).addTo(map);
  }

  document.getElementById("GPS_fix").innerHTML = GPS_fix;
  document.getElementById("GPS_fixquality").innerHTML = GPS_fixquality;

  if (GPS_fix == 1) {
    document.getElementById("GPS_fix").innerHTML = "Fix Acquired";
  } else {
    document.getElementById("GPS_fix").innerHTML = "No Acquired";
  }

  if (GPS_fixquality == 1) {
    document.getElementById("GPS_fixquality").innerHTML = "GPS";
  } else if (GPS_fixquality == 2) {
    document.getElementById("GPS_fixquality").innerHTML = "DGPS";
  } else {
    document.getElementById("GPS_fixquality").innerHTML = "Invalid";
  }
});
