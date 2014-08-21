// !!!IMPORTANT!!! TIE 3.3V PIN TO AREF PIN

#include <TrapSat.h>
#include <Bridge.h>
#include <FileIO.h>

TempSensor TMP(A0);
CameraMod webcam;
String picName = "room";
int n =1;

void setup() 
{
  Serial.begin(9600);
  Bridge.begin();
  FileSystem.begin();
}

void loop()
{
   webcam.SetName(picName + n);
float TempF = TMP.getTemp();
 TMP.storeTemp(TempF);
  webcam.TakePic();
  n++;
  if (n>9)
  n=0;
    }
