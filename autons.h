void deploy() {
	//autonTopLift(2000, 127);
	moveConeIntake(127);
	wait1Msec(200);
	moveConeIntake(30);
}


/*
while (SensorValue[MogoPot] < 1270)
	wait1Msec(20);
*/
void scoreOn20(){
	wait1Msec(300);
	//move forward
	autonDrive(1950,2000,127);
	autonBrake(1);
	//moving mainlift
	mainLift.target = 1750;
	mainLift.timeout = 2000;
	mainLift.power = 127;
	startTask(autonMainLift);
	//move top lift
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
	//move drive bacwards
	moveDrive(-127, -127);
	wait1Msec(500);
	//stop drive
	moveDrive(0, 0);
	//stop mogo
	moveMogoIntake(0);
}
//make sure this auton is away from driver load plate side
void mogoAuton(int direction){
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

	wait1Msec(200);

	//24
	// reset lift
	a.stacked = true;
	startTask(fieldReset);
	while (a.stacked)
		wait1Msec(20);

	// move forward, grab cone
	autonDrive(400, 1000, 70);
	autonBrake(-1);

	// close claw on cone
	coneIntake.state = CLOSED;
	startTask(autonConeIntake);
	wait1Msec(250);
	// autostack
	stopTask(autonConeIntake);
	startTask(autonStack);
	while (a.stacked)
		wait1Msec(20);

	//drives backwards
	autonDrive(6100, 2000, -127);
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
	autonDrive(3250, 2000, -127);
	autonBrake(-1);
	//rotates 90 degrees, bring lift down
	startTask(autonReset);
	autonRotate(890, 2000, 127, 1 * direction);

	//scores into the 20 point zone
	stopTask(autonReset);
	abortAutostack();
	scoreOn20();

}

// untested
void stationaryGoal(){
	moveConeIntake(30);
	mainLift.target = 2850;
	mainLift.timeout = 2000;
	mainLift.power = 127;
	startTask(autonMainLift);
	startTask(mainLiftPI);
	moveTopLift(-30);
	autonDrive(2200, 2000, 127);
	autonBrake(1);
	autonRotate(870, 2000, 127, -1);
	autonDrive(3200, 2000, 127);
	autonBrake(1);
	autonRotate(870, 2000, 127, -1);
	autonDrive(1300, 2000, 127);
	autonBrake(1);

	wait1Msec(500);
	coneIntake.state = OPEN;
	startTask(autonConeIntake);

}

void stationaryGoal2(int direction){
	//grips cone
	moveConeIntake(30);

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

void drive() {

	autonDrive(500,2000,127);
	autonBrake(1);
	autonRotate(900,2000,127,1);

}
