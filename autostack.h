

void autoStackHelper(int topLiftAngle, int mainLiftMaxHeight, bool matchLoad) {
	int middleTopLiftAngle = 1400; // adjust value
	int tolerance = 20;


	// claw stall
	moveConeIntake(30);

	// move top lift to middle angle
	if (!matchload) {
		autonTopLift(middleTopLiftAngle, 127);
	}

	// bring main lift to necessary height
	if (SensorValue[MainLiftPot] < mainLiftMaxHeight)
		autonMainLift_SWAG(mainLiftMaxHeight, 3000);
		//autonMainLift(mainLiftMaxHeight, 3000, 127);

	// bring vertibar to scoring angle
	// insert deceleration curve here
	stopTask(topLiftPI);
	autoDecelTopLift(topLiftAngle);
	//autonTopLift(topLiftAngle, 127);
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
		autoStackHelper(3000, 1350, matchLoad); //no lift
	} else if (conesOnMogo == 1) {
		autoStackHelper(3000, 1500, matchLoad);
	} else if (conesOnMogo == 2) {
		autoStackHelper(3000, 1730, matchLoad);
	} else if (conesOnMogo == 3) {
		autoStackHelper(3000, 1870, matchLoad);
	} else if (conesOnMogo == 4) {
		autoStackHelper(3000, 1930, matchLoad); // works
	} else if (conesOnMogo == 5) {
		autoStackHelper(3000, 2080, matchLoad);
	} else if (conesOnMogo == 6) {
		autoStackHelper(3000, 2180, matchLoad);
	} else if (conesOnMogo == 7) {
		autoStackHelper(3000, 2360, matchLoad); // works
	} else if (conesOnMogo == 8) {
		autoStackHelper(3000, 2470, matchLoad);
	} else if (conesOnMogo == 9) {
		autoStackHelper(3000, 2600, matchLoad);
	} else if (conesOnMogo == 10) {
		autoStackHelper(3000, 2780, matchLoad);
	} else if (conesOnMogo == 11) {
		autoStackHelper(3000, 2970, matchLoad); // last untested
	} else if (conesOnMogo == 12) {
		autoStackHelper(3000, 3170, matchLoad);
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
