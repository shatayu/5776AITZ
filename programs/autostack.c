// main autostack logic
task autostackUp() {
	a.stacked = false;
	// claw stall
	moveConeIntake(30);

	// bring top lift to intermediary height
	// start by powering max
	topLift.target = 1250;
	topLift.timeout = 4000;
	topLift.power = 127;
	startTask(autonTopLift);
	while (SensorValue[TopLiftPot] < 1000)
		wait1Msec(20);

	// then PI to exact intermediary height
	topLift.target = 1400;
	startTask(topLiftPI);

	// lift to desired height
	mainLift.target = a.maxHeight;
	mainLift.power = 127;
	mainLift.timeout = 4000;
	startTask(mainLiftPI);

	// after the lift has risen a certain amount begin raising top lift to max height
	while (SensorValue[MainLiftPot] < a.maxHeight - 600 && a.maxHeight > 1600)
		wait1Msec(20);

	stopTask(autonTopLift);
	stopTask(topLiftPI);
	moveTopLift(127);

	// after the vertibar rises a certain amount bring main lift to scoring height
	//while (SensorValue[TopLiftPot] < 2400)
	//	wait1Msec(20);
	//mainLift.target = a.scoringHeight;
	//mainLift.power = 60;

	// open claw at the end
	//while (abs(SensorValue[MainLiftPot] - a.scoringHeight) > 50)
	//	wait1Msec(20);
	while (abs(2750 - SensorValue[TopLiftPot]) > 100)
		wait1Msec(20);
	coneIntake.state = OPEN;
	wait1Msec(250);
	startTask(autonConeIntake);
	wait1Msec(250);
	a.stacked = true;
}

void abortAutostack() {
	// stop all forms of movement
	stopTask(autostackUp);
	stopTask(autonMainLift);
	stopTask(mainLiftPI);
	stopTask(autonTopLift);
	stopTask(topLiftPI);
	stopTask(autonConeIntake);

	// ensure no motors are moving
	moveMainLift(0);
	moveTopLift(0);
	moveConeIntake(0);
}

task fieldReset() {
	// lift to maximum height
	//mainLift.target = a.maxHeight;
	//mainLift.power = 127;
	//mainLift.timeout = 4000;
	//startTask(autonTopLift);

	// bring top lift to intermediary height
	// start by powering max
	//while (abs(SensorValue[MainLiftPot] - (a.maxHeight - 100)) > 50 && a.maxHeight > 1600)
	//	wait1Msec(20);

	// bring top lift down
	//if (SensorValue[MainLiftPot] > 1400) { // only go to middle if you need to travel down
		topLift.target = 1400;
		startTask(topLiftPI);
	//}

	// bring main lift down when top lift is sufficiently far
	while (SensorValue[TopLiftPot] > 1750)
		wait1Msec(20);

	mainLift.target = 1270;
	mainLift.power = 127;
	mainLift.timeout = 1500;
	startTask(autonMainLift);

	while (SensorValue[MainLiftPot] > mainLift.target + 400)
		wait1Msec(20);

	stopTask(topLiftPI);
	moveTopLift(-127);
	while (SensorValue[TopLiftPot] > 900)
		wait1Msec(20);
	moveTopLift(0);
}
