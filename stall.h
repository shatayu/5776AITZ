/*
PI loop to hold the main lift steady
*/
task holdMainLift() {
	float kp = 0.2; float ki = 0.1
	int error; int integral = 0;
	int integralCap = 10;	int powerCap = 50;
	int target = SensorValue[MainLiftPot];
	int power;

	while (true) {
		error = target - SensorValue[MainLiftPot];
		integral += error;

		if (abs(integral) < integralCap) {
			power = (kp * error) + (ki * integral);
		} else {
			power = (kp * error) + (sgn(integral) * ki * integralCap);
		}

	 	if (abs(power) < powerCap) {
	 		moveMainLift(power);
	 	} else {
	 		moveMainLift(sgn(power) * powerCap);
		}
	}
}

task holdMogo() {
	float kp = 0.4; float ki = 0.1
	int error; int integral = 0;
	int integralCap = 10;	int powerCap = 50;
	int target = SensorValue[MogoPot];
	int power;

	while (true) {
		error = target - SensorValue[MogoPot];
		integral += error;

		if (abs(integral) < integralCap) {
			power = (kp * error) + (ki * integral);
		} else {
			power = (kp * error) + (sgn(integral) * ki * integralCap);
		}

	 	if (abs(power) < powerCap) {
	 		moveMogoIntake(power);
	 	} else {
	 		moveMogoIntake(sgn(power) * powerCap);
		}
	}
}

task holdTopLift() {
	float kp = 0.3; float ki = 0.1
	int error; int integral = 0;
	int integralCap = 10;	int powerCap = 20;
	int target = SensorValue[TopLiftPot];
	int power;

	while (true) {
		error = target - SensorValue[TopLiftPot];
		integral += error;

		if (abs(integral) < integralCap) {
			power = (kp * error) + (ki * integral);
		} else {
			power = (kp * error) + (sgn(integral) * ki * integralCap);
		}

	 	if (abs(power) < powerCap) {
	 		moveTopLift(power);
	 	} else {
	 		moveTopLift(sgn(power) * powerCap);
		}
	}
}
