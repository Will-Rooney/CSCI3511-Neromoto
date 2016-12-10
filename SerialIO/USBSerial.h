/*
 *  USBSerial.h
 *  Basic USB Serial IO
 *
 *  Created by Rooney, William on 11/23/2016.
 *  Source: http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing
 *
 */

#ifndef USBSERIAL_H
#define USBSERIAL_H

#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <iostream>

class USBSerial {
public:
	USBSerial(const char *device);
	~USBSerial();

	void setBaudRate(const speed_t &rate);
	void getAttributes();
	void setAttributes();
	void flushPort();

	unsigned char readChar();
	std::string readChars();
	void writeChar(unsigned char c);
	void writeChars(std::string s);

private:
	struct termios tty;
	int USB;
};

#endif