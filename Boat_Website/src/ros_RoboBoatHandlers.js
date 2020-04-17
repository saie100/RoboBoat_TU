
/*
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

var ard_LeftPWM_listener = new ROSLIB.Topic({
  ros: ros,
  name: '/Motor_LeftPWM',
  messageType: 'std_msgs/Float32'
});

var ard_RightPWM_listener = new ROSLIB.Topic({
  ros: ros,
  name: '/Motor_RightPWM',
  messageType: 'std_msgs/Float32'
});

 var ControlMode = new ROSLIB.Topic({
  ros: ros,
  name: '/status_light_manual_mode',
  messageType: 'std_msgs/Bool'
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
*/

BatteryListener.subscribe(function(message) {
  var separateBattery = message.data.split(",");
  bat_6s = separateBattery[0].split(" ").map(Number);
  bat_4s = separateBattery[1].split(" ").map(Number);
  bat_3sa = separateBattery[2].split(" ").map(Number);
  bat_3sb = separateBattery[3].split(" ").map(Number);

  Chart_Battery.data.datasets[0].data = [bat_6s[0], bat_4s[0], bat_3sa[0], bat_3sb[0]];
  Chart_Battery.data.datasets[1].data = [bat_6s[1], bat_4s[1], bat_3sa[1], bat_3sb[1]];
  Chart_Battery.data.datasets[2].data = [bat_6s[2], bat_4s[2], bat_3sa[2], bat_3sb[2]];
  Chart_Battery.data.datasets[3].data = [bat_6s[3], bat_4s[3], 0, 0];
  Chart_Battery.data.datasets[4].data = [bat_6s[4], 0, 0, 0];
  Chart_Battery.data.datasets[5].data = [bat_6s[5], 0, 0, 0];
  Chart_Battery.update(0);
  /*
  console.log('bat_6s ' + bat_6s);
  console.log('bat_4s ' + bat_4s);
  console.log('bat_3sa ' + bat_3sa);
  console.log('bat_3sb ' + bat_3sb);
  */
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
    chart.data.labels.push(count);
    chart.data.datasets.forEach((dataset, index) => {
      dataset.data.push(newData[index]);
    });
  } else {
    chart.data.labels.push(count);
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
    document.getElementById("GPS_fix").innerHTML = "Acquired";
  } else {
    document.getElementById("GPS_fix").innerHTML = "Searching";
  }

  if (GPS_fixquality == 1) {
    document.getElementById("GPS_fixquality").innerHTML = "GPS";
  } else if (GPS_fixquality == 2) {
    document.getElementById("GPS_fixquality").innerHTML = "DGPS";
  } else {
    document.getElementById("GPS_fixquality").innerHTML = "Invalid";
  }
});
