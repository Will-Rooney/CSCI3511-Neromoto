#include "USBSerial.h"
/*
 * Author: Will Rooney
 *
 * Basic USB Serial Communication on a Linux Platform
 *
 */

int main(int argc, char *argv[]) {
	std::string cerebotPort = "/dev/tty", unoPort = "/dev/tty";
	cerebotPort.append(argv[1]);
	unoPort.append(argv[2]);

	USBSerial Cerebot(cerebotPort);
	USBSerial Uno(unoPort);
	unsigned char buf = '\0';
	std::string response;

	do {
		buf = Uno.readChar();
		std::cout << "Sent: " << buf << std::endl;
	    Cerebot.writeChar(buf);
	    response = Cerebot.readChars();
    	Uno.writeChars(response);
    	std::cout << "Received: " << response;
	} while( buf != 'X' );

	return 0;
}