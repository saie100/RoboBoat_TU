ard_LeftPWM_listener.subscribe(function(message) {
  // Update the chart with the left gamepad value
  updateGamepadChart(0, message.data);
  // Round and update the table with the left gamepad value
  document.getElementById("lJoystickVal").innerHTML = Math.round(message.data*1000)/1000;
});

ard_RightPWM_listener.subscribe(function(message) {
  // Update the chart with the right gamepad value
  updateGamepadChart(1, message.data);
  // Round and update the table with the right gamepad value
  document.getElementById("rJoystickVal").innerHTML = Math.round(message.data*1000)/1000;
});

BatteryListener.subscribe(function(message) {
  // Battery readings are separated by commas ... so split on the commas
  var separateBattery = message.data.split(",");
  // cell readings are separated by spaces, so split on the spaces and map to a number
  bat_6s = separateBattery[0].split(" ").map(Number);
  bat_4s = separateBattery[1].split(" ").map(Number);
  bat_3sa = separateBattery[2].split(" ").map(Number);
  bat_3sb = separateBattery[3].split(" ").map(Number);

  // Update the battery chart data
  Chart_Battery.data.datasets[0].data = [bat_6s[0], bat_4s[0], bat_3sa[0], bat_3sb[0]];
  Chart_Battery.data.datasets[1].data = [bat_6s[1], bat_4s[1], bat_3sa[1], bat_3sb[1]];
  Chart_Battery.data.datasets[2].data = [bat_6s[2], bat_4s[2], bat_3sa[2], bat_3sb[2]];
  Chart_Battery.data.datasets[3].data = [bat_6s[3], bat_4s[3], 0, 0];
  Chart_Battery.data.datasets[4].data = [bat_6s[4], 0, 0, 0];
  Chart_Battery.data.datasets[5].data = [bat_6s[5], 0, 0, 0];
  // Process the battery chart update
  Chart_Battery.update(0);
});

IMU_AbsOrientationListener.subscribe(function(message) {
  // Store the time that the message was recieved
  msgTime = ((message.header.stamp.secs) + (message.header.stamp.nsecs / Math.pow(10, 9)));

  // Update at a fixed interval to make the website more responsive
  if (msgTime - IMU_OrientationLastUpdateTime >= 1 / PLOT_UPDATE_FREQUENCY) {
    IMU_OrientationLastUpdateTime = msgTime;
    orientation_deg = [message.vector.x, message.vector.y, message.vector.z];
    var rotation = BoatModel.rotation;

    rotation[0] = orientation_deg[0] - 90;
    rotation[1] = orientation_deg[1];
    rotation[2] = orientation_deg[2];
    BoatModel.rotation = rotation;

    updateChart(Chart_OrientationDeg, orientation_deg, getChartTime(msgTime), IMU_Cnt);
    IMU_Cnt++;
  }

});

IMU_LinearAccelerationListener.subscribe(function(message) {

  msgTime = Math.round(((message.header.stamp.secs) + (message.header.stamp.nsecs / Math.pow(10, 9))) * 10000) / 10000;

  // Update at a fixed interval to make the website more responsive
  if (msgTime - IMU_LinearAccelerationLastUpdateTime >= 1 / PLOT_UPDATE_FREQUENCY) {
    IMU_LinearAccelerationLastUpdateTime = msgTime;
    accel = [message.vector.x, message.vector.y, message.vector.z];

    updateChart(Chart_Acceleration, accel, getChartTime(msgTime), IMU_Accel_Cnt);
    IMU_Accel_Cnt++;
  }

});

IMU_AngularVelocityListener.subscribe(function(message) {

  msgTime = Math.round(((message.header.stamp.secs) + (message.header.stamp.nsecs / Math.pow(10, 9))) * 10000) / 10000;

  // Update at a fixed interval to make the website more responsive
  if (msgTime - IMU_AngularVelocityLastUpdateTime >= 1 / PLOT_UPDATE_FREQUENCY) {
    IMU_AngularVelocityLastUpdateTime = msgTime;
    angVel = [message.vector.x, message.vector.y, message.vector.z];

    updateChart(Chart_AngularVelocity, angVel, getChartTime(msgTime), IMU_AngVel_Cnt);
    IMU_AngVel_Cnt++;
  }

});

