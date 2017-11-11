/*
manages top lift (vertibar)
all the way up 3640
all the way down with mogo in 1485
all the way down 1230
*/

int topLiftTarget;
int topLiftPower;

task autonTopLiftHelper() {
}

void autonTopLift(int topLiftTarget, int power) {
	stopTask(topLiftPI);
	int timeout = 5000;

	int timer = 0;
	if (SensorValue[TopLiftPot] < topLiftTarget) { 	// lift is below target
		while (SensorValue[TopLiftPot] < topLiftTarget && timer < timeout) {
			moveTopLift(power);
			wait1Msec(20);
			timer += 20;
		}
	} else if (SensorValue[TopLiftPot] > topLiftTarget) { // lift is above target
		while (SensorValue[TopLiftPot] > topLiftTarget && timer < timeout) {
			moveTopLift(-power);
			wait1Msec(20);
			timer += 20;
		}
	}

	moveTopLift(0);
	startTask(topLiftPI);
}

/*
moves mogo to specific position.
all the way out 3190
all the way in 1485
*/
int mogoTarget;
task autonMogo() {
	int timeout = 5000; // amount of time claw is allowed to reach its state
	int power = 70;

	// greater sensor value := mogo intake more withdrawn
	int timer = 0;
	if (SensorValue[MogoPot] < mogoTarget) { 	// extend intake
		while (SensorValue[MogoPot] < mogoTarget && timer < timeout) {
			moveMogoIntake(127);
			wait1Msec(20);
			timer += 20;
		}
	} else if (SensorValue[MogoPot] > mogoTarget) { // extend intake
		while (SensorValue[MogoPot] > mogoTarget && timer < timeout) {
			moveMogoIntake(-127);
			wait1Msec(20);
			timer += 20;
		}
	}

	moveMogoIntake(0);
}

/*
moves lift to specific position.
220 all the way down
1320 all the way up
*/

void autonMainLift(int target, int timeout, int power) {
	stopTask(mainLiftPI);
	int timer = 0;

	if (SensorValue[MainLiftPot] < target) { 	// lift is below target
		while (SensorValue[MainLiftPot] < target && timer < timeout) {
			moveMainLift(power);
			wait1Msec(20);
			timer += 20;
		}
	} else if (SensorValue[MainLiftPot] > target) { // lift is above target
		while (SensorValue[MainLiftPot] > target && timer < timeout) {
			moveMainLift(-power);
			wait1Msec(20);
			timer += 20;
		}
	}

	moveMainLift(0);
	startTask(mainLiftPI);
}
