/*
  Author: Zach Richard
  Date: 05/19/2014
  Project: Trap Sat: Capitol College

  This library will be used to take and store pictures using the Arduino YUN and a USB webcam.
*/
#ifndef CameraMod_h
#define CameraMod_h
// Headers:
#include "Arduino.h"

class CameraMod
{
  private:
    String filename;  // Name of the file.
    String location;  // Location to be saved
  public:
    CameraMod();
    void SetName(String); // used to set the name of the picture
    void SetDir(String);  // used to set the directory where the file should be stored
    void TakePic();
    String GetPic(); // Will return the full directory path, including the name of the file
};

#endif

