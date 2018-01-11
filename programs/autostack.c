// main autostack logic
task autostackUp() {
	autostack_state.stacked = false;

	// stall torque to grip cone with (change to -30 later, 0 for testing right now)
	b_cone_intake(0);

	// raise vertibar to height farthest away from robot
	int middleHeight = 1080;
	nb_vbar_PID(middleHeight, 127, 15000);
	waitUntil(SensorValue[TopLiftPot] > middleHeight - 100);

	// begin raising lift to target height
	nb_lift(autostack_state.maxHeight, 127, 5000);
	waitUntil(SensorValue[MainLiftPot] > autostack_state.maxHeight - 100);

	// once the lift is almost at the top, raise vertibar all the way (fully back) and keep it there
	stopTask(nb_vbar_PID_task);
	nb_vbar(3000, 127, 5000);
	waitUntil(SensorValue[TopLiftPot] > 3000);
	stopTask(nb_vbar_task);

	b_vbar(20);

	// once the lift is at the top come down on the stack
	b_lift(-127);
	wait1Msec(200);
	b_lift(20);

	autostack_state.stacked = true;
}

task fieldReset() {
	// bring the vertibar to an intermediary angle
	int resetHeight = 500;
	nb_vbar(resetHeight, 127, 5000);

	// reset lift all the way
	waitUntil(SensorValue[TopLiftPot] < resetHeight + 600);
	nb_lift(1350, 127, 5000);

	autostack_state.stacked = false;
}

task matchReset() {

}

void autostackTaskReset() {
		// stop all tasks relating to autostack
	stopTask(autostackUp);
	stopTask(fieldReset);
	stopTask(matchReset);
	stopTask(nb_lift_task);
	stopTask(nb_lift_task);
	stopTask(nb_vbar_task);
	stopTask(nb_vbar_PID_task);
	stopTask(nb_cone_intake_task);

	// ensure no motors are moving
	b_lift(0);
	b_vbar(0);
	b_cone_intake(0);
}

void abortAutostack() {
	// stop all tasks relating to autostack
	autostackTaskReset();

	// stops waits
	autostack_state.stacked = true;
	wait1Msec(100);
	autostack_state.stacked = false;
}

bool FIELD = true;
bool MATCH = false;

void autostack(int conesOnMogo, bool reset) {
	// set height to stack cone
	switch(conesOnMogo) {
		case 0:
			autostack_state.maxHeight = 1320;
			break;
		case 1:
			autostack_state.maxHeight = 1420;
			break;
		case 2:
			autostack_state.maxHeight = 1550;
			break;
		case 3:
			autostack_state.maxHeight = 1670;
			break;
		case 4:
			autostack_state.maxHeight = 1920;
			break;
		case 5:
			autostack_state.maxHeight = 2070;
			break;
		case 6:
			autostack_state.maxHeight = 2140;
			break;
		case 7:
			autostack_state.maxHeight = 2280;
			break;
		case 8:
			autostack_state.maxHeight = 2410;
			break;
		case 9:
			autostack_state.maxHeight = 2510;
			break;
		case 10:
			autostack_state.maxHeight = 2640;
			break;
		case 11:
			autostack_state.maxHeight = 2900;
			break;
		case 12:
			autostack_state.maxHeight = 3050;
			break;
		default:
			autostack_state.maxHeight = 3050;
	}

	// autostack
	startTask(autostackUp);
	while (autostack_state.stacked == false)
		wait1Msec(20);
	wait1Msec(100);

// ensure no task carries over to reset
	autostackTaskReset();
	// reset
	if (reset == FIELD) {
		startTask(fieldReset);
		while (autostack_state.stacked == true)
			wait1Msec(20);
	} else {
		startTask(matchReset);
	}
}

task autonStack() {
	// autostack up
	autostack_state.maxHeight = 1450;

	startTask(autostackUp);
	while (autostack_state.stacked == false)
		wait1Msec(20);
	//autostackTaskReset();
}

task autonReset() {
	// field reset
	startTask(fieldReset);

	// wait
	while (autostack_state.stacked == true)
		wait1Msec(20);

	// ensure no task carries over to drive
	abortAutostack();
}
