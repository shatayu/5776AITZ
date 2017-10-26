void autoStackHelper(int topLiftAngle, int mainLiftMaxHeight, int mainLiftScoreHeight) {
	int middleTopLiftAngle = 1910; // adjust value
	int tolerance = 70;

	// claw stall
	clawStall(true);

	// bring top lift to middle angle
	autonTopLift(middleTopLiftAngle);


	// bring main lift to necessary height
	autonMainLift(mainLiftMaxHeight);
	//writeDebugStream("Main lift at necessary height");

	// bring vertibar to scoring angle
	autonTopLift(topLiftAngle);
	writeDebugStream("Vertibar at scoring angle");

	// bring main lift to scoring height
	if (mainLiftMaxHeight != mainLiftScoreHeight)
		autonMainLift(mainLiftScoreHeight);

	autonConeIntake(OPEN);

	// RESET	// bring main lift back to max height
	autonMainLift(mainLiftMaxHeight);
}

void reset() {
		int middleTopLiftAngle = 1910; // adjust value
	int tolerance = 70;
	//// bring top lift back to middle height
	stopTask(holdTopLift);
	moveTopLift(-127);
	wait1Msec(20000);
	autonTopLift(middleTopLiftAngle);

	//// bring main lift down to base height
	//int baseMainLiftHeight = 1460;
	autonMainLift(1460);

	//// being top lift back to base height
	autonTopLift(1200);
}

/* brings lift down to neutral position */
void autoStack(int conesOnMogo) {
	if (conesOnMogo == 0 || conesOnMogo == 1) {
		autoStackHelper(3550, 1470, 1470);
	} else if (conesOnMogo == 2) {
		autoStackHelper(3630, 1590, 1590);
	} else if (conesOnMogo == 3) {
		autoStackHelper(3750, 1690, 1690);
	} else if (conesOnMogo == 4) {
		autoStackHelper(3750, 1810, 1810);
	} else if (conesOnMogo == 5) {
		autoStackHelper(3750, 1880, 1880);
	} else if (conesOnMogo == 6) {
		autoStackHelper(3750, 1980, 1980);
	} else if (conesOnMogo == 7) {
		autoStackHelper(3750, 2080, 2080);
	} else if (conesOnMogo == 8) {
		autoStackHelper(3750, 2160, 2160);
	} else if (conesOnMogo == 9) {
		autoStackHelper(3750, 2230, 2230);
	} else if (conesOnMogo == 10) {
		autoStackHelper(3750, 2300, 2300);
	} else if (conesOnMogo >= 11 && conesOnMogo <= 15) {
		autoStackHelper(3750, 2700, 2700);
		reset();
	}
}
