//// main autostack logic
////int rollerState = 1; // 0 := still, 1 := intaking, -1 != outtaking

void abortAutostack() {
	stopTask(nb_lift_PID_task);
	stopTask(nb_lift_task);
	stopTask(nb_vbar_task);
	stopTask(nb_vbar_PID_task);
	stopTask(nb_cone_intake_task);
	stopTask(field_up);
	stopTask(match_reset);
	stopTask(field_reset);
	stopTask(autostack_control);

	b_lift(0);
	b_vbar(0);
	b_cone_intake(0);

	startTask(autostack_control);
}

task autostack_control() {
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
			autostack_state.type = FIELD;
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
		if (vexRT[Btn7R]) {
			if (autostack_state.mogo_cones < 12) {
				waitUntil(!vexRT[Btn7R]);
				autostack_state.mogo_cones++;
			}
		} else if (vexRT[Btn7L]) {
			if (autostack_state.mogo_cones > 0) {
				waitUntil(!vexRT[Btn7L]);
				autostack_state.mogo_cones--;
			}
		}
		wait1Msec(20);
	}
}

void autostack(int cone, int reset) {
	// set height to stack cone
	int firstHeight = 180;
	int heights[14] = {firstHeight - 30, firstHeight + 25, firstHeight + 115, firstHeight + 225, // 0-11 tuned
										 firstHeight + 325, firstHeight + 415, firstHeight + 515, firstHeight + 605,
									 	 firstHeight + 795, firstHeight + 895, firstHeight + 1035, firstHeight + 1275,
									 	 firstHeight + 1815, 3140};

	int firstVbarHeight = 3750;
	int vbarHeights[14] = {firstVbarHeight, firstVbarHeight, firstVbarHeight, firstVbarHeight,
												 firstVbarHeight, firstVbarHeight, firstVbarHeight, firstVbarHeight,
											 	 firstVbarHeight, firstVbarHeight, firstVbarHeight, firstVbarHeight,
											 	 firstVbarHeight, firstVbarHeight};


	int firstDropTime = 200;

	int dropTimes[14] = {firstDropTime, firstDropTime, firstDropTime, firstDropTime,
											 firstDropTime, firstDropTime, firstDropTime, firstDropTime,
											 firstDropTime, firstDropTime, firstDropTime, firstDropTime,
											 firstDropTime, firstDropTime};

	autostack_state.lift_height = heights[cone];
	autostack_state.vbar_height = vbarHeights[cone];
	autostack_state.drop = dropTimes[cone];
  autostack_state.offset_up = 330;

	startTask(field_up);
	waitUntil(autostack_state.stacked == 2);

	stopTask(nb_lift_task);
	stopTask(nb_vbar_task);

	if (reset == FIELD) {
		startTask(field_reset);
	} else {
		startTask(match_reset);
	}

	waitUntil(!autostack_state.stacked);
}
