/*
manages top lift (vertibar)
all the way up 3640
all the way down with mogo in 1485
all the way down 1230
*/

void autonTopLift(int topLiftTarget) {
	stopTask(holdTopLift);
	int timeout = 5000;
	int power = 70;

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
	startTask(holdTopLift);
}

/*
moves mogo to specific position.
all the way out 3190
all the way in 1485
*/
int mogoTarget;
task autonMogo() {
	stopTask(holdMogo);
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
	startTask(holdMogo);
	stopTask(autonMogo);
}

/*
moves lift to specific position.
220 all the way down
1320 all the way up
*/

void autonMainLift(int mainLiftTarget) {
	int timeout = 4000;
	int power = 127;

	stopTask(holdMainLift);
	int timer = 0;
	if (SensorValue[MainLiftPot] < mainLiftTarget) { 	// lift is below target
		while (SensorValue[MainLiftPot] < mainLiftTarget && timer < timeout) {
			moveMainLift(power);
			wait1Msec(20);
			timer += 20;
		}
	} else if (SensorValue[MainLiftPot] > mainLiftTarget) { // lift is above target
		while (SensorValue[MainLiftPot] > mainLiftTarget && timer < timeout) {
			moveMainLift(-power);
			wait1Msec(20);
			timer += 20;
		}
	}

	moveMainLift(0);
	startTask(holdMainLift);
}
