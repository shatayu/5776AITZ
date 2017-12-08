void mogo22(int direction){

// SCORE 20
	//keeps cone in claw
	moveConeIntake(30);
	//moves top lift
	topLift.target = 2750;
	topLift.timeout = 2000;
	topLift.power = 127;
	startTask(autonTopLift);
	//check and waits until top lift is a a set value
	while(SensorValue[TopLiftPot] < 1375){
		wait1Msec(20);
	}
	//keeps the top lift at the highest
	moveTopLift(40);
	//moves mogo intake outward
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 740;
	startTask(autonMogoIntake);
	//drive forwrd towards mogo
	autonDrive(5300, 2000, 127);
	autonBrake(1);
	//takes mogo back in
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 2720;
	startTask(autonMogoIntake);
	// checks and waits until the mogo value is at a set value
	while(SensorValue[MogoPot] < 2690){
		wait1Msec(20);
	}
	wait1Msec(250);
	// opens up the claw to drop cone
	coneIntake.state = OPEN;
	startTask(autonConeIntake);

	wait1Msec(100);

	//drives backwards
	autonDrive(5700, 2000, -127);
	autonBrake(-1);
	//swing rotates 45 degrees
	stopTask(autonStack);
	//autonRotate(420, 2000, 127, 1* direction);

	SensorValue[Gyro] = 0;
	while (abs(SensorValue[Gyro]) < 430) {
		if (direction == 1) {
			moveDrive(127, 0);
		} else {
			moveDrive(0, 127);
		}
	}

	if (direction == 1) {
		moveDrive(-30, 0);
	} else {
		moveDrive(0, -30);
	}
	wait1Msec(100);
	moveDrive(0, 0);

	//drive backwards
	wait1Msec(250);

	// tune distance here
	autonDrive(2900, 2000, -127);
	autonBrake(-1);
	//rotates 90 degrees, bring lift down
	startTask(autonReset);
	autonRotate(890, 2000, 127, 1 * direction);

	//scores into the 20 point zone and backs out
	stopTask(autonReset);
	abortAutostack();
	scoreOn20();

}
