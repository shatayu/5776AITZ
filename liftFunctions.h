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


int PAUSE_TIME = 250;
void autoDecelTopLift(int topLiftTarget) {
	stopTask(topLiftPI);
	int timeout = 5000;


	int timer = 0;
	if (SensorValue[TopLiftPot] < topLiftTarget) { 	// lift is below target
		while (SensorValue[TopLiftPot] < topLiftTarget && timer < timeout) {
			moveTopLift(127);
			wait1Msec(20);
			timer += 20;
		}
		wait1Msec(PAUSE_TIME);
	} else if (SensorValue[TopLiftPot] > topLiftTarget) { // lift is above target
		while (SensorValue[TopLiftPot] > topLiftTarget && timer < timeout) {
			moveTopLift(-127);
			wait1Msec(20);
			timer += 20;
		}
		wait1Msec(PAUSE_TIME);
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


float integral = 0;

float ki = 0.0007;
int base = 75;
void autonMainLift_SWAG(int target, int timeout) {
	stopTask(mainLiftPI);
	int timer = 0;



	int kstable = 200;

	integral = 0;
	int integralCap = 90;

	int error = target - SensorValue[MainLiftPot];


	int stableTime = 0;
	while (SensorValue[MainLiftPot] < target-150 && timer < timeout) { //momentum offset 150
		error = target - SensorValue[MainLiftPot];
		float percent = error*1.0/target;
		percent = percent * percent * percent;
		moveMainLift(base+(127-base)*percent);
		wait1Msec(20);
		timer += 20;
	}

	moveMainLift(-20);
	wait1Msec(80);

	startTask(mainLiftPI);
}

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
