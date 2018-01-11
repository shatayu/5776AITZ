#pragma config(Sensor, in1,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    TopLiftPot,     sensorPotentiometer)
#pragma config(Sensor, in3,    ClawPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    MainLiftPot,    sensorPotentiometer)
#pragma config(Sensor, in5,    Gyro,           sensorGyro)
#pragma config(Sensor, in6,    LLine,          sensorLineFollower)
#pragma config(Sensor, in7,    CLine,          sensorLineFollower)
#pragma config(Sensor, in8,    RLine,          sensorLineFollower)
#pragma config(Sensor, dgtl1,  REncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  RUltrasonic,    sensorSONAR_cm)
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



#include "Vex_Competition_Includes.c"

int selectedAuton = 2;

task selector() {
	int NUM_AUTONS = 4;
	string autonNames[] = {"ONLY DEPLOY", "2PT STAGO", "24PT MOGO", "PSKILLS", "22PT MOGO"};

	while (!bIfiAutonomousMode) {
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
		if (abs(selectedAuton) > NUM_AUTONS) {
			selectedAuton = -sgn(selectedAuton) * NUM_AUTONS;
		}

		// display auton name
		displayLCDCenteredString(0, autonNames[abs(selectedAuton)]);

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
	startTask(selector);
	bl_calibrate_gyro();
	bStopTasksBetweenModes = true;
	bLCDBacklight = true;
}

int sign;
task autonomous() {
	autostack_state.maxHeight = 1900;
	startTask(autostackUp);
	waitUntil(autostack_state.stacked);
	startTask(fieldReset);
}

// drive code
int leftPower;
int rightPower;
task driveControl() {
	while (true) {
		// dead zone
		leftPower = (abs(vexRT[Ch3] + vexRT[Ch1]) > 20) ? vexRT[Ch3] + vexRT[Ch1] : 0;
		rightPower = (abs(vexRT[Ch3] - vexRT[Ch1]) > 20) ? vexRT[Ch3] - vexRT[Ch1] : 0;

		// apply power
		b_drive(leftPower, rightPower);
		wait1Msec(20);
	}
}
/*
task autostackControl() {
	while (true) {
		if (vexRT[Btn8L] || vexRT[Btn8LXmtr2])
			abortAutostack();

		if (vexRT[Btn8RXmtr2]) {
			startTask(matchReset);
			waitUntil(SensorValue[MainLiftPot] < 1500);
			abortAutostack();
		}

		if (SensorValue[MainLiftPot] < 1350) {
			autostack_state.stacked = false;
		}
		wait1Msec(20);
	}
}
*/

int conesOnMogo = 0;

task usercontrol() {
	startTask(selector);
	// initialize drive code for drive
	startTask(driveControl);

	// initialize autostack stopping code
	//startTask(autostackControl);

	int clawStall = 15;
	while (true) {
		// LCD code
		//displayLCDNumber(0, 8, conesOnMogo);

		// main lift code
		if (vexRT[Btn7U]) {
			stopTask(nb_lift_PID_task);
			b_lift(127);
		} else if (vexRT[Btn7D]) {
			stopTask(nb_lift_PID_task);
			b_lift(-127);
		} else {
			int mainLiftPower = (abs(vexRT[Ch3Xmtr2]) > 10) ? vexRT[Ch3Xmtr2] : 0;
			if (mainLiftPower != 0)
				stopTask(nb_lift_PID_task);
			b_lift(mainLiftPower);
		}
		/*
		// top lift code
		if (vexRT[Btn8U]) {
			stopTask(nb_vbar_PID_task);
			b_vbar(127);
		} else if (vexRT[Btn8D]) {
			stopTask(nb_vbar_PID_task);
			b_vbar(-127);
		} else {
			int topLiftPower = (abs(vexRT[Ch2Xmtr2]) > 10) ? vexRT[Ch2Xmtr2] : 0;
			if (topLiftPower != 0) {
				stopTask(nb_vbar_PID_task);
			}
			b_vbar(topLiftPower);
		}

		*/

		//vbar PID test code
		if (vexRT[Btn8R]) {
			nb_vbar_PID(1080, 127, 15000);
			wait1Msec(150);
		} else if(vexRT[Btn8L]) {
			stopTask(nb_vbar_PID_task);
			b_vbar(0);
		}

		// mogo intake code
		if ((vexRT[Btn5U] || vexRT[Btn7UXmtr2]) && SensorValue[MogoPot] < 2690) {
			b_mogo_intake(127); // withdraw mogo intake
		} else if ((vexRT[Btn5D] || vexRT[Btn7DXmtr2]) && SensorValue[MogoPot] > 750) {
			b_mogo_intake(-127); // extend mogo intake
		} else {
			b_mogo_intake(0);
		}


		// cone intake (claw) code
		if (vexRT[Btn6U] && vexRT[Btn6D]) {
			b_cone_intake(15); // stall torque
			} else if (vexRT[Btn6U] || vexRT[Btn6UXmtr2]) {
			b_cone_intake(70); // close cone intake
			} else if (vexRT[Btn6D] || vexRT[Btn6DXmtr2]) {
			b_cone_intake(-70); // open cone intake
			} else {
			b_cone_intake(0); // stall cone intake in the right direction
		}

		/*

		// autostack
		if (vexRT[Btn8R] || vexRT[Btn8R]) {
			autostack(conesOnMogo, FIELD);
			conesOnMogo++;
		}

		// counter control
		if ((vexRT[Btn7L] || vexRT[Btn7LXmtr2]) && conesOnMogo > 0) {
			waitUntil(!vexRT[Btn7L] || vexRT[Btn7LXmtr2]);
			conesOnMogo--;
		} else if (vexRT[Btn7R] || vexRT[Btn7RXmtr2]) {
			waitUntil(!(vexRT[Btn7R] || vexRT[Btn7RXmtr2]));
			conesOnMogo++;
		}

		/*
		PARTNER STICK EXTRAS


		if (vexRT[Btn8UXmtr2]) {
			autostack(conesOnMogo, MATCH);
			conesOnMogo++;
		}

		if (vexRT[Btn8DXmtr2]) {
			conesOnMogo = 0;
		}

		if (vexRT[Btn8LXmtr2]) {
			abortAutostack();
		}
		*/


		wait1Msec(20);
	}
}