IMU_MagnetometerListener.subscribe(function(message) {

  msgTime = Math.round(((message.header.stamp.secs) + (message.header.stamp.nsecs / Math.pow(10, 9))) * 10000) / 10000;

  // Update at a fixed interval to make the website more responsive  if (msgTime - IMU_MagnetometerLastUpdateTime >= 1 / PLOT_UPDATE_FREQUENCY) {
  if (msgTime - IMU_MagnetometerLastUpdateTime >= 1 / PLOT_UPDATE_FREQUENCY) {
    IMU_MagnetometerLastUpdateTime = msgTime;
    magVec = [message.vector.x, message.vector.y, message.vector.z];

    updateChart(Chart_Magnetometer, magVec, getChartTime(msgTime), IMU_MagVec_Cnt);
    IMU_MagVec_Cnt++;
  }

});

GPS_Coordinates.subscribe(function(message) {

  GPS_fix = message.status.status; //< Have a fix? (1/0 - true/false)
  GPS_fixquality = message.status.service; //< Fix quality (0, 1, 2 = Invalid, GPS, DGPS)
  GPS_latitude = message.latitude;
  GPS_longitude = -message.longitude;
  GPS_altitude = message.altitude;

  document.getElementById("GPS_latitude").innerHTML = GPS_latitude;
  document.getElementById("GPS_longitude").innerHTML = GPS_longitude;
  // Set altutude and convert from cm to ft
  document.getElementById("GPS_altitude").innerHTML = GPS_altitude * 0.0328084;


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


LIDAR_Scan.subscribe(function(message) {
  msgTime = Math.round(((message.header.stamp.secs) + (message.header.stamp.nsecs / Math.pow(10, 9))) * 10000) / 10000;

  // Update at a fixed interval to make the website more responsive
  if (msgTime - LIDAR_LastUpdateTime >= 1 / LIDAR_UPDATE_FREQUENCY) {
    LIDAR_LastUpdateTime = msgTime;

    var range_min = 100;
    var range_max = 0;
    var ang = message.angle_min;
    var catesian_data = [];
    var i;
    for (i = 0; i < message.ranges.length; i++) {
    if(message.ranges[i] != Infinity){
      var xc = message.ranges[i] * Math.cos(ang);
      var yc = message.ranges[i] * Math.sin(ang);
      if(-xc > 0){
        catesian_data.push({ x: yc, y: -xc});
        if(message.ranges[i] < range_min){
          range_min = message.ranges[i];
        }
        else if(message.ranges[i] > range_max){
          range_max = message.ranges[i];
        }
      }
    }
      ang = ang + message.angle_increment;
    }

    var f_secs = Math.round(message.header.stamp.nsecs / Math.pow(10,5)); // Fractional seconds
    var myDate = new Date(message.header.stamp.secs * 1000);

    var options = { hour12: false, fractionalSecondDigits: 3};

    document.getElementById("LIDAR_range_min").innerHTML = Math.round(range_min*1000)/1000;
    document.getElementById("LIDAR_range_max").innerHTML = Math.round(range_max*1000)/1000;
    document.getElementById("LIDAR_time_increment").innerHTML = Math.round(message.time_increment*1000*1000)/1000;
    document.getElementById("LIDAR_scan_time").innerHTML = Math.round(message.scan_time*1000*1000)/1000;
    document.getElementById("LIDAR_last_measured_Time").innerHTML = (myDate.toLocaleString("en-US", options) + "." + f_secs).replace(", ", "<br>");

    Chart_LIDAR.data.datasets[0].data = catesian_data;
    Chart_LIDAR.update(0);

  }
});

function updateChart(chart, newData, name, count) {
  if (count < MAX_PLOT_IDX) {
    chart.data.labels.push(name);
    chart.data.datasets.forEach((dataset, index) => {
      dataset.data.push(newData[index]);
    });
  } else {
    chart.data.labels.push(name);
    chart.data.datasets.forEach((dataset, index) => {
      dataset.data.push(newData[index]);
      dataset.data.splice(0, 1); // remove first data point
    });
    chart.data.labels.splice(0, 1);
  }

  chart.update(0);
}

function getChartTime(unixTime){
  var date = new Date(unixTime*1000);
  var msgTime_Formatted = "" + date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds() + "." + date.getMilliseconds();
  if(date.getMilliseconds() < 10){
    msgTime_Formatted = msgTime_Formatted.padEnd(msgTime_Formatted.length + 2, "0");
  }
  else if(date.getMilliseconds() < 100){
    msgTime_Formatted = msgTime_Formatted.padEnd(msgTime_Formatted.length + 1, "0");
  }
  return msgTime_Formatted;
}
