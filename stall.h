task topLiftPI() {
	float kp = 0.12; float ki = 0;
	int error; int integral = 0;
	int integralCap = 15;	int powerCap = 127;
	int power; int target = 1500;

	while (true) {
		error = target - SensorValue[TopLiftPot];
		integral += error;

		int integralPower = (abs(integral) < integralCap) ? integral : integralCap;

		power = kp * error + ki * integralPower;

		//if (abs(error) < 20) {
		//	moveTopLift(0);
		//} else if (abs(error) < 50) {
		//	moveTopLift(sgn(power) * 40);
		//} else
		if (abs(error) < 50) {
			moveTopLift(0);
		} else if (abs(power) < 35) {
			moveTopLift(sgn(power) * 35);
		} else if (abs(power) < powerCap) {
			moveTopLift(power);
		} else {
			moveTopLift(sgn(power) * powerCap);
		}
	}

	wait1Msec(20);
}

task mainLiftPI() {
	float kp = 0.35; float ki = 0.05;
	int error; int integral = 0;
	int integralCap = 30; int powerCap = 127;
	int target;
	int power;

	while (true) {
		// hold with PI
		error = target - SensorValue[MainLiftPot];
		integral += error;

		int integralPower = (abs(integral) < integralCap) ? integral : integralCap;

		power = kp * error + ki * integralPower;

		if (abs(error) < 20) {
			moveMainLift(0);
		} else if (abs(error) < 357) {
			moveMainLift(sgn(power) * 30);
		} else if (abs(power) < powerCap) {
			moveMainLift(power);
		} else {
			moveMainLift(sgn(power) * powerCap);
		}
	}

	wait1Msec(20);
}
