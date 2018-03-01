#pragma config(Sensor, in1,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    TopLiftPot,     sensorPotentiometer)
#pragma config(Sensor, in3,    ClawPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    MainLiftPot,    sensorPotentiometer)
#pragma config(Sensor, in5,    Gyro,           sensorGyro)
#pragma config(Sensor, in6,    LLine,          sensorLineFollower)
#pragma config(Sensor, in7,    CLine,          sensorPotentiometer)
#pragma config(Sensor, in8,    RLine,          sensorLineFollower)
#pragma config(Sensor, dgtl1,  REncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  RUltrasonic,    sensorSONAR_cm)
#pragma config(Sensor, dgtl11, LUltrasonic,    sensorSONAR_cm)
#pragma config(Motor,  port2,           LDrive,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LMainLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           ConeIntake,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LMogoIntake,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           RMogoIntake,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           TopLift,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RMainLift,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RDrive,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
purple zipties := right side
green zipties := left side
pink zipties := other
*/

#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

int testLiftHeight = 0;
int testDistance = 80;

#include "programs/autostack.h"
#include "PID/PID.h"
#include "basic/b_functions.h"
#include "auton/blocking/bl_drive.h"
#include "auton/nonblocking/settings.h"
#include "auton/nonblocking/nb_lift.h"
#include "auton/nonblocking/nb_vbar.h"
#include "auton/nonblocking/nb_intake.h"

#include "PID/PID.c"
#include "basic/b_functions.c"
#include "auton/blocking/bl_drive.c"
#include "auton/blocking/bl_sensors.c"
#include "auton/nonblocking/nb_lift.c"
#include "auton/nonblocking/nb_vbar.c"
#include "auton/nonblocking/nb_intake.c"
#include "programs/autostack.c"

#include "autonomous_programs/scoreOn20.c"
#include "autonomous_programs/auton28.c"
#include "autonomous_programs/auton9.c"
#include "autonomous_programs/auton2.c"

#include "Vex_Competition_Includes.c"

int selectedAuton = 2;

task selector() {
	int NUM_AUTONS = 4;
	string autonNames[] = {"ONLY DEPLOY", "2PT STAGO", "24PT MOGO", "9PT MOGO"};

	while (true) {
		// change autons by using buttons; left and right cycle through autons, center inverts direction
		if (nLCDButtons == 1) {
			waitUntil(nLCDButtons == 0);
			selectedAuton--;
		} else if (nLCDButtons == 2) {
			waitUntil(nLCDButtons == 0);
			selectedAuton *= -1;
		} else if (nLCDButtons == 4) {
			waitUntil(nLCDButtons == 0);
			selectedAuton++;
		}

		// loop over to the other end of the list if no more autons to go through
		if (abs(selectedAuton) > NUM_AUTONS)
			selectedAuton = -sgn(selectedAuton) * NUM_AUTONS;


		// display auton name
		//displayLCDCenteredString(0, autonNames[abs(selectedAuton)]);
	if (abs(selectedAuton) == 1) {
		displayLCDCenteredString(0, autonNames[1]);
	} else if (abs(selectedAuton) == 2) {
		displayLCDCenteredString(0, autonNames[2]);
	} else if (abs(selectedAuton) == 3) {
		displayLCDCenteredString(0, autonNames[3]);
	} else {
		displayLCDCenteredString(0, "NO AUTON SELECTED");
	}

		// display auton side
		if (sgn(selectedAuton) == 1) {
			displayLCDCenteredString(1, "RIGHT");
			} else if (sgn(selectedAuton) == -1) {
			displayLCDCenteredString(1, "LEFT");
			} else {
			displayLCDCenteredString(1, "N/A");
		}

		wait1Msec(20);
	}
}

void pre_auton() {
	clearDebugStream();
	startTask(selector);
	bl_calibrate_gyro();
	bStopTasksBetweenModes = true;
	bLCDBacklight = true;
}

task timerLCD() {
	for (int i = 0; i < 125000; i += 50) {
		writeDebugStreamLine("%d", i);
		wait1Msec(50);
	}
}

