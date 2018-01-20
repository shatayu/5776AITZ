// main autostack logic
task autostackUp() {
	// open claw position = 1350
	autostack_state.stacked = false;

	// stall torque to grip cone with (change to -30 later, 0 for testing right now)
	b_cone_intake(-30);

	// raise vertibar to height farthest away from robot
	int middleHeight = 1280;
	nb_vbar_PID(middleHeight, 127, 15000);
	waitUntil(SensorValue[TopLiftPot] > middleHeight - 200);

	// begin raising lift to target height
	nb_lift(autostack_state.maxHeight, 127, 15000);
	waitUntil(SensorValue[MainLiftPot] > autostack_state.maxHeight - 100);

	// once the lift is almost at the top, raise vertibar all the way (fully back) and keep it there
	stopTask(nb_vbar_PID_task);
	nb_vbar_PID(autostack_state.vbarHeight, 127, 5000);
	waitUntil(SensorValue[TopLiftPot] >=	autostack_state.vbarHeight);

	// once the lift is at the top come down on the stack
	startTask(nb_lift_velocity);
	b_lift(-127);
	wait1Msec(500);
	waitUntil(lift.velocity > -150);
	b_lift(0);

	// disable vertibar PID to begin reset
	stopTask(nb_vbar_PID_task);

	// for first cone wait extra since it's unstable
	if (autostack_state.maxHeight <= 1500) {
		wait1Msec(350);
	}
	// open claw
	b_cone_intake(127);
	if (SensorValue[ClawPot] > 240 && SensorValue[ClawPot] < 280) {
		wait1Msec(250);
	} else {
		waitUntil(SensorValue[ClawPot] < 1100);
	}

	wait1Msec(100);
	b_cone_intake(0);

	// flag stacked as true
	autostack_state.stacked = true;
}

task fieldReset() {
	// bring the vertibar to an intermediary angle
	int resetHeight = 2400;
	nb_vbar_PID(resetHeight, 127, 125000);

	// reset lift all the way
	waitUntil(SensorValue[TopLiftPot] < resetHeight + 100);
	nb_lift(1330, 127, 5000);

	autostack_state.stacked = false;
}

task matchReset() {
		// bring the vertibar to an intermediary angle
	int resetHeight = 550;
	nb_vbar(resetHeight, 127, 5000);

	// reset lift all the way
	waitUntil(SensorValue[TopLiftPot] < resetHeight + 1600);
	nb_lift(1670, 127, 5000);

	autostack_state.stacked = false;
}

void abortAutostack() {
	stopTask(autostackUp);
	stopTask(matchReset);
	stopTask(fieldReset);
	stopTask(nb_lift_PID_task);
	stopTask(nb_lift_task);
	stopTask(nb_vbar_task);
	stopTask(nb_vbar_PID_task);
	stopTask(nb_cone_intake_task);

	b_lift(0);
	b_vbar(0);
	b_cone_intake(0);
}

bool FIELD = true;
bool MATCH = false;

void autostack(int conesOnMogo, bool reset) {
	// set height to stack cone
	switch(conesOnMogo) {
		case 0:
			autostack_state.maxHeight = 1520; // works 1/13
			autostack_state.vbarHeight = 2840;
			break;
		case 1:
			autostack_state.maxHeight = 1570; // works 1/13
			autostack_state.vbarHeight = 2840;
			break;
		case 2:
			autostack_state.maxHeight = 1650; // works 1/13
			autostack_state.vbarHeight = 2840;
			break;
		case 3:
			autostack_state.maxHeight = 1700; // works 1/13
			autostack_state.vbarHeight = 2800;
			break;
		case 4:
			autostack_state.maxHeight = 1820; // works 1/13
			autostack_state.vbarHeight = 2800;
			break;
		case 5:
			autostack_state.maxHeight = 1875; // works 1/13
			autostack_state.vbarHeight = 2800;
			break;
		case 6:
			autostack_state.maxHeight = 1920; // works 1/13
			autostack_state.vbarHeight = 2800;
			break;
		case 7:
			autostack_state.maxHeight = 1970; // works 1/13
			autostack_state.vbarHeight = 2800;
			break;
		case 8:
			autostack_state.maxHeight = 2030; // works 1/14
			autostack_state.vbarHeight = 2600;
			break;
		case 9:
			autostack_state.maxHeight = 2250; // works 1/14
			autostack_state.vbarHeight = 2400;
			break;
		case 10:
			autostack_state.maxHeight = 2330; // works 1/15
			autostack_state.vbarHeight = 2400;
			break;
		case 11:
			autostack_state.maxHeight = 2450; // works 1/15
			autostack_state.vbarHeight = 2400;
			break;
		case 12:
			autostack_state.maxHeight = 2730; // works 1/15
			autostack_state.vbarHeight = 2400;
			break;
		case 13:
			autostack_state.maxHeight = 2880; // works 1/15
			autostack_state.vbarHeight = 2400;
			break;
		case 14:
			autostack_state.maxHeight = 2915; // working
			autostack_state.vbarHeight = 2400;
			break;

		default:
			autostack_state.maxHeight = 3140;
			autostack_state.vbarHeight = 2400;
	}

	startTask(autostackUp);
	waitUntil(autostack_state.stacked);
	abortAutostack();
	if (reset == FIELD) {
		startTask(fieldReset);
	} else {
		startTask(matchReset);
	}
	waitUntil(!autostack_state.stacked);
}
