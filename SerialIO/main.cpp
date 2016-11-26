#include "USBSerial.h"

int main(void) {
	USBSerial Cerebot("/dev/ttyACM1");
	USBSerial Uno("/dev/ttyACM0");
	unsigned char buf = '\0';
	std::string response;

	do {
		buf = Uno.readChar();
		std::cout << "Sent: " << buf << std::endl;
	    Cerebot.writeChar(buf);
	    response = Cerebot.readChars();
    	std::cout << "Received: " << response;
    	Uno.writeChars(response);
	} while( buf != 'X' );

	return 0;
}