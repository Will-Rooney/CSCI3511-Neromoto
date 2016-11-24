#include "USBSerial.h"

int main(void) {
	USBSerial Cerebot("/dev/ttyACM1");
	USBSerial Uno("/dev/ttyACM0");
	unsigned char buf = '\0';

	do {
		buf = Uno.readChar();
		std::cout << "Sent: " << buf << std::endl << "Received: ";
	    Cerebot.writeChar(buf);
    	std::cout << Cerebot.readChars();
	} while( buf != 'X' );

	return 0;
}