void moveMainLift(int power) {
	motor[LMainLift] = power;
	motor[RMainLift] = power;
}

task autonMainLift() {
	int error = mainLift.target - SensorValue[MainLiftPot];
	int timer = 0;
	while (abs(error) > 30 && timer < mainLift.timeout) {
		moveMainLift(sgn(error) * mainLift.power);
		wait1Msec(20);
		timer += 20;
		error = mainLift.target - SensorValue[MainLiftPot];
		wait1Msec(20);
	}
	moveMainLift(0);
	stopTask(autonMainLift);
}

task mainLiftPI() {
	float kp = 0.35; float ki = 0.05;
	int error; int integral = 0;
	int integralCap = 30; int powerCap = 127;

	while (true) {
		// hold with PI
		error = mainLift.target - SensorValue[MainLiftPot];
		integral += error;

		int integralPower = (abs(integral) < integralCap) ? integral : integralCap;

		int PIpower = kp * error + ki * integralPower;

		if (abs(error) < 60) {
			mainLift.power = 0;
		} else if (abs(error) < 500 && sgn(PIpower) == -1) {
			mainLift.power = sgn(PIpower) * 30;
		} else if (abs(error) < 360 && sgn(PIpower) == 1) {
			mainLift.power = sgn(PIpower) * 40;
		} else if (abs(PIpower) > powerCap) {
			mainLift.power = sgn(PIpower) * powerCap;
		} else {
			mainLift.power = PIpower;
		}

		moveMainLift(mainLift.power);
		wait1Msec(20);
	}
}

void moveTopLift(int power) {
	motor[TopLift] = power;
}

task autonTopLift() {
	int error = topLift.target - SensorValue[TopLiftPot];
	int timer = 0;
	while (sgn(error) == sgn(topLift.target - SensorValue[TopLiftPot]) && timer < topLift.timeout) {
		moveTopLift(sgn(error) * 127);
		wait1Msec(20);
		timer += 20;
		error = topLift.target - SensorValue[TopLiftPot];
		wait1Msec(20);
	}

	if (topLift.target == 2750) {
		moveTopLift(50);
	} else {
		moveTopLift(0);
	}
}

task topLiftPI() {
	float kp = 0.12; float ki = 0;
	int error; int integral = 0;
	int integralCap = 15;	int powerCap = 127;

	while (true) {
		error = topLift.target - SensorValue[TopLiftPot];
		integral += error;

		int integralPower = (abs(integral) < integralCap) ? integral : integralCap;

		int PIpower = kp * error + ki * integralPower;

		if (abs(error) < 70) {
			topLift.power = 0;
		} else if (abs(error) < 150) {
			topLift.power = sgn(PIpower) * 35;
		} else if (abs(PIpower) < 35) {
			topLift.power = sgn(PIpower) * 35;
		} else if (abs(PIpower) > powerCap) {
			topLift.power = sgn(PIpower) * powerCap;
		} else {
			topLift.power = PIpower;
		}

		moveTopLift(topLift.power);
		wait1Msec(20);
	}
}
