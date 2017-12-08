void scoreOn20(){
	wait1Msec(300);
	//move forward
	autonDrive(1950,2000,127);
	autonBrake(1);
	// moving mainlift
	mainLift.target = 1750;
	mainLift.timeout = 2000;
	mainLift.power = 127;
	startTask(autonMainLift);
	// deploy
	topLift.target = 3640;
	topLift.timeout = 2000;
	topLift.power = 127;
	startTask(autonTopLift);
	//keep moving drive forward
	moveDrive(127, 127);
	wait1Msec(250);
	//keep moving drive forward
	moveDrive(30,30);
	//MOVE MOGO
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 1270;
	startTask(autonMogoIntake);

	while (SensorValue[MogoPot] > 1270) {
		wait1Msec(20);
	}
	//bring back in the mogo
	moveMogoIntake(30);
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 1340;
	mainLift.target = 1450;
	startTask(mainLiftPI);
	//move drive backwards
	moveDrive(-127, -127);
	wait1Msec(600);
	//stop drive
	moveDrive(0, 0);
	//stop mogo
	moveMogoIntake(0);
}
