void bl_drive_brake(int direction) {
	b_drive(-direction * 30, -direction * 30);
	wait1Msec(50);
	b_drive(0, 0);
}


void bl_drive(int target, int power, int timeout, bool brake) {
	//SensorValue[LEncoder] = 0;
	//SensorValue[REncoder] = 0;

	//int timer = 0;
	//b_drive(power, power);

	//while (abs(SensorValue[REncoder]) < target && timer < timeout) {
	//	wait1Msec(20);
	//	timer += 20;
	//}

	//bl_drive_brake(sgn(power));

	SensorValue[LEncoder] = 0;

	b_drive(power, power);
	clearTimer(T1);
	waitUntil(abs(SensorValue[LEncoder]) > target || time1[T1] > timeout);
	if (brake) {
		bl_drive_brake(sgn(power));
	}
}

void bl_drive_rotate_brake(int direction) {
	b_drive(-direction * BRAKE_POWER, direction * BRAKE_POWER);
	wait1Msec(BRAKE_TIME);
	b_drive(0, 0);
}

void bl_drive_rotate(int target, int power, int timeout) {
	int timer = 0;

	SensorValue[Gyro] = 0;

	while (target - abs(SensorValue[Gyro]) > 300 && timer < timeout) {
		b_drive(power, -power);
		wait1Msec(20);
		timer += 20;
	}

	while (target - abs(SensorValue[Gyro]) > 20 && timer < timeout) {
		b_drive(power * 0.4, -power * 0.4);
		wait1Msec(20);
		timer += 20;
	}

	bl_drive_rotate_brake(sgn(power));
}
