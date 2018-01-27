// main autostack logic
task autostackUp() {
	int vbarHeight = 2550; // tuned
	stopTask(nb_lift_PID_task);
	// open claw position = 1350
	autostack_state.stacked = false;

	// stall torque to grip cone with (change to -30 later, 0 for testing right now)
	b_cone_intake(-30);

	// raise vertibar to height farthest away from robot
	int middleHeight = 1480;
	nb_vbar_PID(middleHeight, 127, 15000);
	waitUntil(SensorValue[TopLiftPot] > middleHeight - 200);
	writeDebugStreamLine("Vertibar reached the middle height");

	// begin raising lift to target height
	nb_lift(autostack_state.maxHeight, 127, 15000);
	waitUntil(SensorValue[MainLiftPot] > autostack_state.maxHeight - 100);
	writeDebugStreamLine("Lift reached to target height");

	// once the lift is almost at the top, raise vertibar all the way (fully back) and keep it there
	stopTask(nb_vbar_PID_task);
	nb_vbar(vbarHeight, 127, 5000);
	waitUntil(SensorValue[TopLiftPot] >= vbarHeight);
	writeDebugStreamLine("Vertibar has came up all the way, lift currently at %d", SensorValue[MainLiftPot]);
	b_vbar(20);

	// once the lift is at the top come down on the stack
	b_lift(-127);
	wait1Msec(250);
	startTask(nb_lift_velocity);
	wait1Msec(250);
	waitUntil(lift.velocity > -500);
	b_lift(0);
	writeDebugStreamLine("Lift is all the way down, currently at %d", SensorValue[MainLiftPot]);

	// disable vertibar PID to begin reset
	stopTask(nb_vbar_PID_task);

	// for first cone wait extra since it's unstable
	if (autostack_state.maxHeight <= 1500) {
		wait1Msec(350);
	}

	// flag stacked as true
	autostack_state.stacked = true;
}

task fieldReset() {
	// bring the vertibar to an intermediary angle
	int resetVbarHeight = 830;
	int resetLiftHeight = 1450;
	nb_vbar(resetVbarHeight, 127, 125000);

	// reset lift all the way
	waitUntil(SensorValue[TopLiftPot] < resetVbarHeight + 200);

	// bring lift to reset height
	int height = SensorValue[MainLiftPot];

	//// brake lift
	nb_lift(resetLiftHeight, 127, 1250000);
	b_lift(-127);
	wait1Msec(300);
	b_lift(0);

	nb_cone_intake(OPEN);
	autostack_state.stacked = false;
}

task matchReset() {
		// bring the vertibar to an intermediary angle
	int resetHeight = 550;
	nb_vbar(resetHeight, 127, 5000);

	// reset lift all the way
	waitUntil(SensorValue[TopLiftPot] < resetHeight + 1600);
	nb_lift_PID(1670, 127, 5000);

	nb_cone_intake(OPEN);
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
			autostack_state.maxHeight = 1635; // works 1/26
			break;
		case 1:
			autostack_state.maxHeight = 1710; // works 1/26
			break;
		case 2:
			autostack_state.maxHeight = 1795; // works 1/26
			break;
		case 3:
			autostack_state.maxHeight = 1885; // works 1/26
			break;
		case 4:
			autostack_state.maxHeight = 1980; // works 1/26
			break;
		case 5:
			autostack_state.maxHeight = 2030; // works 1/13
			break;
		case 6:
			autostack_state.maxHeight = 2140; // works 1/13
			break;
		case 7:
			autostack_state.maxHeight = 2250; // works 1/13
			break;
		case 8:
			autostack_state.maxHeight = 2360; // works 1/14
			break;
		case 9:
			autostack_state.maxHeight = 2500; // works 1/14
			break;
		case 10:
			autostack_state.maxHeight = 2330; // works 1/15
			break;
		case 11:
			autostack_state.maxHeight = 2450; // works 1/15
			break;
		case 12:
			autostack_state.maxHeight = 2730; // works 1/15
			break;
		case 13:
			autostack_state.maxHeight = 2880; // works 1/15
			break;
		case 14:
			autostack_state.maxHeight = 2915; // working
			break;

		default:
			autostack_state.maxHeight = 3140;
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
