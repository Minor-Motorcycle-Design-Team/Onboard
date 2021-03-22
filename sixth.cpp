#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>

using namespace std;

int main()
{
  int fd;
  if ((fd = serialOpen ("/dev/serial0", 9600)) < 0)
  {
    cout<< "unable to open device";
    return 1;
  }
  else
  {
    cout<< "ttyAMA0 initialised ok/n";
  }
  char cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  char cmd2[9];
  cout<<"Tilt Angle Sensor is Running";
  while (1)
  {
    delay(1000);
    write (fd,cmd,9);
    read (fd, cmd2, 9);
    for (int loop = 0; loop <= 8; loop++)
    {
      cout<< (int)cmd2[loop] << "\t";
      cout<< "\n";
      cout<< "\n" << cmd2;
    }
  }
}
