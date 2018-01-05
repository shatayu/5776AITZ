void moveMainLift(int power) {
	motor[LMainLift] = power;
	motor[RMainLift] = power;
}

task autonMainLift() {
	int error = mainLift.target - SensorValue[MainLiftPot];
	int timer = 0;

	if (error > 0) {
		while (error > 0 && timer < mainLift.timeout) {
			moveMainLift(mainLift.power);
			timer += 20;
			wait1Msec(20);
			error = mainLift.target - SensorValue[MainLiftPot];

			if (SensorValue[MainLiftPot] < 1350 && sgn(mainLift.power) == -1)
				break;
		}
	} else if (error < 0) {
		while (error < 0 && timer < mainLift.timeout) {
			moveMainLift(-mainLift.power);
			timer += 20;
			wait1Msec(20);
			error = mainLift.target - SensorValue[MainLiftPot];

			if (SensorValue[MainLiftPot] < 1350 && sgn(mainLift.power) == -1)
				break;
		}
	}

	moveMainLift(-sgn(error) * 30);
	wait1Msec(50);
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

		if (abs(error) < 30) {
			mainLift.power = 0;
		} else if (abs(error) < 500 && sgn(PIpower) == -1) {
			mainLift.power = sgn(PIpower) * 30;
		} else if (abs(error) < 200 && sgn(PIpower) == 1) {
			mainLift.power = sgn(PIpower) * 30;
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
	//while (sgn(error) == sgn(topLift.target - SensorValue[TopLiftPot]) && timer < topLift.timeout) {
	//	moveTopLift(sgn(error) * 127);
	//	wait1Msec(20);
	//	timer += 20;
	//	error = topLift.target - SensorValue[TopLiftPot];
	//	wait1Msec(20);
	//}
	if (error > 0) {
		while (error > 0 && timer < topLift.timeout) {
			moveTopLift(topLift.power);
			wait1Msec(20);
			timer += 20;
			error = topLift.target - SensorValue[TopLiftPot];
		}
	} else {
		while (error < 0 && timer < topLift.timeout) {
				moveTopLift(-topLift.power);
				wait1Msec(20);
				timer += 20;
				error = topLift.target - SensorValue[TopLiftPot];
			}
	}

	if (topLift.target == 2750) {
		moveTopLift(35);
	} else {
		moveTopLift(0);
	}
}

task topLiftPI() {
	float kp = 0.18; float ki = 0.08;
	int error; int integral = 0;
	int integralCap = 15;	int powerCap = 127;

	while (true) {
		error = topLift.target - SensorValue[TopLiftPot];
		integral += error;

		int integralPower = (abs(integral) < integralCap) ? integral : integralCap;

		int PIpower = kp * error + ki * integralPower;

		if (abs(error) < 20) {
			topLift.power = 0;
		} else if (abs(PIpower) > 5 && abs(PIpower) < 20) {
			topLift.power = sgn(PIpower) * 20;
		} else if (abs(PIpower) > powerCap) {
			topLift.power = sgn(PIpower) * powerCap;
		} else {
			topLift.power = PIpower;
		}

		moveTopLift(topLift.power);
		wait1Msec(20);
	}
}
