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

//make sure this auton is away from driver load plate side
void mogo24(int direction){
	//keeps cone in claw
	moveConeIntake(30);

	//drive forwrd towards mogo (deploy)
	autonDrive(400, 2000, 127);

	// raise lift
	moveMainLift(127);
	waitUntil(SensorValue[MainLiftPot] > 1500);
	moveMainLift(0);

	//moves mogo intake outward
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 740;
	startTask(autonMogoIntake);

	// move vertibar up
	topLift.target = 2750;
	topLift.timeout = 2000;
	topLift.power = 127;

	startTask(autonTopLift);

	// do not proceed until the mogo is out
	waitUntil(SensorValue[MogoPot] < 1400);

	// continue driving forward after everything is out
	//autonDrive(3700, 2000, 127);
	autonDrive(2800, 2000, 127);
	autonDrive(800, 2000, 70);
	autonDrive(400, 2000, 50);
	autonBrake(1);

	//takes mogo back in
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 2720;
	startTask(autonMogoIntake);

	// checks and waits until the mogo value is at a set value
	waitUntil(SensorValue[MogoPot] > 2620);

	// bring lift down
	moveMainLift(-127);
	wait1Msec(200);
	moveMainLift(0);

	wait1Msec(300);
	// opens up the claw to drop cone
	moveConeIntake(-127);
	wait1Msec(250);
	moveConeIntake(-15);

	//24
	// reset top lift
	moveTopLift(-127);
	waitUntil(SensorValue[TopLiftPot] < 1000);
	moveTopLift(0);

	// move forward, grab cone
	autonDrive(550, 1000, 70);
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
	autonDrive(6400, 5000, -80);
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
	autonDrive(2700, 2000, -80);
	autonBrake(-1);
	//rotates 90 degrees, bring lift down
	startTask(autonReset);
	autonRotate(890, 2000, 80, 1 * direction);

	//scores into the 20 point zone
	stopTask(autonReset);
	abortAutostack();
	scoreOn20();

}

// stationary goal auton
void stationaryGoal(int direction){
	//grips cone
	moveConeIntake(30);

	//drives forward
	autonDrive(400, 2000, 127);
	autonBrake(1);

	//moves main lift
	mainLift.target = 2850;
	mainLift.timeout = 2000;
	mainLift.power = 127;
	startTask(autonMainLift);
	startTask(mainLiftPI);

	//moves top lift
	moveTopLift(-30);

	//rotates 90 degrees
	autonRotate(900, 2000, 70, -1 * direction);

	//drives forward towards stationary
	autonDrive(2000, 2000, 127);
	autonBrake(1);

	wait1Msec(500);
	stopTask(mainLiftPI);
	mainLift.target = 2400;
	mainLift.power = 127;
	mainLift.timeout = 3000;

	startTask(autonMainLift);

	waitUntil(SensorValue[MainLiftPot] < 2500);

	coneIntake.state = OPEN;
	startTask(autonConeIntake);
	wait1Msec(300);

	//drives backwards
	autonDrive(500, 2000, -127);

	moveMainLift(-127);
	wait1Msec(700);
	moveMainLift(0);

	//rotates towards mogo
	autonRotate(870, 2000, 127, 1 * direction);

	//drives forward
	autonDrive(500, 2000, 127);

	//stops PID
	stopTask(mainLiftPI);
}

