void autoStackHelper(int topLiftAngle, int mainLiftMaxHeight, int mogoAngle) {
	int middleTopLiftAngle = 1910; // adjust value
	int tolerance = 50;

	// claw stall
	clawStall(true);

	// bring top lift to middle angle
	autonTopLift(middleTopLiftAngle, 127);

	if (mogoAngle != 1) {
		mogoTarget = mogoAngle;
		startTask(autonMogo);
	}
	// bring main lift to necessary height
	autonMainLift(mainLiftMaxHeight, 127);

	// bring vertibar to scoring angle
	autonTopLift(topLiftAngle, 127);

	autonConeIntake(OPEN);
}

void reset() {
	int middleTopLiftAngle = 1910; // adjust value
	int tolerance = 70;
	//// bring top lift back to middle height
	stopTask(holdTopLift);
	autonTopLift(middleTopLiftAngle, 127);

	//// bring main lift down to base height
	//int baseMainLiftHeight = 1460;
	autonMainLift(1440, 127);
	mogoTarget = 1380;
	startTask(autonMogo);

	//// being top lift back to base height
	autonTopLift(1720, 50);
	stopTask(holdTopLift);
}

/* brings lift down to neutral position */
void autoStack(int conesOnMogo) {
	if (conesOnMogo == 0) {
		autoStackHelper(3790, 1580, 1400);
	} else if (conesOnMogo == 1) {
		autoStackHelper(3790, 1580, 1400);
	} else if (conesOnMogo == 2) {
		autoStackHelper(3350, 1660, 1400);
	} else if (conesOnMogo == 3) {
		autoStackHelper(3790, 1750, 1500);
	} else if (conesOnMogo == 4) {
		autoStackHelper(3790, 1810, 1500);
	} else if (conesOnMogo == 5) {
		autoStackHelper(3690, 1870, 1400);
	} else if (conesOnMogo == 6) {
		autoStackHelper(3750, 1980, 1500);
	} else if (conesOnMogo == 7) {
		autoStackHelper(3750, 2080, 1500);
	} else if (conesOnMogo == 8) {
		autoStackHelper(3750, 2160, 1);
	} else if (conesOnMogo == 9) {
		autoStackHelper(3650, 2230, 1);
	} else if (conesOnMogo == 10) {
		autoStackHelper(3650, 2300, 1);
	} else if (conesOnMogo == 11) {
		autoStackHelper(3650, 2400, 1);
	} else if (conesOnMogo == 12) {
		autoStackHelper(3650, 2480, 1);
	} else if (conesOnMogo == 13) {
		autoStackHelper(3650, 2580, 1);
	} else if (conesOnMogo == 14) {
		autoStackHelper(3650, 2720, 1);
	}
}
