void scoreOn20(){

	//puts the mogo claw all the way out
	moveMogoIntake(127);
	wait1Msec(2500);

	//drives backward without moving the mogo
		moveDrive(-127, -127);
	wait1Msec(1500);
	moveDrive(0, 0);

	//pulls the mogo claw back up
	moveMogoIntake(-127);
	wait1Msec(500);

	moveMogoIntake(0);
}

void mogo20(int direction) {
//height for the post is equal to autostack(5)
	autonTopLift(1900, 127);
	autonMainLift(1590, 127);
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
	autonDrive(6200, 7000, -127);
	autonBrake(false);

	//// rotate 45 degrees clockwise
	moveDrive(-70, 70);
	wait1Msec(550);
	moveDrive(0, 0);

	// back up into alignment with 20pt zone
	autonDrive(1800, 2000, -127);
	autonBrake(false);

	// rotate 90 degrees counterclockwise
	moveDrive(-60, 60);
	wait1Msec(1050);
	moveDrive(30, -30);
	wait1Msec(50);
	moveDrive(0, 0);


	// drive straight
	moveDrive(127, 127);
	wait1Msec(1500);
	moveDrive(0, 0);
	// wait for a bit

	//puts the mogo claw all the way out
	stopTask(holdMogo);
	moveMogoIntake(127);
	wait1Msec(1500);

	//drives backward without moving the mogo
	moveDrive(-127, -127);
	wait1Msec(1500);
	moveDrive(0, 0);

	//pulls the mogo claw back up
	moveMogoIntake(-127);
	wait1Msec(500);

	moveMogoIntake(0);
}
