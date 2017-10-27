void mogo20(int direction) {
	// START RED TILE
	// deploy mogo intake
	mogoTarget = 3190;
	startTask(autonMogo);
	// drive straight into mogo
	autonDrive(2000, 3000, 127);
	autonBrake(true);
	// score preload cone on mogo
	autoStack(0);
	// drive back
	autonDrive(2000, 3000, -127);
	autonBrake(false);
	// rotate 45 degrees clockwise
	autonRotate(90, 2000, 80);
	// back up into alignment with 20pt zone
	autonDrive(700, 1500, -80);
	// rotate 90 degrees counterclockwise
	autonRotate(90, 2000, 80);
	// drive straight
	autonDrive(1000, 2000, 127);
	// wait for a bit
	wait1Msec(300);
	// drive back
	autonDrive(1000, 2000, -127);
	

}

// assumes that you are at the 20 point mark
//drives backward for you
void scoreOn20(){

	//puts the mogo claw all the way out
	moveMogoIntake(127);
	wait1Msec(2500);

	//drives backward without moving the mogo
	autonDrive(1000,2000,-80);

	//pulls the mogo claw back up
	moveMogoIntake(-127);
	wait1Msec(500);

	moveMogoIntake(0);
}
	bool OPEN = true;
	bool CLOSED = false;

void skillsMatchLoads(int cones){
	for(int i = 0; i<cones;i++){
	//open claw up
	autonConeIntake(OPEN);
	//rotate 45 degrees counter-clockwise
	autonRotate(45,2000,-80);
	//drive back allign to pick up cone
	autonDrive(500,2000,127);
	//Pick up cone
	pickUpCone();
	//rotate 135 degrees clockwise
	autonRotate(135,2000,80);
	//drive straight to allign with the post
	autonDrive(500,2000,80);
	//rotate 135 degrees counterclockwise to allign with post
	autonRotate(135,2000,-80);
	// score the cone onto post
	scoreOnPost();
	//reset bot
	reset();
}
	//run mogo20 code
	mogo20(1);

}
//assumes the bot is ready to pick up cone
void pickUpCone(){
	//lift claw up to height of cone
	autonTopLift(2000,127);
	//closes claw to grab cone
	autonConeIntake(CLOSED);
	//lifts cone up
	autonTopLift(2500,127);
	//drives backward
	autonDrive(500,2000,-127);

}
//assumes that bot is already in position to score onto post
void scoreOnPost(){
	//lift top lift to max hieght with cone
	autonTopLift(3640,127);
	//moves forward twords the post
	autonDrive(500,2000,127);
	//drops down the lift
	autonTopLift(2000,127);
	//releseas claw
	autonConeIntake(OPEN);
	// drives backward
	autonDrive(500,2000,-127);
	//reset bot
	reset();
	wait1Msec(500);
}

//assumes bot is at original starting point
void robotPark(){

	autonDrive(2000,2000,127);

}

