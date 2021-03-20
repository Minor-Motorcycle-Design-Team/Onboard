#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

int
open_port(void)
{
	int fd;
	fd = open("/dev/ttyfl" , O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		perror ("open_port: Unable to open /dev/ttyfl -");
	}
	else
	{
		fcntl(fd, F_SETFL, 0);
	}
	return (fd);
}