task autonomous() {
	//if (abs(selectedAuton) == 1) {
	//	auton2(sgn(selectedAuton));
	//} else if (abs(selectedAuton) == 2) {
	//	auton28(sgn(selectedAuton));
	//} else if (abs(selectedAuton) == 3) {
	//	auton9(sgn(selectedAuton));
	//}
	//autostack(0, FIELD);
	startTask(timerLCD);
	auton28(1);
	stopTask(timerLCD);
}

int clawState = 0;
task subsystemControl() {
	while (true) {
		if (vexRT[Btn5U] && vexRT[Btn5D]) {
			b_lift(0); // remove any stall torque downward
		} else if (vexRT[Btn5U]) {
			stopTask(nb_lift_PID_task);
			b_lift(127); // raise lift
			waitUntil(!vexRT[Btn5U]);
			b_lift(0);
		} else if (vexRT[Btn5D]) {
			stopTask(nb_lift_PID_task);
			b_lift(-127); // lower lift
			waitUntil(!vexRT[Btn5D]);
			b_lift(-10); // keep lift down (lift is so light that without pressure it will rise due to contact)
		}

		// vertibar code
		if (vexRT[Btn6U]) {
			waitUntil(!vexRT[Btn6U]);
			if (SensorValue[TopLiftPot] > 1900) {
				stopTask(nb_vbar_PID_task);
				nb_vbar(1450, 127, 5000);
			} else {
				stopTask(nb_vbar_PID_task);
				nb_vbar(2800, 127, 5000);
			}
		}

		// cone intake (claw) code
		b_cone_intake(rollerState * 127);
		if (vexRT[Btn8U]) {
			rollerState = -1;
		} else if (vexRT[Btn6D]) {
			waitUntil(!vexRT[Btn6D]);
			rollerState = rollerState == 1 ? 0 : 1;
		}

			// mogo intake code (update values accordingly)
		if (vexRT[Btn7U] && SensorValue[MogoPot] < 2800) { // replace 2690 with current max
			b_mogo_intake(127); // withdraw mogo intake
		} else if (vexRT[Btn7D] && SensorValue[MogoPot] > 500) { // replace 750 with current min
			b_mogo_intake(-127); // extend mogo intake
		} else {
			b_mogo_intake(0);
		}

		wait1Msec(20);
	}
}

int conesOnMogo = 0;

bool getStackTrigger() {
	int threshold = 2220; // tuned
	return SensorValue[ClawPot] > threshold && !autostack_state.stacked; // false := don't stack, true := do stack
}

task autostackControl() {
	while (true) {
		if (/*vexRT[Btn8R]*/ getStackTrigger()) {
			abortAutostack();
			stopTask(subsystemControl);
			autostack(conesOnMogo, FIELD);
			startTask(subsystemControl);
			conesOnMogo++;
			clawState = OPEN;
		} else if (vexRT[Btn8D]) {
			stopTask(nb_vbar_PID_task);
			stopTask(subsystemControl);
			autostack(conesOnMogo, MATCH);
			startTask(subsystemControl);
			conesOnMogo++;
		} else if (vexRT[Btn7L]) {
			waitUntil(!vexRT[Btn7L]);
			if (conesOnMogo > 0)
				conesOnMogo--;
		} else if (vexRT[Btn7R]) {
			waitUntil(!vexRT[Btn7R]);
			if (conesOnMogo < 16)
				conesOnMogo++;
		} else if (vexRT[Btn8UXmtr2]){
			conesOnMogo = 0;
		}

		wait1Msec(20);
	}
}

task usercontrol() {
	startTask(selector);

	// initialize code for lift, vbar, mogo, cone intake
	startTask(subsystemControl);

	// initialize autostack code
	startTask(autostackControl);

	while (true) {
		// drive code

		// dead zone
		int leftPower = (abs(vexRT[Ch3] + vexRT[Ch1]) > 20) ? vexRT[Ch3] - vexRT[Ch1] : 0;
		int rightPower = (abs(vexRT[Ch3] - vexRT[Ch1]) > 20) ? vexRT[Ch3] + vexRT[Ch1] : 0;

		// apply power
		b_drive(leftPower, rightPower);

		// abort autostack
		if (vexRT[Btn8L]) {
			abortAutostack();
			autostack_state.stacked = false;
			startTask(subsystemControl);
			startTask(autostackControl);
		}

		wait1Msec(20);
	}
}
