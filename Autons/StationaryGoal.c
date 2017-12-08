// stationary goal auton
void stationaryGoal(int direction){
	//grips cone
	moveConeIntake(30);

	// deploy
	moveTopLift(127);
	wait1Msec(800);
	moveTopLift(0);

	//moves main lift
	mainLift.target = 2850;
	mainLift.timeout = 2000;
	mainLift.power = 127;
	startTask(autonMainLift);
	startTask(mainLiftPI);

	//drives forward
	autonDrive(400, 2000, 127);
	autonBrake(1);

	//moves top lift
	moveTopLift(-30);

	//rotates 90 degrees
	autonRotate(900, 2000, 70, -1 * direction);

	//drives forward towards stationary
	autonDrive(2000, 2000, 127);
	autonBrake(1);

	wait1Msec(500);

	//opens up claw
	coneIntake.state = OPEN;
	startTask(autonConeIntake);
	wait1Msec(300);

	//drives backwards
	autonDrive(500, 2000, -127);

	//rotates towards mogo
	autonRotate(870, 2000, 127, 1 * direction);

	//drives forward
	autonDrive(500, 2000, 127);

	//pulls out mogo intake
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 740;
	startTask(autonMogoIntake);

	//stops PID
	stopTask(mainLiftPI);
}
