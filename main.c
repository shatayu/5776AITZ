#pragma config(Sensor, in1,    ConePot,        sensorPotentiometer)
#pragma config(Sensor, in2,    MogoPot,        sensorPotentiometer)
#pragma config(Sensor, in3,    LiftPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    FourBarPot,     sensorPotentiometer)
#pragma config(Sensor, in5,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  LEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  REncoder,       sensorQuadEncoder)
#pragma config(Motor,  port2,           LDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LMainLift,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           ConeIntake,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LMogoIntake,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RMogoIntake,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           TopLift,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RMainLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           RDrive,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

#include "motor.h"
#include "functions.h"
#include "stall.h"
#include "autons.h"
#include "Vex_Competition_Includes.c"

void pre_auton() {
  bStopTasksBetweenModes = true;
}

task autonomous() {

}

task usercontrol() {
  while (true) {

  	// drive code
  	moveDrive(vexRT[Ch3] - vexRT[Ch1], vexRT[Ch3] + vexRT[Ch1]);

  	// top lift (4-bar) code
  	if (vexRT[Btn6U]) {
  		moveTopLift(127);
  	} else if (vexRT[Btn6D]) {
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

  	// mogo intake code
  	if (vexRT[Btn7U]) {
  		moveMogoIntake(127);
  	} else if (vexRT[Btn7D]) {
  		moveMogoIntake(-127);
  	} else {
  		moveMogoIntake(0);
  	}

  	// cone intake code
  	if (vexRT[Btn8U]) {
  		moveConeIntake(127);
  	} else if (vexRT[Btn8D]) {
  		moveConeIntake(-127);
  	} else if (vexRT[Btn8L]) {
  		clawStall(true);
  	} else {
  		clawStall(false);
  	}

  	wait1Msec(20);
  }
}
