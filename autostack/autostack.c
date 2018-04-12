// main autostack logic
int rollerState = 1; // 0 := still, 1 := intaking, -1 != outtaking
task autostackUp() {
	stopTask(nb_lift_PID_task);
	//// debug code
	//autostack_state.maxHeight = testLiftHeight; // debug code
	//autostack_state.vbarHeight = testVbarHeight;
	//autostack_state.dropTime = testDropTime;
	autostack_state.offsetUp = testOffsetUp;

	stopTask(nb_lift_PID_task);
	autostack_state.stacked = false;

	// stall torque to grip cone with
	b_cone_intake(20);

	nb_lift(autostack_state.maxHeight, 127, 15000);
	waitUntil(SensorValue[MainLiftPot] > autostack_state.maxHeight - autostack_state.offsetUp);
	nb_vbar(autostack_state.vbarHeight, 127, 2000);

	waitUntil(SensorValue[TopLiftPot] > autostack_state.vbarHeight);
	stopTask(nb_lift_task);
	b_lift(-127);
	wait1Msec(autostack_state.dropTime);
	b_cone_intake(-127);
	wait1Msec(100);
	// flag stacked as true
	autostack_state.stacked = true;
}

task fieldReset() {
	b_lift(127);
	wait1Msec(100);
	b_lift(20)
	// bring the vertibar to an intermediary angle
	int resetVbarHeight = 1470;
	int resetLiftHeight = 1570;
	stopTask(nb_vbar_PID_task);

	//if (autostack_state.maxHeight > 2300) {
	//	nb_vbar(resetVbarHeight, 127, 125000);
	//} else {
	//	nb_vbar(resetVbarHeight, 127, 125000);
	//}
	b_vbar(-127);

	// reset lift all the way
	int offset = 1200;
	waitUntil(SensorValue[TopLiftPot] < resetVbarHeight + testOffset && SensorValue[TopLiftPot] > 280);
	writeDebugStreamLine("middle vbar height: %d", SensorValue[TopLiftPot]);

	// bring lift to reset height
	nb_lift_PID(resetLiftHeight, 127, 125000);

	// bring vertibar down all the way
	stopTask(nb_vbar_PID_task);
	//nb_vbar(resetVbarHeight, 127, 125000);

	// finish up
	b_cone_intake(127);
	waitUntil(SensorValue[MainLiftPot] < resetLiftHeight + 200);
	writeDebugStreamLine("final vbar height: %d", SensorValue[TopLiftPot]);
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
	// upTime = 100ms
	// dropTime = 150ms
	int firstHeight = 1580;
	int heights[14] = {firstHeight, firstHeight + 55, firstHeight + 125, firstHeight + 235, // 0-11 tuned
										 firstHeight + 325, firstHeight + 415, firstHeight + 515, firstHeight + 605,
									 	 firstHeight + 795, firstHeight + 895, firstHeight + 1035, firstHeight + 1275,
									 	 firstHeight + 1815, 3140};

	int firstVbarHeight = 3900;
	int vbarHeights[14] = {firstVbarHeight, firstVbarHeight, firstVbarHeight, firstVbarHeight,
												 firstVbarHeight, firstVbarHeight, firstVbarHeight, firstVbarHeight,
											 	 firstVbarHeight, firstVbarHeight, firstVbarHeight, firstVbarHeight,
											 	 firstVbarHeight, firstVbarHeight};

	int firstDropTime = 110;
	int dropTimes[14] = {firstDropTime, firstDropTime, firstDropTime, firstDropTime,
											 firstDropTime, firstDropTime, firstDropTime, firstDropTime,
											 firstDropTime, firstDropTime, firstDropTime, firstDropTime,
											 firstDropTime, firstDropTime};

	int firstOffsetUp = 250;
	int offsets[14] = {firstOffsetUp, firstOffsetUp, firstOffsetUp, firstOffsetUp,
										 firstOffsetUp, firstOffsetUp, firstOffsetUp, firstOffsetUp,
										 firstOffsetUp, firstOffsetUp, firstOffsetUp, firstOffsetUp,
										 firstOffsetUp, firstOffsetUp};

	autostack_state.maxHeight = heights[conesOnMogo];
	autostack_state.vbarHeight = vbarHeights[conesOnMogo];
	autostack_state.dropTime = dropTimes[conesOnMogo];
	autostack_state.offsetUp = offsets[conesOnMogo];
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
