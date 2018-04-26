/*
writes data to second LCD screen (read-only, buttons do not work)
@param line: the line of the string to be written to the LCD
@param s: the string to be written to the LCD
@return 1 if successful
*/
int writeSecondLCD(int line, string s) {
   unsigned char data[22];
    int i, cs;
    int len;

    // bounds check line variable
    if(( line < 0 ) || (line > 1))
        return(-1);

    // Header for LCD communication
    data[0] = 0xAA;
    data[1] = 0x55;
    data[2] = 0x1e;
    data[3] = 0x12;
    data[4] = 0x02 + line;

    // Clear transmit buffer
    for(i=0;i<16;i++)
        data[ 5+i ] = 0x20;


    // get string length
    len = strlen(s);
    if( len > 16 )
        len = 16;

    // copy string to transmit buffer
    memcpy( &(data[5]), s, len );

    // calculate checksum
    cs = 0;
    for(i=4;i<21;i++)
         cs = cs + data[i];

    data[21] = 0x100 - cs;

    // transmit
    for(i=0;i<22;i++)
        {
        // send char
        sendChar(uartOne, data[i]);

        // wait for transmission complete
        while( ! bXmitComplete(uartOne) )
             ; // should really have some sort of timeout here !
        }
    // success
    return(1);
}

int selectedAuton = 2;

#define MAIN true
#define SECOND false

void displayLCD(int LCD, int line, string text, bool centered) {
	if (LCD == MAIN && centered) {
		displayLCDCenteredString(line, text);
	} else if (LCD == MAIN && !centered) {
		displayLCDString(line, 0, text);
	} else {
		writeSecondLCD(line, text);
	}
}


task selector() {
	int NUM_AUTONS = 3;
	string autonNames[] = {"NO AUTON", "9PT MOGO", "26PT MOGO"};
  setBaudRate(uartOne, baudRate19200);
  wait1Msec(100);
	// uart1 right LCD
	// uart2 left LCD
  //int encoderValue = Sensor
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
		if (abs(selectedAuton) > NUM_AUTONS - 1) {
			selectedAuton = -sgn(selectedAuton) * (NUM_AUTONS - 1);
		}

		// display auton name
		if (abs(selectedAuton) >= 0 && abs(selectedAuton) <= NUM_AUTONS - 1) {
			displayLCDCenteredString(0, autonNames[abs(selectedAuton)]);
		} else {
			displayLCDCenteredString(0, "NO AUTON");
		}


		// display auton side
		if (sgn(selectedAuton) == 1) {
			displayLCDCenteredString(1, "RIGHT");
		} else if (sgn(selectedAuton) == -1) {
			displayLCDCenteredString(1, "LEFT");
		} else {
			displayLCDCenteredString(1, "N/A");
		}
	}
}
