void bl_calibrate_gyro() {
	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[in5] = sensorNone;
	delay(1000);
	//Reconfigure Analog Port 5 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[in5] = sensorGyro;
	wait1Msec(2000);
}
