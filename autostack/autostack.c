// main autostack logic
int rollerState = 1; // 0 := still, 1 := intaking, -1 != outtaking
int vbarHeight;
task autostackUp() {
	stopTask(nb_lift_PID_task);
	//autostack_state.maxHeight = testLiftHeight;
	if (autostack_state.maxHeight == 3140) {
		vbarHeight = 3330;
	} else if (autostack_state.maxHeight > 2200 && autostack_state.maxHeight < 2400) { // conesOnMogo >= 10
		vbarHeight = 3330 - 150;
  } else {
		vbarHeight = 3330;
	}

	stopTask(nb_lift_PID_task);
	autostack_state.stacked = false;

	// stall torque to grip cone with
	b_cone_intake(20);

	// raise vertibar to height farthest away from robot
	int middleHeight = 1540;
	nb_vbar_PID(middleHeight, 127, 3000);
	waitUntil(SensorValue[TopLiftPot] > middleHeight - 550);

	// begin raising lift to target height
	nb_lift(autostack_state.maxHeight, 127, 15000);
	waitUntil(SensorValue[MainLiftPot] > autostack_state.maxHeight - 300);

	// once the lift is almost at the top, raise vertibar all the way (fully back) and keep it there
	stopTask(nb_vbar_PID_task);
	if (autostack_state.maxHeight > 2200) { // conesOnMogo >= 10
		nb_vbar_PID(vbarHeight, 127, 5000);
	} else {
		nb_vbar(vbarHeight, 127, 5000);
	}

	waitUntil(SensorValue[TopLiftPot] >= vbarHeight - 250);
	b_vbar(20);

	// once the lift is at the top come down on the stack
	b_lift(-127);
	wait1Msec(250);
	startTask(nb_lift_velocity);
	waitUntil(lift.velocity > -800);
	b_lift(0);

	// disable vertibar PID to begin reset
	stopTask(nb_vbar_PID_task);

	// outtake rollers
	b_cone_intake(-127);

	// flag stacked as true
	autostack_state.stacked = true;
}

task fieldReset() {
	b_lift(127);
	wait1Msec(200); // tune
	b_lift(0);
	// bring the vertibar to an intermediary angle
	int middleHeight = 1520;
	int resetVbarHeight = 900;
	int resetLiftHeight = 1666;
	stopTask(nb_vbar_PID_task);
	nb_vbar(resetVbarHeight, 127, 125000);

	// reset lift all the way
	waitUntil(SensorValue[TopLiftPot] < middleHeight + 200);

	// bring lift to reset height
	nb_lift_PID(resetLiftHeight, 127, 125000);

	// bring vertibar down all the way
	stopTask(nb_vbar_PID_task);
	nb_vbar(resetVbarHeight, 127, 125000);

	// brake lift
	b_cone_intake(127);
	waitUntil(SensorValue[MainLiftPot] < resetLiftHeight + 200);
	autostack_state.stacked = false;
}
// change this
task matchReset() {
	b_cone_intake(-127);
	// bring the vertibar to an intermediary angle
	int middleHeight = 1520;
	int resetVbarHeight = 900;
	int resetLiftHeight = 2100;

	// if lift is too low raise it first before bringing vertibar down so vertibar doesn't hit perimeter
	if (SensorValue[MainLiftPot] > resetLiftHeight) {
		nb_lift(resetLiftHeight, 127, 125000);
		waitUntil(SensorValue[MainLiftPot] < resetLiftHeight + 400);
	} else {
		nb_lift_PID(resetLiftHeight, 127, 125000);
		waitUntil(SensorValue[MainLiftPot] > resetLiftHeight - 100);
	}
	nb_vbar(resetVbarHeight, 127, 125000);

	waitUntil(SensorValue[MainLiftPot] < resetLiftHeight + 200);
	b_cone_intake(127);
	autostack_state.stacked = false;
}

void abortAutostack() {
	// set clawpot port to no sensor
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
	writeDebugStreamLine("%d", conesOnMogo);
	// set height to stack cone
	int heights[15];
	heights[0] = 1600;
	heights[1] = 1660; // tuned
	heights[2] = 1700; // tuned
	heights[3] = 1780; // tuned
	heights[4] = 1850; // tuned
	heights[5] = 1900; // tuned
	heights[6] = 1960; // tuned
	heights[7] = 2020; // tuned
	heights[8] = 2090; // tuned
	heights[9] = 2180; // tuned
	heights[10] = 2260; // tuned
	heights[11] = 2420; // tuned
	heights[12] = 2600; // tuned
	heights[13] = 3140;
	heights[14] = 3140;


	autostack_state.maxHeight = heights[conesOnMogo];
	writeDebugStreamLine("%d", autostack_state.maxHeight);

	startTask(autostackUp);
	waitUntil(autostack_state.stacked);

	stopTask(nb_lift_PID_task);
	stopTask(nb_lift_task);
	stopTask(nb_vbar_task);
	stopTask(nb_vbar_PID_task);
	stopTask(nb_cone_intake_task);

	if (reset == FIELD) {
		startTask(fieldReset);
	} else {
		startTask(matchReset);
	}
	waitUntil(!autostack_state.stacked);
	rollerState = 1;
}
