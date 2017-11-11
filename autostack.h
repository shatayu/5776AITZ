void autoStackHelper(int topLiftAngle, int mainLiftMaxHeight, bool matchLoad) {
	int middleTopLiftAngle = 1400; // adjust value
	int tolerance = 20;


	// claw stall
	moveConeIntake(30);

	if (!matchload)
		autonTopLift(middleTopLiftAngle, 127);

	// bring main lift to necessary height
	if (SensorValue[MainLiftPot] < mainLiftMaxHeight)
		autonMainLift(mainLiftMaxHeight, 3000, 127);

	// bring vertibar to scoring angle
	stopTask(topLiftPI);
	autonTopLift(topLiftAngle, 127);
	stopTask(topLiftPI);

	autonConeIntake(OPEN);
}

void reset() {
	// bring top lift back to middle height
	autonTopLift(1400, 127);
	// bring main lift down to base height
	if (SensorValue[MainLiftPot] > 1450)
		autonMainLift(1420, 6000, 127);

	//// being top lift back to base height
	autonTopLift(880, 127);
}

/* brings lift down to neutral position */
void autoStack(int conesOnMogo, bool matchLoad) {
	if (conesOnMogo == 0) {
		autoStackHelper(3000, 1400, matchLoad);
	} else if (conesOnMogo == 1) {
		autoStackHelper(3000, 1480, matchLoad);
	} else if (conesOnMogo == 2) {
		autoStackHelper(3000, 1650, matchLoad;
	} else if (conesOnMogo == 3) {
		autoStackHelper(3000, 1800, matchLoad);
	} else if (conesOnMogo == 4) {
		autoStackHelper(3000, 1970, matchLoad);
	} else if (conesOnMogo == 5) {
		autoStackHelper(3000, 2070, matchLoad); // works
	} else if (conesOnMogo == 6) {
		autoStackHelper(3000, 2160, matchLoad);
	} else if (conesOnMogo == 7) {
		autoStackHelper(3000, 2350, matchLoad);
	} else if (conesOnMogo == 8) {
		autoStackHelper(3000, 2480, matchLoad); // works
	} else if (conesOnMogo == 9) {
		autoStackHelper(3000, 2650, matchLoad);
	} else if (conesOnMogo == 10) {
		autoStackHelper(3000, 2750, matchLoad);
	} else if (conesOnMogo == 11) {
		autoStackHelper(3000, 2900, matchLoad);
	} else if (conesOnMogo == 12) {
		autoStackHelper(3000, 3280, matchLoad); // last untested
	} else if (conesOnMogo == 13) {
		autoStackHelper(3000, 2580, matchLoad);
	} else if (conesOnMogo == 14) {
		autoStackHelper(3000, 2720, matchLoad);
	}
}

void matchLoadReset() {
		// bring top lift back to middle height
	autonTopLift(2150, 127);
	// bring main lift down to base height
	autonMainLift(1640, 6000, 127);
	stopTask(mainLiftPI);
	moveMainLift(127);
	wait1Msec(50);
	moveMainLift(0);
	startTask(mainLiftPI);
}
