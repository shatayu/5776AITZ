void mogo20(int direction) {
	// START RED TILE
	// deploy mogo intake
	autonMogo(500);
	// drive straight into mogo
	autonDrive(2000, 3000, 127);
	// score preload cone on mogo
	autonStack();
	// drive back
	autonDrive(2000, 3000, -127);
	// rotate 45 degrees clockwise
	autonRotate(90, 2000, 80);
	// back up into alignment with 20pt zone
	autonDrive(700, 1500, -80);
	// rotate 90 degrees counterclockwise
	autonRotate(90, 2000, 80);
	// drive straight
	autonDrive(1000, 2000, 127);
	// wait for a bit
	wait1Msec(300s);
	// drive back
	autonDrive(1000, 2000, -127);
}
