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
	autonMainLift(1790, 127);
	//// START RED TILE
	// deploy mogo intake
	mogoTarget = 3160;
	startTask(autonMogo);

	// drive straight into mogo
	autonDrive(6000, 7000, 127);
	autonBrake(true);

	// bring mogo in
	mogoTarget = 1460;
	startTask(autonMogo);

	int timer = 0; int i = 0;
	while (timer < 800 && i < 10) {
		if (i % 2 == 0) {
			mogoTarget = 1480;
		} else {
			mogoTarget = 1440;
		}
	}

	int time = 0;
	while (SensorValue[MogoPot] > 1460 && time < 3000) {
		wait1Msec(20);
		time += 20;
	}

	// drive back
	autonDrive(5000, 7000, -127);
	autonBrake(false);

	//// rotate 45 degrees clockwise
	moveDrive(70 * direction, -70 * direction);
	wait1Msec(550);
	moveDrive(0, 0);

	// back up into alignment with 20pt zone
	autonDrive(1800, 2500, -127);
	autonBrake(false);

	// rotate 90 degrees counterclockwise
	moveDrive(127 * direction, -127 * direction);
	wait1Msec(650);
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

void cone() {
	autonTopLift(1960, 127);

	autonDrive(840, 1000, 127);
	autonBrake(1)
	wait1Msec(300);
	autonDrive(300, 1000, -127);
	autonBrake(-1);

	wait1Msec(400);

	moveConeIntake(80);
	wait1Msec(300);
	moveConeIntake(0);


	// lift to right height

	clawStall(true);
	autonMainLift(2270, 80);
	autonTopLift(1620, 80);

	// score cone
	autonDrive(930, 2000, 127);
	autonBrake(1);
	wait1Msec(500);
	autonConeIntake(OPEN);

	autonDrive(800, 2000, -127);
}
