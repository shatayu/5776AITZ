task topLiftPI() {
	float kp = 0; float ki = 0;
	int error; int integral = 0;
	int integralCap = 15;	int powerCap = 30;
	int power; int target;

	while (true) {
		if (vexRT[Btn8U]) {
			moveTopLift(127); // raise lift
			target = SensorValue[TopLiftPot];
		} else if (vexRT[Btn8D]) {
			moveTopLift(-127); // lower lift
			target = SensorValue[TopLiftPot];
		} else {
			//trigger PI
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
		wait1Msec(20);
	}
}

task mainLiftPI() {
	float kp = 0; float ki = 0;
	int error; int integral = 0;
	int integralCap = 30;	int powerCap = 30;
	int target;
	int power;

	while (true) {
		if (vexRT[Btn5U]) {
			moveMainLift(127); // raise lift
			target = SensorValue[MainLiftPot];
		} else if (vexRT[Btn5D]) {
			moveMainLift(-127); // lower lift
			target = SensorValue[MainLiftPot];
		} else {
			// hold with PI
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
			int a = SensorValue[MainLiftPot];
			wait1Msec(100);
			int b = SensorValue[MainLiftPot];
		}
		wait1Msec(20);
	}
}