void mogo22(int direction){

// SCORE 20
	//keeps cone in claw
	moveConeIntake(30);
	//check and waits until top lift is a a set value
	while(SensorValue[TopLiftPot] < 1375){
		wait1Msec(20);
	}

	//drive forwrd towards mogo
	autonDrive(600, 2000, 127);

		//moves mogo intake outward
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 740;
	startTask(autonMogoIntake);

	//moves top lift
	topLift.target = 2750;
	topLift.timeout = 2000;
	topLift.power = 127;
	startTask(autonTopLift);
	//keeps the top lift at the highest
	moveTopLift(40);

	// continue driving
	autonDrive(4700, 2000, 127);
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

/*
programming skills (currently 40 points, planning to go 72):

* orient away from match loads

- score edge mogo in 20 with preload
- score two mogos near stationary goal in 10

- drive across and score one far center mogo in 20
- score second far center mogo in 10
- score corner mogo in 10

*/

void pskills(int direction) {
	// SCORE 20
	//keeps cone in claw
	moveConeIntake(30);

	// deploy
	autonDrive(400, 2000, 127);

	//keeps the top lift at the highest
	moveTopLift(40);
	//moves mogo intake outward
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 740;
	startTask(autonMogoIntake);

		//moves top lift
	topLift.target = 2750;
	topLift.timeout = 2000;
	topLift.power = 127;
	startTask(autonTopLift);
	//check and waits until top lift is a a set value
	while(SensorValue[TopLiftPot] < 1375){
		wait1Msec(20);
	}

	//drive forwrd towards mogo
	autonDrive(4700, 2000, 127);
	autonBrake(1);

	//takes mogo back in
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 2520;
	startTask(autonMogoIntake);

	// checks and waits until the mogo value is at a set value
	while(SensorValue[MogoPot] < 2470){
		wait1Msec(20);
	}
	wait1Msec(250);
	// opens up the claw to drop cone
	coneIntake.state = OPEN;
	startTask(autonConeIntake);

	wait1Msec(400);

	//drives backwards
	autonDrive(5500, 2000, -127);
	autonBrake(-1);
	//swing rotates 45 degrees
	stopTask(autonStack);
	//autonRotate(420, 2000, 127, 1* direction);

	SensorValue[Gyro] = 0;
	while (abs(SensorValue[Gyro]) < 430) {
		if (direction == 1) {
			moveDrive(80, 0);
		} else {
			moveDrive(0, 80);
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

	// tune distance here: diagonal backward
	autonDrive(2200, 2000, -127);
	autonBrake(-1);
	//rotates 90 degrees, bring lift down
	startTask(autonReset);
	autonRotate(900, 2000, 80, 1 * direction);

	//scores into the 20 point zone and backs out
	stopTask(autonReset);
	abortAutostack();
	scoreOn20();

	/*
	SECOND MOGO
	*/
	wait1Msec(1000);
	// stall torque to keep vertibar up
	topLift.target = 2750;
	startTask(autonTopLift);

	// turn 90 degrees clockwise to begin grabbing left near center mogo
	autonRotate(890, 2000, 80, 1 * direction);

	// move forward to line up, extend mobile goal to prepare to collect mobile goal
	mogoIntake.state = 740;
	startTask(autonMogoIntake);
	autonDrive(800, 2000, 127);
	autonBrake(1);

	// turn 90 degrees, now facing mobile goal
	autonRotate(900, 2000, 80, 1 * direction);
	stopTask(autonMogoIntake);

	// collect mobile goal
	autonDrive(2700, 2000, 127);
	autonBrake(1);

	// begin withdrawing mobile goal intake to scoring height, rotate to face backwards
	mogoIntake.state = 2650;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] < mogoIntake.state)
		wait1Msec(20);
	stopTask(autonMogoIntake);
	autonRotate(1850, 6000, 80, -1 * direction);

	// score mogo in 10
	mogoIntake.state = 1270;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] > mogoIntake.state)
		wait1Msec(20);
	stopTask(autonMogoIntake);
	moveMogoIntake(30); // stall torque to keep mogo up
	autonDrive(3600, 3000, 127);
	autonBrake(1);

	//drive out of scoring zone
	autonDrive(300, 3000, -127);
	autonBrake(-1);
	moveMogoIntake(0);

	/*
	THIRD mogo
	*/

	//rotate counter clockwise towards next mogo
	autonRotate(900, 2000, 70, -1 * direction);

	//drive diagonal
	autonDrive(3100, 2000, 127);//tune distance
	autonBrake(1);

	//take out mogo intake
	mogoIntake.state = 740;
	startTask(autonMogoIntake);

	//rotate towards third mogo
	autonRotate(900, 2000, 70, -1);

	//drive forward to get mogo
	autonDrive(2300, 2000, 127);
	autonBrake(1);

	// begin withdrawing mobile goal intake to scoring height, rotate to face backwards
	mogoIntake.state = 2625;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] < mogoIntake.state)
		wait1Msec(20);
	stopTask(autonMogoIntake);
	autonDrive(700, 3000, -127);
	autonBrake(-1);
	autonRotate(1800, 2000, 90, 1 * direction);

	//take out mogo and move forward to score
	mogoIntake.state = 1270;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] > 1260)
		wait1Msec(20);
	stopTask(autonMogoIntake);
	moveMogoIntake(30); // stall torque to keep mogo up

	//score on 10
	autonDrive(2400, 3000, 127);
	autonBrake(1);

	//move out of 10 point zone
	autonDrive(500, 3000, -127);
	autonBrake(-1);

	//rotate 180 towards next mogo
	autonRotate(1840, 2000, 80, -1 * direction);

	/*
	FOURTH MOGO
	*/

	//take out mogointake
	mogoIntake.state = 740;
	startTask(autonMogoIntake);

	//drive forward
	autonDrive(7500,2000,127);
	autonBrake(1);
	// gather mogo
	mogoIntake.state = 2650;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] < mogoIntake.state)
		wait1Msec(20);
	stopTask(autonMogoIntake);

	// continue driving forward second distance
	autonDrive(2900, 2000, 127);

	//take a 90 degree turn counterclockwise
	autonRotate(900, 5000, 127, -1 * direction);

	//drive forward a little (tune this distance) 1200
	autonDrive(1200, 2000, 127);

	//take a 90 degree turn clockwise
	autonRotate(900, 5000, 127, 1 * direction);

	//score on 20
	scoreOn20();

		mogoIntake.state = 2650;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] < mogoIntake.state)
		wait1Msec(20);
	stopTask(autonMogoIntake);

		/*
	FIFTH MOGO
	*/

	//rotates towords next mogo
	autonRotate(900, 2000, 80, 1 * direction);

	//allign with next mogo diagnol
	autonDrive(1850, 2000, 127);

	//alligned stright towords mogo
	autonRotate(450, 2000, 80, 1*direction);


	//moves mogo intake outward
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 740;
	startTask(autonMogoIntake);
	//drive forwrd towards mogo
	autonDrive(6000, 2000, 127);
	autonBrake(1);
	//takes mogo back in
	mogoIntake.power = 127;
	mogoIntake.timeout = 3000;
	mogoIntake.state = 2720;
	startTask(autonMogoIntake);
	// checks and waits until the mogo value is at a set value
	while(SensorValue[MogoPot] < 2670){
		wait1Msec(20);
	}
	wait1Msec(250);

	//drives backwards
	autonDrive(5900, 2000, -127);
	autonBrake(-1);
	//swing rotates 45 degrees

	autonRotate(450, 2000, 80, -1* direction);

	// tune distance here: diagonal backward
	autonDrive(1000, 2000, -127);
	autonBrake(-1);

	//rotates 90 degrees, bring lift down
	autonRotate(900, 2000, 80, -1 * direction);

	// score mogo in 10
	mogoIntake.state = 1270;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] > mogoIntake.state)
		wait1Msec(20);
	stopTask(autonMogoIntake);
	moveMogoIntake(30); // stall torque to keep mogo up
	autonDrive(500, 3000, 127);
	autonBrake(1);

	//drive out of scoring zone
	autonDrive(500, 3000, -127);
	autonBrake(-1);
	moveMogoIntake(0);

	/*
	SIXTH MOGO
	*/

	autonRotate(900, 2000, 80, -1* direction);

	//align with 5th mogo, bring mogo out
	mogoIntake.state = 740;
	startTask(autonMogoIntake);
	autonDrive(2000, 2000, 127);
	autonBrake(1);

	// turn 90 degrees, now facing mobile goal
	autonRotate(900, 2000, 80, -1 * direction);
	stopTask(autonMogoIntake);

	// collect mobile goal
	autonDrive(2700, 2000, 127);
	autonBrake(1);

	// begin withdrawing mobile goal intake to scoring height, rotate to face backwards
	mogoIntake.state = 2650;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] < mogoIntake.state)
		wait1Msec(20);
	stopTask(autonMogoIntake);
	autonRotate(1810, 6000, 85, -1 * direction);

	// score mogo in 10
	mogoIntake.state = 1270;
	startTask(autonMogoIntake);
	while (SensorValue[MogoPot] > mogoIntake.state)
		wait1Msec(20);
	stopTask(autonMogoIntake);
	moveMogoIntake(30); // stall torque to keep mogo up
	autonDrive(2600, 3000, 127);
	autonBrake(1);

	//drive out of scoring zone
	autonDrive(500, 3000, -127);
	autonBrake(-1);
	moveMogoIntake(0);
}
