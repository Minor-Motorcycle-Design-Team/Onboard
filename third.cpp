void InterfaceUART::PortInitialization()
{
        fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NDELAY );
     if (fd <0) {perror(MODEMDEVICE); exit(-1); }

     tcgetattr(fd,&oldtio); /* save current serial port settings */
     bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

        /*
          BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
          CRTSCTS : output hardware flow control (only used if the cable has
                    all necessary lines. See sect. 7 of Serial-HOWTO)
          CS8     : 8n1 (8bit,no parity,1 stopbit)
          CLOCAL  : local connection, no modem contol
          CREAD   : enable receiving characters
        */
         newtio.c_cflag = B9600 | CRTSCTS | CS8 | CLOCAL | CREAD;

        /*
          IGNPAR  : ignore bytes with parity errors
          ICRNL   : map CR to NL (otherwise a CR input on the other computer
                    will not terminate input)
          otherwise make device raw (no other input processing)
        */
         newtio.c_iflag = IGNPAR | ICRNL;

        /*
         Raw output.
        */
         newtio.c_oflag = 0;

        /*
          ICANON  : enable canonical input
          disable all echo functionality, and don't send signals to calling program
        */
         newtio.c_lflag = ICANON;

     /*set signal*/
         //saio.sa_handler = signal_handler_IO;
         //saio.sa_flags = 0;
         //saio.sa_restorer = NULL;
         //sigaction(SIGIO,&saio,NULL);

         fcntl(fd, F_SETFL, FNDELAY);//|FASYNC//FNDELAY ,#FNDELAY makes read function to return with 0 if no characters are available on the port and if FNDELAY == 0, it is blocking mode
         fcntl(fd, F_SETOWN, getpid());

    /*
      initialize all control characters
      default values can be found in /usr/include/termios.h, and are given
      in the comments, but we don't need them here
    */
     newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
     newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
     newtio.c_cc[VERASE]   = 0;     /* del */
     newtio.c_cc[VKILL]    = 0;     /* @ */
     newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
     newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
     newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
     newtio.c_cc[VSWTC]    = 0;     /* '\0' */
     newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
     newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
     newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
     newtio.c_cc[VEOL]     = 0;     /* '\0' */
     newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
     newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
     newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
     newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
     newtio.c_cc[VEOL2]    = 0;     /* '\0' */

    /*
      now clean the modem line and activate the settings for the port
    */
     tcflush(fd, TCIFLUSH);
     tcsetattr(fd,TCSANOW,&newtio);

        return;
}

void *InterfaceUART::ReadData(void *p){
      //InterfaceUART *app = (InterfaceUART*)p;
      res = read(fd,buf,255);
    //buf[res] = 0;
      float *a = (float*)malloc(sizeof(float));
      *a = (float)atof(buf);
      //pthread_exit((void*)&a); //success
      return (void*)a;
}
void *InterfaceUART::ReadData_helper (void *p){
    InterfaceUART *app = (InterfaceUART*)p;
    return ((InterfaceUART*)p)->ReadData(app);
}
