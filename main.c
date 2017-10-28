#pragma config(Sensor, in1,    MainLiftPot,    sensorPotentiometer)
#pragma config(Sensor, in2,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, in3,    TopLiftPot,     sensorPotentiometer)
#pragma config(Sensor, in5,    Gyro,           sensorGyro)
#pragma config(Sensor, in6,    ConePot,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  LEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  REncoder,       sensorQuadEncoder)
#pragma config(Motor,  port2,           LDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LMainLift,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           ConeIntake,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LMogoIntake,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           RMogoIntake,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           TopLift,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RMainLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           RDrive,        tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

#include "motor.h"
#include "stall.h"
#include "functions.h"
#include "liftFunctions.h"
#include "autostack.h"
#include "autons.h"

#include "Vex_Competition_Includes.c"

void pre_auton() {
	//calibrate();
  bStopTasksBetweenModes = true;
}

/*
-5532 775 = 6307
767 -5677 = 6444
-5069 -7892 = 2820
-6452 -4295 = -2157
*/

task autonomous() {
//
mogo20(1);

}

int conesOnMogo = 0;
task usercontrol() {
	bool stallOn;
  while (true) {
  	//displayLCDNumber(conesOnMogo);
  	// drive code
  	moveDrive(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);

  	// top lift (4-bar) code
  	if (vexRT[Btn8U]) {
  		stopTask(holdTopLift);
  		moveTopLift(127);
  	} else if (vexRT[Btn8D]) {
  		stopTask(holdTopLift);
  		moveTopLift(-127);
  	} else {
  		moveTopLift(0);
  	}

  	// main lift (RD4B) code
  	if (vexRT[Btn5U]) {
  		moveMainLift(127);
  	} else if (vexRT[Btn5D]) {
  		moveMainLift(-127);
  	} else {
  		moveMainLift(0);
  	}

  	// mogo intake code\

  	if (vexRT[Btn7U]) {
  		stopTask(holdMogo);
  		moveMogoIntake(-127);
  	} else if (vexRT[Btn7D]) {
  		stopTask(holdMogo);
  		moveMogoIntake(127);
  	} else {
  		moveMogoIntake(0);
  	}

  	// cone intake (claw) code
  	if (vexRT[Btn6U]) {
  		moveConeIntake(60);
  	} else if (vexRT[Btn6D]) {
  		moveConeIntake(-60);
  	} else if (vexRT[Btn8L]) {
  	} else {
  		clawStall(false);
  	}

  	if (vexRT[Btn7LXmtr2]) {
  		clawStall(true);
  	}

  	// autostack code
  	if (vexRT[Btn8R]) {
  		autoStack(conesOnMogo);
  		conesOnMogo++;
  		reset();
  		stopTask(holdMainLift);
  	} else if (vexRT[Btn7L] && conesOnMogo > 0) {
  		waitUntil(!vexRT[Btn7L]);
  		conesOnMogo--;
  	} else if (vexRT[Btn7R]) {
  		waitUntil(!vexRT[Btn7R]);
  		conesOnMogo++;
  	}

  	if (vexRT[Btn8UXmtr2]) {
  		startTask(holdMainLift);
  	} else if (vexRT[Btn8DXmtr2]) {
  		stopTask(holdMainLift);
  	}

  	if (vexRT[Btn8RXmtr2]) {
  		startTask(holdTopLift);
  	} else if (vexRT[Btn8LXmtr2]) {
  		stopTask(holdTopLift);
  	}

    if (vexRT[Btn7UXmtr2]) {
  		startTask(holdMogo);
  	} else if (vexRT[Btn7DXmtr2]) {
  		stopTask(holdMogo);
  	}

  	wait1Msec(20);
  }
}
