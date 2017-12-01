const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

typedef enum
{
  AutoMode_None = 0,
  AutoMode_Mogo = 1,
  AutoMode_Stationary = 2,
  AutoMode_Count
} AutoModes;
const int autoSelectTimeout = 60000;
string autoNames[AutoMode_Count] = {"NONE", "Mogo", "Stationary"};
int autoMode = 0;

void SelectAutonomous()
{
	//SelectingAutonomous = true;
	time1[T3]= 0;
	autoMode = 0;

	bLCDBacklight = true;
	// Display first entry by default
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDCenteredString(0, autoNames[0]);
	displayLCDCenteredString(1, "<     Enter    >");

	// Loop until the center button is pushed
	while ((nLCDButtons != centerButton) && (time1[T3] < autoSelectTimeout) && bIfiRobotDisabled)
	{
	  // If no buttons pushed keep waiting
	  if (nLCDButtons == 0)
	    wait1Msec(10);
	  else
	  {
	    // If left button pushed
	    if (nLCDButtons == leftButton)
	    {
	      // Show the previous autoMode, with wrap
	      if (autoMode > 0)
	        autoMode--;
	      else
	        autoMode = AutoMode_Count - 1;
	    }
	    // If right button pushed
	    else if(nLCDButtons == rightButton)
	    {
	      // Show the next autoMode, with wrap
	      if (autoMode < (int)(AutoMode_Count - 1))
	        autoMode++;
	      else
	        autoMode = 0;
	    }

	    //Update display
	    clearLCDLine(0);
	    displayLCDCenteredString(0, autoNames[autoMode]);

	    // Wait until the button is released before continuing
	    while ((nLCDButtons != 0) && (time1[T3] < autoSelectTimeout))
	      wait1Msec(10);
	  }
	}

	// If timed out, then select no autonomous
	if (time1[T3] >= autoSelectTimeout)
	  autoMode = 0;

 	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDCenteredString(0, autoNames[autoMode]);
	displayLCDCenteredString(1, "Selected!");
	wait1Msec(2000);
	//bLCDBacklight = false;
	//SelectingAutonomous = false;
}
