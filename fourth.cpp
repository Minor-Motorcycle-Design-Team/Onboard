#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

using namespace std;

int main(int argc, char** argv)
{
	int uart0_filestream = -1;
	uart0_filestream = open("/dev/ttyUSB1", O_RDONLY | O_NOCTTY | O_NDELAY);
	if (uart0_filestream == -1)
	{
		printf("Error - Unable to open UART");
	}
	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600 | CRTSCTS | CS8 | PARENB | CLOCAL | CREAD;
	options.c_iflag = IGNPAR | ICRNL;
	options.c_oflag = 0;
	options.c_lflag = ICANON;
  fcntl(uart0_filestream, F_SETFL, FNDELAY);
  fcntl(uart0_filestream, F_SETOWN, getpid());
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
	if (uart0_filestream != -1)
	{
		unsigned char rx_buffer[256];
		int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);
		while (rx_length < 255)
		{
			if (rx_length < 0)
			{
				std::cout<<"An error occured";
			}
			else if (rx_length == 0)
			{
				std::cout<<"No data, waiting";
			}
			else
			{
				rx_buffer[rx_length] = '\0';
				printf("%i bytes read: %s\n", rx_length, rx_buffer);
			}
		}
	}
	close(uart0_filestream);
}
