/*
  Author: Zach Richard
  Date: 05/19/2014
  Project: Trap Sat: Capitol College

  This library will be used to take and store pictures using the Arduino YUN and a USB webcam.
*/
#include <String.h> // Not sure if best practice
#include <Process.h>
#include <Bridge.h>

#include "CameraMod.h"

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
    

