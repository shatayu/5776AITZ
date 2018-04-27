
//cones on stago starts at the hieght of the same value as  6 cones on mogo autostack(6) hieght
//cones on stogo max is 5 cones so autostack(11)
task stago_up() {
	writeDebugStreamLine("stago up");
	autostack_state.stacked = 1;

	b_lift(127);
	wait1Msec(timesUp[autostack_state.mogo_cones]);
	b_lift(0);

	// stall torque to hold cone
	b_cone_intake(30);

	// bring vbar to correct heights
	autostack_state.vbar_height = 2100; // vbar angle to land on stago - needs tuning
	nb_vbar_PID(autostack_state.vbar_height, 127, 5000);
	waitUntil(autostack_state.vbar_height + 50 > sget_vbar(SENSOR));
	writeDebugStreamLine("vbar back for stago");

	// stago is ~6 cones tall
	autostack_state.lift_height = heights[autostack_state.stago_cones + 6];

	// lift to correct heights
	nb_lift(autostack_state.lift_height, 127, 5000);
	waitUntil(autostack_state.lift_height - 100 < sget_lift(SENSOR));
	writeDebugStreamLine("lifted down");

	stopTask(nb_lift_PID_task);
	b_cone_intake(-127);
	autostack_state.stacked = 2;
}

task stago_reset() {
	writeDebugStreamLine("stago resetting");
	if (autostack_state.mogo_cones < 8) {
		stopTask(nb_lift_PID_task);
		// start outtaking
		b_cone_intake(-127);

			// bring vbar to appropriate height
		stopTask(nb_vbar_PID_task);
		nb_vbar_PID(vbarHeights[autostack_state.mogo_cones], 127, 10000);
		waitUntil(sget_vbar(SENSOR) > vbarHeights[autostack_state.mogo_cones] - 50);
		writeDebugStreamLine("vbar back");

		// get lift up
		if (autostack_state.mogo_cones > 11) {
			autostack_state.mogo_cones = 11;
		}

		nb_lift_PID(heights[autostack_state.mogo_cones], 127, 10000);
		waitUntil(sget_lift(SENSOR) > heights[autostack_state.mogo_cones] + 50);
		writeDebugStreamLine("lift at right height for reset");

		autostack_state.stacked = 0;

		// start intaking again
		b_cone_intake(127);
	} else {
		writeDebugStreamLine("high cone reset");
		dropTimes[0] = firstDropTime + 50;
  	dropTimes[1] = firstDropTime + 50;
  	dropTimes[2] = firstDropTime;
  	heights[1] = firstHeight + 160;
  	heights[2] = firstHeight + 220;
  	offsetsUp[2] = firstOffsetUp;
  	offsetsUp[3] = firstOffsetUp;
  	offsetsUp[4] = firstOffsetUp;
  	offsetsUp[5] = firstOffsetUp;

		autostack_state.lift_height = heights[autostack_state.mogo_cones];
		autostack_state.vbar_height = vbarHeights[autostack_state.mogo_cones];
		autostack_state.drop = dropTimes[autostack_state.mogo_cones];
	  autostack_state.offset_up = offsetsUp[autostack_state.mogo_cones];
	  autostack_state.up = timesUp[autostack_state.mogo_cones];

	  	stopTask(nb_lift_PID_task);

		//// debug code - leave this here
		//autostack_state.lift_height = testLiftHeight - 1000; // debug code
		//autostack_state.vbar_height = testVbarHeight;
		//autostack_state.drop = testDropTime;

		autostack_state.stacked = 1;
		// stall torque to grip cone with
		b_cone_intake(30);
		//nb_vbar_PID(2000, 127, 15000);
		//waitUntil(sget_vbar(SENSOR) > 1750);
		writeDebugStreamLine("the height is %d", autostack_state.lift_height);

		// tell lift to go up until vbar can start rising with it, then have both go up
		nb_lift_PID(autostack_state.lift_height, 127, 15000);

		waitUntil(sget_lift(SENSOR) > autostack_state.lift_height - autostack_state.offset_up);
		writeDebugStreamLine("vbar moving back now");
		b_vbar(0);
		stopTask(nb_vbar_task);
		stopTask(nb_vbar_PID_task);
		if (autostack_state.mogo_cones < 7){
			nb_vbar(autostack_state.vbar_height, 127, 15000);
		} else {
			nb_vbar_PID(autostack_state.vbar_height, 127, 15000);
		}

		// come down once the vbar's all the way back
		waitUntil(sget_vbar(SENSOR) > autostack_state.vbar_height);
		b_vbar(20);
		stopTask(nb_lift_task);
		stopTask(nb_lift_PID_task);
		b_lift(-127);
		wait1Msec(autostack_state.drop);
		b_lift(0);
		// flag stacked as true
		autostack_state.stacked = 2;
	}
}
