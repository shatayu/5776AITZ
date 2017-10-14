/*
PI loop to hold the main lift steady
*/
task holdMainLift() {
	float kp = 0.1; float ki = 0.1;
	int error = 0; int integral = 0;
	int integralCap = 10;	int powerCap = 15;
	int target = SensorValue[LiftPot];
	int power;

	while (true) {
		error = target - SensorValue[LiftPot];
		integral += error;

		if (abs(integral) < integralCap) {
			power = kp * error + ki * integral;
		} else {
			power = kp * error + sgn(integral) * ki * integralCap;
		}

	 	if (abs(power) < powerCap) {
	 		moveMainLift(power);
	 	} else {
	 		moveMainLift(sgn(power) * powerCap);
		}
	}
}
