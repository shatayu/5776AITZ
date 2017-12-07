// main autostack logic
task autostackUp() {
	a.stacked = false;

	// stop any prior lift tasks
	stopTask(autonTopLift);
	stopTask(topLiftPI);
	stopTask(autonMainLift);
	stopTask(mainLiftPI);

	// claw stall
	moveConeIntake(30);

	// bring top lift to intermediary height
	// start by powering max
	topLift.target = 1300;
	topLift.timeout = 4000;
	topLift.power = 127;
	startTask(autonTopLift);
	while (SensorValue[TopLiftPot] < 1300)
		wait1Msec(20);

	stopTask(autonTopLift);
	// then PI to exact intermediary height
	topLift.target = 1500;
	startTask(topLiftPI);

	// lift to desired height
	mainLift.target = a.maxHeight;
	mainLift.power = 70;
	mainLift.timeout = 4000;
	if (mainLift.target > 1660) { // if small height PI too slow so autonMainLift used
		startTask(mainLiftPI);
	} else {
		startTask(autonMainLift);
	}


	// after the lift has risen a certain amount begin raising top lift to max height
	while (SensorValue[MainLiftPot] < a.maxHeight - 400)
		wait1Msec(20);

	stopTask(autonTopLift);
	stopTask(topLiftPI);

	topLift.power = 127;
	topLift.target = 2750;
	startTask(autonTopLift);
	while (SensorValue[TopLiftPot] < 2750)
		wait1Msec(20);
	stopTask(autonTopLift);
	moveTopLift(20);

	// open claw at the end
	stopTask(mainLiftPI);
	stopTask(autonMainLift);
	moveConeIntake(50);
	coneIntake.state = OPEN;
	moveMainLift(-127);
	wait1Msec(200);
	moveMainLift(0);
	startTask(autonConeIntake);
	wait1Msec(100);
	moveMainLift(127);
	waitUntil(SensorValue[MainLiftPot] > a.maxHeight);
	moveMainLift(0);
	// flag that cone is stacked
	a.stacked = true;
}



task fieldReset() {
	moveConeIntake(-15);

	// bring top lift down
	topLift.power = 127;
	topLift.timeout = 1000;
	topLift.target = 1530;
	if (a.maxHeight > 1500) {
		startTask(topLiftPI);
	} else {
		startTask(autonTopLift);
	}


	// bring main lift down when top lift is sufficiently far
	while (SensorValue[TopLiftPot] > 1530)
		wait1Msec(20);

	stopTask(topLiftPI);
	moveTopLift(-10);
	mainLift.target = 1300;
	mainLift.power = 70;
	mainLift.timeout = 1500;
	startTask(autonMainLift);
	if (SensorValue[MainLiftPot] > 1700);
		wait1Msec(300);
	mainLift.power = 127;

	// bring top lift in when main lift is sufficiently far down
	while (SensorValue[MainLiftPot] > mainLift.target + 400)
		wait1Msec(20);

	stopTask(topLiftPI);
	moveTopLift(-127);
	wait1Msec(500);
	a.stacked = false;
}

task matchReset() {
	moveConeIntake(-15);

	// bring top lift down
	topLift.target = 1530;
	startTask(topLiftPI);

	// bring main lift down when top lift is sufficiently far
	while (SensorValue[TopLiftPot] > topLift.target)
		wait1Msec(20);

	mainLift.target = 1570;
	mainLift.power = 127;
	mainLift.timeout = 3000;
	startTask(mainLiftPI);

	while (SensorValue[MainLiftPot] > mainLift.target)
		wait1Msec(20);

	a.stacked = false;
}

void autostackTaskReset() {
		// stop all tasks relating to autostack
	stopTask(autostackUp);
	stopTask(fieldReset);
	stopTask(matchReset);
	stopTask(autonMainLift);
	stopTask(mainLiftPI);
	stopTask(autonTopLift);
	stopTask(topLiftPI);
	stopTask(autonConeIntake);

	// ensure no motors are moving
	moveMainLift(0);
	moveTopLift(0);
	moveConeIntake(-15);
}

void abortAutostack() {
	// stop all tasks relating to autostack
	autostackTaskReset();

	// stops waits
	a.stacked = true;
	wait1Msec(100);
	a.stacked = false;
}

bool FIELD = true;
bool MATCH = false;

void autostack(int conesOnMogo, bool reset) {
	// set height to stack cone
	if (conesOnMogo == 0) {
		a.maxHeight = 1320;
	} else if (conesOnMogo == 1) {
		a.maxHeight = 1420;
	} else if (conesOnMogo == 2) {
		a.maxHeight = 1550;
	} else if (conesOnMogo == 3) { // works
		a.maxHeight = 1670;
	} else if (conesOnMogo == 4) {
		a.maxHeight = 1920;
	} else if (conesOnMogo == 5) { // works
		a.maxHeight = 2070;
	} else if (conesOnMogo == 6) {
		a.maxHeight = 2140;
	} else if (conesOnMogo == 7) {
		a.maxHeight = 2280;
	} else if (conesOnMogo == 8) {
		a.maxHeight = 2410;
	} else if (conesOnMogo == 9) {
		a.maxHeight = 2510;
	} else if (conesOnMogo == 10) {
		a.maxHeight = 2640;
	} else if (conesOnMogo == 11) {
		a.maxHeight = 2900;
	} else if (conesOnMogo <= 12) {
		a.maxHeight = 3050;
	}

	// autostack
	startTask(autostackUp);
	while (a.stacked == false)
		wait1Msec(20);
	wait1Msec(100);

// ensure no task carries over to reset
	autostackTaskReset();
	// reset
	if (reset == FIELD) {
		startTask(fieldReset);
		while (a.stacked == true)
			wait1Msec(20);
	} else {
		startTask(matchReset);
	}
}

task autonStack() {
	// autostack up
	a.maxHeight = 1450;

	startTask(autostackUp);
	while (a.stacked == false)
		wait1Msec(20);
	//autostackTaskReset();
}

task autonReset() {
	// field reset
	startTask(fieldReset);

	// wait
	while (a.stacked == true)
		wait1Msec(20);

	// ensure no task carries over to drive
	abortAutostack();
}
