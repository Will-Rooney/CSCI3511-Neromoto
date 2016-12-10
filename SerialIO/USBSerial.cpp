/*
 *  USBSerial.cpp
 *  Basic USB Serial IO
 *
 *  Created by Rooney, William on 11/23/2016.
 *  Source: http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing
 *
 */

#include "USBSerial.h"

USBSerial::USBSerial(const char *device) {
	USB = open( device, O_RDWR | O_NOCTTY );
	memset (&tty, 0, sizeof tty);

	/* Error Handling */
	getAttributes();

	/* Set Baud Rate */
	setBaudRate((speed_t)B9600);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	flushPort();
	setAttributes();
}

USBSerial::~USBSerial() {
	close(USB);
}

void USBSerial::setBaudRate(const speed_t &rate) {
	cfsetospeed (&tty, rate);
	cfsetispeed (&tty, rate);
}

void USBSerial::getAttributes() {
	if ( tcgetattr ( USB, &tty ) != 0 ) {
	   std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
	}
}
void USBSerial::setAttributes() {
	if ( tcsetattr ( USB, TCSANOW, &tty ) != 0 ) {
	   std::cout << "Error " << errno << " from tcsetattr" << std::endl;
	}
}

void USBSerial::flushPort() {
	tcflush( USB, TCIFLUSH );
}

unsigned char USBSerial::readChar() {
	unsigned char buf = '\0';
	read( USB, &buf, 1 );
	return buf;
}

std::string USBSerial::readChars() {
	int n = 0,
    spot = 0;
	char buf = '\0';

	/* Whole response*/
	char response[1024];
	memset(response, '\0', sizeof response);

	do {
	    n = read( USB, &buf, 1 );
	    sprintf( &response[spot], "%c", buf );
	    spot += n;
	    std::cout << buf;
	} while( buf != '\n' && n > 0);

	return std::string(response);
}

void USBSerial::writeChar(unsigned char c) {
	write( USB, &c, 1 );
}

void USBSerial::writeChars(std::string s) {
	const char * c = s.c_str();
	int n_written = 0, spot = 0;

	do {
		n_written = write( USB, &c[spot], 1 );
		spot += n_written;
	} while ( c[spot-1] != '\n' && n_written > 0 );
}
