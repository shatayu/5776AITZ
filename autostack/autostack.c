//// main autostack logic
////int rollerState = 1; // 0 := still, 1 := intaking, -1 != outtaking

void abortAutostack() {
	stopTask(nb_lift_PID_task);
	stopTask(nb_lift_task);
	stopTask(nb_vbar_task);
	stopTask(nb_vbar_PID_task);
	stopTask(nb_cone_intake_task);
	stopTask(field_up);
	stopTask(match_up);
	stopTask(match_reset);
	stopTask(field_reset);
	stopTask(autostack_control);

	b_lift(0);
	b_vbar(0);
	b_cone_intake(0);

	startTask(autostack_control);
}

task autostack_control() {
	autostack_state.type = FIELD;
	while (true) {
		if (vexRT[Btn8R] || sget_trigger()) {
			if (vexRT[Btn8R]) {
				autostack_state.stacked = 0;
			}
			// let button get released
			waitUntil(!vexRT[Btn8R]);

			// disable potentially interfering systems
			stopTask(subsystemControl);
			//abortAutostack();

			// stack
			if (autostack_state.type != NONE) {
				autostack(autostack_state.mogo_cones, autostack_state.type);
			}

			startTask(subsystemControl);

			// increment the appropriate internal counts
			if (autostack_state.mogo_cones < 13 && (autostack_state.type == FIELD || autostack_state.type == MATCH)) {
				autostack_state.mogo_cones++;
			} else if (autostack_state.mogo_cones > 0 && autostack_state.type == STAGO) {
				autostack_state.mogo_cones--;
				autostack_state.stago_cones++;
			}
		}

		// manual control for incrementing

		// field cones
		if (vexRT[Btn6UXmtr2] && vexRT[Btn6DXmtr2]) {
			waitUntil(!(vexRT[Btn6UXmtr2] && vexRT[Btn6DXmtr2]));
			autostack_state.mogo_cones = 0;
		} else if (vexRT[Btn6UXmtr2]) {
			if (autostack_state.mogo_cones < 12) {
				waitUntil(!vexRT[Btn6UXmtr2]);
				autostack_state.mogo_cones++;
			}
		} else if (vexRT[Btn6DXmtr2]) {
			if (autostack_state.mogo_cones > 0) {
				waitUntil(!vexRT[Btn6DXmtr2]);
				autostack_state.mogo_cones--;
			}
		}

		// stago cones
		if (vexRT[Btn5UXmtr2] && vexRT[Btn5DXmtr2]) {
			waitUntil(!(vexRT[Btn5UXmtr2] && vexRT[Btn5DXmtr2]));
			autostack_state.stago_cones = 0;
		} else if (vexRT[Btn5UXmtr2]) {
			if (autostack_state.stago_cones < 12) {
				waitUntil(!vexRT[Btn5UXmtr2]);
				autostack_state.stago_cones++;
			}
		} else if (vexRT[Btn5DXmtr2]) {
			if (autostack_state.stago_cones > 0) {
				waitUntil(!vexRT[Btn5DXmtr2]);
				autostack_state.stago_cones--;
			}
		}

		// set types of stacks
		if (vexRT[Btn8RXmtr2]) {
			autostack_state.type = FIELD;
		} else if (vexRT[Btn8DXmtr2]) {
			autostack_state.type = MATCH;
		} else if (vexRT[Btn8LXmtr2]) {
			autostack_state.type = STAGO;
		}

		// go to reset heights
		if (vexRT[Btn7RXmtr2]) {
			stopTask(nb_lift_PID_task);
			nb_lift_PID(390, 127, 125000);
			autostack_state.type = FIELD;
		} else if (vexRT[Btn7DXmtr2]) {
			stopTask(nb_lift_PID_task);
			nb_lift_PID(800, 127, 125000);
			autostack_state.type = MATCH;
		} else if (vexRT[Btn7LXmtr2]) {
			autostack_state.type = STAGO;
		}
	}
}

// set height to stack cone (finalize arithmetic)
int firstHeight = 180;
int heights[12] = {firstHeight, firstHeight + 160, firstHeight + 220, firstHeight + 340, // 0-11 tuned
									 firstHeight + 470, firstHeight + 565, firstHeight + 715, firstHeight + 810,
								 	 firstHeight + 930, firstHeight + 1030, firstHeight + 1140, firstHeight + 1310};

int firstVbarHeight = 3450;
int vbarHeights[12] = {firstVbarHeight, firstVbarHeight, firstVbarHeight, firstVbarHeight,
											 firstVbarHeight - 200, firstVbarHeight - 200, firstVbarHeight - 200, firstVbarHeight - 300,
										 	 firstVbarHeight - 600, firstVbarHeight - 400, firstVbarHeight - 400, firstVbarHeight - 600};


int firstDropTime = 200;
int dropTimes[12] = {firstDropTime + 50, firstDropTime + 50, firstDropTime, firstDropTime,
										 firstDropTime, firstDropTime, firstDropTime, firstDropTime,
										 firstDropTime, firstDropTime, firstDropTime, firstDropTime};

int firstOffsetUp = 350;
int offsetsUp[12] = {firstOffsetUp, firstOffsetUp - 30, firstOffsetUp, firstOffsetUp,
										 firstOffsetUp, firstOffsetUp, firstOffsetUp - 100, firstOffsetUp,
										 firstOffsetUp, firstOffsetUp - 100, firstOffsetUp, firstOffsetUp};

void autostack(int cone, int reset, bool blocking) {
	autostack_state.lift_height = heights[cone];
	autostack_state.vbar_height = vbarHeights[cone];
	autostack_state.drop = dropTimes[cone];
  autostack_state.offset_up = offsetsUp[cone];

  if (autostack_state.type == FIELD) {
  	startTask(field_up);
  } else if (autostack_state.type == MATCH) {
  	dropTimes[0] -= 100;
  	dropTimes[1] -= 50;
  	dropTimes[2] += 50;
  	heights[4] += 50;
		heights[5] += 150;
		heights[6] += 150;
		heights[7] += 120;
		heights[8] += 150;

		autostack_state.lift_height = heights[cone];
		autostack_state.vbar_height = vbarHeights[cone];
		autostack_state.drop = dropTimes[cone];
		autostack_state.offset_up = offsetsUp[cone];
  	startTask(match_up);
	} else if (autostack_state.type == STAGO) {
		startTask(stago_up);
	}

	waitUntil(autostack_state.stacked == 2);

	stopTask(nb_lift_task);
	stopTask(nb_vbar_task);
	writeDebugStreamLine("%d", autostack_state.lift_height);
	writeDebugStreamLine("%d", autostack_state.offset_up);

	if (autostack_state.mogo_cones < 11) {
		if (autostack_state.type == FIELD) {
			startTask(field_reset);
		} else if (autostack_state.type == MATCH) {
			startTask(match_reset);
		} else if (autostack_state.type == STAGO) {
			startTask(stago_reset);
		}
	} else {
		b_lift(127);
		wait1Msec(200);
		b_lift(0);
		b_cone_intake(0);
		abortAutostack();
	}

	if (blocking) {
		waitUntil(!autostack_state.stacked);
	}
}
