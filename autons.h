void mogo20(int direction) {
	moveConeIntake(-50);
	wait1Msec(600);
	moveConeIntake(0);

	autonTopLift(1900, 127);
	autonMainLift(1590);
	//// START RED TILE
	// deploy mogo intake
	mogoTarget = 3250;
	startTask(autonMogo);

	// drive straight into mogo
	autonDrive(6300, 7000, 127);
	autonBrake(true);

	// bring mogo in
	mogoTarget = 1460;
	startTask(autonMogo);
	int time = 0;
	while (SensorValue[MogoPot] > 1460 && time < 3000) {
		wait1Msec(20);
		time += 20;
	}

	// drive back
	autonDrive(6400, 7000, -127);
	autonBrake(false);

	//// rotate 45 degrees clockwise
	moveDrive(70, -70);
	wait1Msec(550);
	moveDrive(0, 0);

	// back up into alignment with 20pt zone
	autonDrive(2800, 2000, -127);
	autonBrake(false);

	// rotate 90 degrees counterclockwise
	moveDrive(70, -70);
	wait1Msec(1050);
	moveDrive(0, 0);

	//// drive straight
	//autonDrive(1000, 2000, 127);
	//// wait for a bit
	//wait1Msec(300);
	//// drive back
	//autonDrive(1000, 2000, -127);
}
