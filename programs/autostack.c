// main autostack logic
int rollerState = 1; // 0 := still, 1 := intaking, -1 != outtaking
task autostackUp() {
	stopTask(nb_lift_PID_task);
	//autostack_state.maxHeight = testLiftHeight;
	int vbarHeight = 2550; // tuned
	if (autostack_state.maxHeight > 2650) // conesOnMogo >= 10
		vbarHeight = 2400;
	stopTask(nb_lift_PID_task);
	autostack_state.stacked = false;

	// stall torque to grip cone with
	b_cone_intake(30);

	// raise vertibar to height farthest away from robot
	int middleHeight = 1480;
	nb_vbar_PID(middleHeight, 127, 15000);
	waitUntil(SensorValue[TopLiftPot] > middleHeight - 650);
	writeDebugStreamLine("Vertibar reached the middle height");

	// begin raising lift to target height
	nb_lift(autostack_state.maxHeight, 127, 15000);

	waitUntil(SensorValue[MainLiftPot] > autostack_state.maxHeight - 100);
	writeDebugStreamLine("Lift reached target height");

	// once the lift is almost at the top, raise vertibar all the way (fully back) and keep it there
	stopTask(nb_vbar_PID_task);
	//if (autostack_state.maxHeight > 2400 && autostack_state.maxHeight != 3015) {
	//	nb_vbar_PID(vbarHeight, 127, 5000);
	//} else {
	//	nb_vbar(vbarHeight, 127, 5000);
	//}
	if (autostack_state.maxHeight > 2650) {
		nb_vbar_PID(vbarHeight, 127, 5000);
	} else {
		nb_vbar(vbarHeight, 127, 5000);
	}

	waitUntil(SensorValue[TopLiftPot] >= vbarHeight - 250);
	writeDebugStreamLine("Vertibar has came up all the way, lift currently at %d", SensorValue[MainLiftPot]);
	writeDebugStreamLine("Vertibar is at %d", SensorValue[TopLiftPot]);
	b_vbar(20);

	// once the lift is at the top come down on the stack
	b_lift(-127);
	wait1Msec(250);
	startTask(nb_lift_velocity);
	waitUntil(lift.velocity > -800);
	b_lift(0);
	writeDebugStreamLine("Lift is all the way down, currently at %d", SensorValue[MainLiftPot]);

	// disable vertibar PID to begin reset
	stopTask(nb_vbar_PID_task);

	// outtake rollers
	b_cone_intake(-127);

	// flag stacked as true
	autostack_state.stacked = true;
}

task fieldReset() {
	b_lift(127);
	wait1Msec(300);
	b_lift(0);
	// bring the vertibar to an intermediary angle
	int resetVbarHeight = 830;
	int resetLiftHeight = 1666;
	stopTask(nb_vbar_PID_task);
	nb_vbar(resetVbarHeight, 127, 125000);

	// reset lift all the way
	waitUntil(SensorValue[TopLiftPot] < resetVbarHeight + 200);

	// bring lift to reset height
	nb_lift_PID(resetLiftHeight, 127, 125000);

	// brake lift
	b_cone_intake(127);
	waitUntil(SensorValue[MainLiftPot] < resetLiftHeight + 200);
	autostack_state.stacked = false;
}
// change this
task matchReset() {
		b_cone_intake(40);
	// bring the vertibar to an intermediary angle
	int resetVbarHeight = 830;
	int resetLiftHeight = 1840;
	//nb_vbar(resetVbarHeight, 127, 125000);

	//// reset vertibar all the way
	//waitUntil(SensorValue[TopLiftPot] < resetVbarHeight + 200);

	//// bring lift to reset height

	////// brake lift

	if (SensorValue[MainLiftPot] > resetLiftHeight) {
		nb_lift(resetLiftHeight, 127, 125000);
		waitUntil(SensorValue[MainLiftPot] < resetLiftHeight + 400);
	} else {
		nb_lift_PID(resetLiftHeight, 127, 125000);
		waitUntil(SensorValue[MainLiftPot] > resetLiftHeight - 100);
	}
	nb_vbar(resetVbarHeight, 127, 125000);

	nb_cone_intake(OPEN);
	waitUntil(SensorValue[MainLiftPot] < resetLiftHeight + 200);
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
	rollerState = 0;
	b_cone_intake(0);
}

bool FIELD = true;
bool MATCH = false;

void autostack(int conesOnMogo, bool reset) {
	// set height to stack cone
	switch(conesOnMogo) {
		case 0:
			autostack_state.maxHeight = 1680; // works 2/2
			break;
		case 1:
			autostack_state.maxHeight = 1760; // works 2/2
			break;
		case 2:
			autostack_state.maxHeight = 1800; // works 2/2
			break;
		case 3:
			autostack_state.maxHeight = 1850; // works 2/2
			break;
		case 4:
			autostack_state.maxHeight = 1920; // works 2/2
			break;
		case 5:
			autostack_state.maxHeight = 1990; // works 2/2
			break;
		case 6:
			autostack_state.maxHeight = 2165; // works 2/2
			break;
		case 7:
			autostack_state.maxHeight = 2314; // works 2/2
			break;
		case 8:
			autostack_state.maxHeight = 2500; // works 2/2
			break;
		case 9:
			autostack_state.maxHeight = 2607; // works 1/15 vertibar went to far back
			break;
		case 10:
			autostack_state.maxHeight = 2700; // works 1/15
			break;
		case 11:
			autostack_state.maxHeight = 2930; // works 1/15
			break;
		case 12:
			autostack_state.maxHeight = 3015; // works 1/15
			break;
		/*case 13:
			autostack_state.maxHeight = 2915; // working
			break;
		case 13:
			autostack_state.maxHeight = 3055; // working
			break;*/

		default:
			autostack_state.maxHeight = 3140;
	}

	startTask(autostackUp);
	waitUntil(autostack_state.stacked);

	stopTask(nb_lift_PID_task);
	stopTask(nb_lift_task);
	stopTask(nb_vbar_task);
	stopTask(nb_vbar_PID_task);
	stopTask(nb_cone_intake_task);

//	b_cone_intake(0);
	if (autostack_state.maxHeight > 2650) {
		waitUntil(vexRT[Btn8R]);
	}// conesOnMogo >= 10

	if (reset == FIELD) {
		startTask(fieldReset);
	} else {
		startTask(matchReset);
	}
	waitUntil(!autostack_state.stacked);
	rollerState = 1;
}
