#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, in1,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    TopLiftPot,     sensorPotentiometer)
#pragma config(Sensor, in3,    ClawPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    MainLiftPot,    sensorPotentiometer)
#pragma config(Sensor, in5,    Gyro,           sensorGyro)
#pragma config(Sensor, in6,    LLine,          sensorLineFollower)
#pragma config(Sensor, in7,    CLine,          sensorPotentiometer)
#pragma config(Sensor, in8,    PEX,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  LEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  REncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  stackTrigger,   sensorTouch)
#pragma config(Sensor, dgtl6,  meme,           sensorTouch)
#pragma config(Sensor, dgtl7,  MogoDetector,   sensorSONAR_cm)
#pragma config(Sensor, dgtl9,  RUltrasonic,    sensorSONAR_cm)
#pragma config(Sensor, dgtl11, LUltrasonic,    sensorSONAR_cm)
#pragma config(Motor,  port1,           MogoIntake,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           RDrive,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RMainLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           MRDrive,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           ConeIntake,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           MLDrive,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           TopLift,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LMainLift,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           LDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

int distance1 = 610;
int distance2 = 120;
int distance3 = 120;
int distance4 = 170;

int testLiftHeight = 2420;
int testVbarHeight = 3650;
int testDropTime = 150;
int testUptime = 100;
int testDistance = 80;
int testOffset = 1600;

int conesOnMogo = 0;

task subsystemControl();

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

#include "auton/scoreOn20.c"
#include "auton/mogoAndCones.c"
#include "auton/mogoAuton.c"
#include "auton/auton13.c"
#include "auton/auton9.c"
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
//void drivetesteroo() {
//	b_drive(127,127);
//	int startTime = nSysTime;
//	int lastEncoder = sget_encoder();
//	wait1Msec(20);
//	while((nSysTime - startTime) < 2000) {

//		datalogDataGroupStart();
//		datalogAddValue(0,sget_encoder()-lastEncoder);
//		datalogDataGroupEnd();
//		lastEncoder=sget_encoder();
//		wait1Msec(40);
//	}
//}
task autonomous() {
	//autostack(6, FIELD);
	//nb_lift_PID(400, 127, 5000);
	mogoAuton(LEFT);
	//auton9(1);
	//nb_lift_PID(200,0,10000)
//while (SensorValue[MainLiftPot] < 2400) {
//	b_lift(60);
//	writeDebugStreamLine("%d", SensorValue[MainLiftPot]);
//	wait1Msec(30);
//}
//b_lift(0);
//nb_vbar_PID(3300, 127, 5000);
//mogoAndCones26(true);
//waitUntil(SensorValue[MogoDetector] < 7);
//b_drive(-127, -127);
//bl_drive(300, 127, 4000);
//bl_drive_rotate(900, 127, 2000);
}

task subsystemControl() {
	while (true) {
		// lift drive code
		if (vexRT[Btn5U] && vexRT[Btn5D]) {
			b_lift(0); // remove any stall torque downward
		} else if (vexRT[Btn5D]) {
			stopTask(nb_lift_PID_task);
			b_lift(-127); // lower lift
			waitUntil(!vexRT[Btn5D]);
			b_lift(-10); // keep lift down (lift is so light that without pressure it will rise due to contact)
		} else if (vexRT[Btn5U] && sget_lift(SENSOR) < 1490) {
			stopTask(nb_lift_PID_task);
			b_lift(127); // raise lift
			waitUntil(!vexRT[Btn5U]);
			b_lift(0);
		}

		// vertibar code
		if (vexRT[Btn6U]) {
			waitUntil(!vexRT[Btn6U]);
			writeDebugStreamLine("button pressed");
			if (SensorValue[TopLiftPot] > 2400) {
				stopTask(nb_vbar_PID_task);
				nb_vbar(2050, 127, 5000);
				if (sget_vbar(SENSOR) < 1870) {
					b_vbar(-10);
				}
			} else {
				stopTask(nb_vbar_PID_task);
				nb_vbar(3400, 127, 5000);
				if (sget_vbar(SENSOR) > 3400) {
				  b_vbar(10);
				}
			}
		}

		// cone intake (claw) code
		if (vexRT[Btn6D]) {
			b_cone_intake(127);
		} else if (vexRT[Btn8U]) {
			b_cone_intake(-127);
		} else if (vexRT[Btn8D]) {
			b_cone_intake(0);
		}

		// mogo intake code (update values accordingly)
		if (vexRT[Btn7U]) { // replace 2690 with current max
			b_mogo_intake(127); // withdraw mogo intake
		} else if (vexRT[Btn7D]) { // replace 750 with current min
			b_mogo_intake(-127); // extend mogo intake
		} else {
			b_mogo_intake(0);
		}

		// partner stick controls to adjust lift heights
		if (vexRT[Btn7RXmtr2]) {
			waitUntil(!vexRT[Btn7RXmtr2]);
			nb_lift_PID(300, 127, 125000);
			autostack_state.type = FIELD;
			b_cone_intake(127);
		} else if (vexRT[Btn7DXmtr2]) {
			waitUntil(!vexRT[Btn7DXmtr2]);
			nb_lift_PID(660, 12, 125000);
			autostack_state.type = MATCH;
			b_cone_intake(127);
		} else if (vexRT[Btn7LXmtr2]) {
			waitUntil(!vexRT[Btn7LXmtr2]);
			autostack_state.type = STAGO;
		}
		wait1Msec(20);
	}
}

task usercontrol() {
	startTask(selector);

	// initialize code for lift, vbar, mogo, cone intake
	startTask(subsystemControl);

	// initialize autostack code
	startTask(autostack_control);
	b_vbar(-10);
	while (true) {
		// drive code

		// dead zone
		int leftPower = abs(vexRT[Ch3]) > 25 ? vexRT[Ch3] : 0;
		int rightPower = abs(vexRT[Ch2]) > 25 ? vexRT[Ch2] : 0;

		// apply power
		b_drive(leftPower, rightPower);

		// abort autostack
		if (vexRT[Btn8L] || vexRT[Btn7UXmtr2]) {
			abortAutostack();
			autostack_state.stacked = false;
			startTask(subsystemControl);
			//startTask(autostackControl);
			b_cone_intake(0);
		}

		//datalogDataGroupStart();
		//datalogAddValue(0,SensorValue[MainLiftPot]);
		//datalogDataGroupEnd();

		wait1Msec(20);
	}
}
