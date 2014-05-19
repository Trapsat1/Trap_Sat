void TakePic(String fileName) 
{
  Process pic;
  pic.begin("fswebcam");
  pic.addParameter("/mnt/sda1/" + fileName + ".png");
  pic.run();
}

string GetPic()
{
}


