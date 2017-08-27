#pragma config(Motor,  port2,           FRDrive,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           CRDrive,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           BRDrive,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LLift,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           RLift,         tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           FLDrive,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           CLDrive,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           BLDrive,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

#include "motor.h"
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

  	// lift code
  	if (vexRT[Btn6U]) {
  		moveLift(127);
  	} else if (vexRT[Btn6D]) {
  		moveLift(-127);
  	} else {
  		moveLift(0);
  	}

  }
}
