#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.>

int main()
{
  int serial_port;
  char data;

  if ((serial_port = serialOpen ("/dev/tyS0" , 9600)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno));
    return 1;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n" , strerror (errno));
    return 1;
  }

  while (1)
  {
    if (serialDataAvail (serial_port))
    {
      data = serialGetchar (serial_port);
      printf ("%c" , data);
      fflush (stdout);
      serialPutchar(serial_port, data);
    }
  }


}
