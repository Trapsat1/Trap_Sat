	/*
	  Author: Zach Richard
	  Date: 05/19/2014
	  Project: Trap Sat: Capitol College

	  This library will be used to take and store pictures using the Arduino YUN and a USB webcam.
	  I've added a class for sensing and storing temperature values. -Mike
	*/

	#include "TrapSat.h"
	//#include "Arduino.h"
	#include "Bridge.h"
	#include "FileIO.h"


	CameraMod::CameraMod() // Constructor
	{
	   filename = "newPicture.png"; // Will be changed to the current dateTime of
	   location = "/mnt/sda1/"; // Root of the sdcard
	}
	void CameraMod::SetName(String n) // used to set the name of the picture
	{
	  filename = n + ".png";
	}

	void CameraMod::SetDir(String dir)  // used to set the directory where the file should be stored
	{
	  location = location + dir + "/"; // since location is already set to the root of the SD, this is really meant to add a folder,
	                   // or multiple folders to the directory path
	}

	void CameraMod::TakePic()
	{
	  Process pic; // Starts a Linux process named pic
	  pic.begin("fswebcam"); // Uses the fswebcam command
	  pic.addParameter(location + filename); // Adds a paramater to fswebcam. This is the full directory path where the file will be saved.
	  pic.run(); // Actually runs the pic process on the Linux processor. !!!This command will halt the program until complete!!!
	}

	String CameraMod::GetPic()// Will return the full directory path, including the name of the file
	{
	  return location + filename;
	}





	TempSensor::TempSensor(int pin)
	{
	    analogReference(EXTERNAL); //this needs to be here when using some reference voltage other than 5 volts for analog inputs
	    _pin = pin;
	}

	float TempSensor::getTemp()
	{
float reading = analogRead(_pin); //1-Taking in values through the A/D converter from 0 to 1023
  float voltage = reading*(3.3/1024.0); //2-Multiplying reading by voltage step size to get voltage
  float TempC = (voltage*100.0)-50.0; //3-Plugging voltage into sensor-specific formula to get temperature in degrees Celsius
  float TempF = (1.8*TempC)+32.0; //4-Converting degrees Celsius to Fahrenheit
 return TempF;
	}

void	TempSensor::storeTemp(float TempF)
	{
	    //This method is a modified version of the "Datalogger" example that comes with the Arduino IDE

	   String dataString;
	    String result;
  Process time;
  // date is a command line utility to get the date and the time
  // in different formats depending on the additional parameter
  time.begin("date");
  time.addParameter("+%D-%T");  // parameters: D for the complete date mm/dd/yy
  //             T for the time hh:mm:ss
  time.run();  // run the command

  // read the output of the command
  while (time.available() > 0) {
    char c = time.read();
    if (c != '\n')
      result += c;
  }
  dataString += result;
  dataString += " = ";

  dataString += String(TempF);

  File dataFile = FileSystem.open("/mnt/sd/datalog.txt", FILE_APPEND);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  else {
    Serial.println("error opening datalog.txt");
}

delay(10000);
	}
