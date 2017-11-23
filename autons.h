void deploy() {
	autonTopLift(2000, 127);
	moveConeIntake(127);
	wait1Msec(200);
	moveConeIntake(30);
}

void scoreOn20(){
	autonMainLift(1800, 3000, 127):
	moveDrive(127, 127);
	wait1Msec(1300);
	moveDrive(0, 0);
	//puts the mogo claw all the way out
	moveMogoIntake(-127);
	wait1Msec(1050);
	moveMogoIntake(0);
	//drives backward without moving the mogo
	moveDrive(0, 0);

	moveDrive(-127, -127);
	wait1Msec(300);
	moveDrive(0, 0);

		moveMogoIntake(127);
	wait1Msec(1050);
	moveMogoIntake(0);
	//pulls the mogo intake back up
	autonDrive(1500,2000,-127);

}

void mogoAuton(int direction){
	//set up
	autonMainLift(1450, 3000, 127);
	moveMogoIntake(-127);
	wait1Msec(1050);
	moveMogoIntake(0);

	autonDrive(5600,2000,127);
	autonBrake(1);
	moveMogoIntake(127);
	wait1Msec(1150);
	moveMogoIntake(0);
	autonBrake(-1);

	autonTopLift(3000, 127);
	autonConeIntake(true);
	reset();

	//moveConeIntake(-127);
	//wait1Msec(200);
	//moveConeIntake(-30);
	//autonDrive(700,2000,70);
	//autonBrake(1);
	//wait1Msec(200);
	//autonConeIntake(CLOSED);
	//autoStack(1,false);
	//reset();

	autonDrive(5450,2000,-127);
	autonBrake(-1);
	autonRotate(450,2000,127,direction);
	autonDrive(2000,2000,-127);
	autonRotate(820,2000,127,1 *direction);
	//scoreOn20();
	autonTopLift(2000,127);
	scoreOn20();
}

// untested
void stationaryGoal(int direction){
	// 2 point
	// line up
	moveConeIntake(30);
	autonDrive(900,2000,127);
	autonBrake(1);
	autonRotate(900,2000,127,-1);
	autonDrive(1700,2000,127);
	autonBrake(1);
	autonRotate(900,2000,127,-1);

	// score
	autonTopLift(2235,127);
	autonMainLift(2200,2000,127);
	autonConeIntake(OPEN);

	// 4 point
	autonDrive(500, 2000, -127);
	autonRotate(900, 2000, 127, 1 * direction);
	autonDrive(1000, 2000, 127);
	autonConeIntake(-1);
	autonMainLift(2400, 2000, 127);
	autonDrive(1000, 2000, -127);
	autonRotate(900, 2000, 127, -1 * direction);
	autonDrive(500, 2000, 127);
	autonConeIntake(OPEN);
}

void drive() {

	autonDrive(500,2000,127);
	autonBrake(1);
	autonRotate(900,2000,127,1);

}
