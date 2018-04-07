#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, in1,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    TopLiftPot,     sensorPotentiometer)
#pragma config(Sensor, in3,    ClawPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    MainLiftPot,    sensorPotentiometer)
#pragma config(Sensor, in5,    Gyro,           sensorGyro)
#pragma config(Sensor, in6,    LLine,          sensorLineFollower)
#pragma config(Sensor, in7,    CLine,          sensorPotentiometer)
#pragma config(Sensor, in8,    PEX,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  REncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  stackTrigger,   sensorTouch)
#pragma config(Sensor, dgtl7,  RUltrasonic,    sensorSONAR_cm)
#pragma config(Sensor, dgtl11, LUltrasonic,    sensorSONAR_cm)
#pragma config(Motor,  port2,           LDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LMainLift,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           ConeIntake,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           MDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           MogoIntake,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           TopLift,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           RMainLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           RDrive,        tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
purple zipties := right side
green zipties := left side
pink zipties := other
*/

#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

int testLiftHeight = 2660;
int testVbarHeight = 1850;
int testDropTime = 150;
int testUptime = 100;
int testDistance = 80;
int testOffset = 1600;

int conesOnMogo = 0;

#include "autostack/autostack.h"
#include "autostack/field.h"
#include "autostack/match.h"
#include "autostack/stago.h"

#include "PID/PID.h"
#include "basic/b_functions.h"

#include "functions/blocking/bl_drive.h"
#include "functions/nonblocking/settings.h"
#include "functions/nonblocking/nb_lift.h"
#include "functions/nonblocking/nb_vbar.h"
#include "functions/nonblocking/nb_intake.h"

#include "basic/b_sensors.h"
#include "basic/b_sensors.c"

#include "PID/PID.c"
#include "basic/b_functions.c"
#include "functions/blocking/bl_drive.c"
#include "functions/blocking/bl_sensors.c"
#include "functions/nonblocking/nb_lift.c"
#include "functions/nonblocking/nb_vbar.c"
#include "functions/nonblocking/nb_intake.c"

#include "autostack/autostack.c"
#include "autostack/field.c"
#include "autostack/match.c"
#include "autostack/stago.c"

//#include "auton/scoreOn20.c"
//#include "auton/mogoAndCones.c"
//#include "auton/mogoAuton.c"
//#include "auton/auton13.c"
//#include "auton/auton9.c"
//#include "auton/auton2.c"

#include "AutoSelectLCD.c"

#include "Vex_Competition_Includes.c"

void pre_auton() {
	clearDebugStream();
	startTask(selector);
	bl_calibrate_gyro();
	bStopTasksBetweenModes = true;
	bLCDBacklight = true;
}

task autonomous() {
	nb_vbar(2000, 127, 2000);

}

task subsystemControl() {
	while (true) {
		// lift drive code
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
		//if (vexRT[Btn6U]) {
		//	waitUntil(!vexRT[Btn6U]);
		//	if (SensorValue[TopLiftPot] > 900) {
		//		writeDebugStreamLine("vbar going down");
		//		stopTask(nb_vbar_PID_task);
		//		nb_vbar(170, 127, 5000);
		//	} else {
		//		stopTask(nb_vbar_PID_task);
		//		nb_vbar(1770, 127, 5000);
		//	}
		//}

		// cone intake (claw) code
		//b_cone_intake(rollerState * 127);
		//if (vexRT[Btn8U]) {
		//	rollerState = -1;
		//	} else if (vexRT[Btn6D]) {
		//	autoDetection = true;
		//	waitUntil(!vexRT[Btn6D]);
		//	rollerState = rollerState == 1 ? 0 : 1;
		//}

		// mogo intake code (update values accordingly)
		if (vexRT[Btn7U]) { // replace 2690 with current max
			b_mogo_intake(127); // withdraw mogo intake
		} else if (vexRT[Btn7D]) { // replace 750 with current min
			b_mogo_intake(-127); // extend mogo intake
		} else {
			b_mogo_intake(0);
		}
		// test
		wait1Msec(20);
	}
}

task usercontrol() {
	startTask(selector);

	// initialize code for lift, vbar, mogo, cone intake
	startTask(subsystemControl);

	// initialize autostack code
	// startTask(autostackControl);

	while (true) {
		// drive code

		// dead zone
		int leftPower = vexRT[Ch3];
		int rightPower = vexRT[Ch2];

		// apply power
		b_drive(leftPower, rightPower);

		// abort autostack
		if (vexRT[Btn8L]) {
			abortAutostack();
			autostack_state.stacked = false;
			startTask(subsystemControl);
			//startTask(autostackControl);
			b_cone_intake(0);
		}

		wait1Msec(20);
	}
}
