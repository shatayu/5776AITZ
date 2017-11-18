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

void mogoAuton(int direction){
	//set up
	moveConeIntake(30);
	autonMainLift(1500,2000,127);

	moveMogoIntake(-127);
	wait1Msec(1150);
	moveMogoIntake(0);

	autonDrive(5100,2000,127);
	autonBrake(1);
	moveMogoIntake(127);
	wait1Msec(1150);
	moveMogoIntake(0);
	autonBrake(-1);
	autoStack(0,true);
	reset();

	autonDrive(700,2000,70);
	autonBrake(1);
	wait1Msec(200);
	autonConeIntake(CLOSED);
	autoStack(1,false);
	reset();

	autonDrive(5900,2000,-127);
	autonBrake(-1);
	autonRotate(450,2000,127,1);
	autonDrive(2700,2000,-127);
	autonRotate(860,2000,127,1);
	scoreOn20();

}

// untested
void stationaryGoal(){
	moveConeIntake(30);
	autonDrive(900,2000,127);
	autonBrake(1);
	autonRotate(900,2000,127,-1);
	autonDrive(1700,2000,127);
	autonBrake(1);
	autonRotate(900,2000,127,-1);
	//hieght 2160, angle 2235
	autonTopLift(2235,127);
	autonMainLift(2200,2000,127);
	autonConeIntake(OPEN);


}

void drive() {

	autonDrive(500,2000,127);
	autonBrake(1);
	autonRotate(900,2000,127,1);

}
