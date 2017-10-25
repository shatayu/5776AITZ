void autoStackHelper(int topLiftAngle, int mainLiftMaxHeight, int mainLiftScoreHeight) {
	int middleTopLiftAngle = 2000; // adjust value
	int tolerance = 20;

	// claw stall
	clawStall(true);

	// bring top lift to middle angle
	topLiftTarget = middleTopLiftAngle;
	startTask(autonTopLift);
	while (abs(SensorValue[TopLiftPot] - middleTopLiftAngle) < tolerance)
		wait1Msec(20);

	// bring main lift to necessary height
	mainLiftTarget = mainLiftMaxHeight;
	startTask(autonMainLift);
	while (abs(SensorValue[MainLiftPot] - mainLiftMaxHeight) < tolerance)
		wait1Msec(20);

	// bring vertibar to scoring angle
	topLiftTarget = topLiftAngle;
	startTask(autonTopLift);
	while (abs(SensorValue[TopLiftPot] - topLiftAngle) < tolerance);
		wait1Msec(20);

	// bring main lift to scoring height
	mainLiftTarget = mainLiftMaxHeight;
	startTask(autonMainLift);
	while (abs(SensorValue[MainLiftPot] - mainLiftScoreHeight) < tolerance)
		wait1Msec(20);

	// release cone
	coneIntakeState = OPEN;
}

/* brings lift down to neutral position */
void reset() {
	autoStackHelper(69, 69, 69, 69);
	stopAllTasks();
}

void autoStack(int conesOnMogo) {
	if (conesOnMogo == 0) {

	} else if (conesOnMogo == 1) {

	}
}
