/*
moves robot "target" encoder units forward with motor power "power".
If the target is not reached in "timeout" ms, stop.
Needs to be braked with autonBrake().
*/
void autonDrive(int target, int timeout, int power) {
	SensorValue[LEncoder] = 0;
	SensorValue[REncoder] = 0;

	int timer = 0;
	while (abs(SensorValue[LEncoder]) < target && timer < timeout) {
		moveDrive(power, power);
		wait1Msec(20);
		timer += 20;
	}

	moveDrive(0, 0);
}

/*
brakes after moving. Use if robot needs to stop
*/
void autonBrake(int direction) {
	moveDrive(-direction * 30, -direction * 30);
	wait1Msec(30);
	moveDrive(0, 0);
}

/*
moves lift to specific position.
*/
void autonMainLift(int target, int timeout, int power) {
	// stopTask(holdMainLift);
	int timer = 0;
	if (SensorValue[LiftPot] < target && power > 0) { 	// lift is below target
		while (SensorValue[LiftPot] < target && timer < timeout) {
			moveMainLift(power);
			wait1Msec(20);
			timer += 20;
		}
	} else if (SensorValue[LiftPot] > target && power < 0) { // lift is above target
		while (SensorValue[LiftPot] > target && timer < timeout) {
			moveMainLift(power);
			wait1Msec(20);
			timer += 20;
		}
	}

	moveMainLift(0);
	// startTask(holdMainLift);
}

/*
moves mogo to specific position.
*/
void autonMogo(int state) {
	int timeout = 5000; // amount of time claw is allowed to reach its state
	int power = 127;

	// greater sensor value := mogo intake more withdrawn
	int timer = 0;
	if (SensorValue[MogoPot] < state) { 	// extend intake
		while (SensorValue[MogoPot] < state && timer < timeout) {
			moveMogoIntake(-127);
			wait1Msec(20);
			timer += 20;
		}
	} else if (SensorValue[LiftPot] > state) { // extend intake
		while (SensorValue[MogoPot] > state && timer < timeout) {
			moveMogoIntake(127);
			wait1Msec(20);
			timer += 20;
		}
	}

	moveMogoIntake(0);
}

// higher sensor value := open
void autonConeIntake(int state) {
	clawStall(false);
	int timeout = 500; // amount of time claw is allowed to reach its state
	int power = 127;

	int timer = 0;
	if (SensorValue[ConePot] < state) { 	// open claw
		while (SensorValue[MogoPot] < state && timer < timeout) {
			moveConeIntake(-power);
			wait1Msec(20);
			timer += 20;
		}
	} else if (SensorValue[LiftPot] > state) { // close claw
		while (SensorValue[MogoPot] > state && timer < timeout) {
			moveConeIntake(power);
			wait1Msec(20);
			timer += 20;
		}
		clawStall(true);
	}

	moveConeIntake(0);
}
