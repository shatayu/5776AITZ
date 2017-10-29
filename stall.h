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


int topLiftPIDTarget;
bool topLiftPID;
bool mainLiftPID;

task holdTopLift() {
	float kp = 0.5; float ki = 0.1
	int error; int integral = 0;
	int integralCap = 20;	int powerCap = 60;
	int target = SensorValue[TopLiftPot];
	int power;

	while (topLiftPID) {
		target = topLiftPIDTarget;
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
		wait1Msec(20);
	}
}

task driveTopLift() {
	float kp = 0.3; float ki = 0.2;
	int error; int integral = 0;
	int integralCap = 20;	int powerCap = 30;
	int power; int target;

	while (true) {
		if (vexRT[Btn8U]) {
			writeDebugStream("moving up\n");
			moveTopLift(127);
			target = SensorValue[TopLiftPot];
		} else if (vexRT[Btn8D]) {
			writeDebugStream("moving down\n");
			moveTopLift(-127);
			target = SensorValue[TopLiftPot];
		} else if (vexRT[Btn8R]) {
			//while
			//target = SensorValue[TopLiftPot];
		} else {
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
			wait1Msec(20);
		}
	}
}

task driveMainLift() {
	float kp = 0.2; float ki = 0.1
	int error; int integral = 0;
	int integralCap = 10;	int powerCap = 50;
	int target;
	int power;

	while (true) {
		if (vexRT[Btn5U]) {
			writeDebugStream("moving up\n");
			moveMainLift(127);
			target = SensorValue[MainLiftPot];
		} else if (vexRT[Btn5D]) {
			writeDebugStream("moving down\n");
			moveMainLift(-127);
			target = SensorValue[MainLiftPot];
		} else {
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
			wait1Msec(20);
		}
	}
}
