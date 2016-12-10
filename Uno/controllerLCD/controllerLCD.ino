#include <LiquidCrystal.h>

int loopCount = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Cerebot Status");
  lcd.setCursor(2,1);
  lcd.print("Disconnected");
  Serial.begin(9600);
}

void loop() {
  if (loopCount > 4) {
    end();
    loopCount = 0;
    delay(4000);
  }
  
  // Tests
  forward();
  delay(500);

  stop();
  delay(1000);

  backward();
  delay(500);

  stop();
  delay(1000);

  left();
  delay(1500);

  stop();
  delay(1000);

  right();
  delay(1500);

  stop();
  delay(2000);
  
  loopCount++;
}

String readSerial() {
  String str = "";

  if(Serial.available() > 0)
    str = Serial.readStringUntil('\n');
  else {
    clearLine(1);
    lcd.setCursor(2,1);
    lcd.print("Disconnected");
  }
  

  return str;
}

void printLcdFromSerial() {
  String received = readSerial();
  lcd.print(received);
}

void clearLine(int l) {
  lcd.setCursor(0,l);
  for (int i = 0; i < 16; ++i) {
    lcd.print(" ");
  }
}

void stop() {
  Serial.print('0');
  delay(10);
  clearLine(1);
  lcd.setCursor(0,1);
  printLcdFromSerial();
}

void forward() {
  Serial.print('1');
  delay(10);
  clearLine(1);
  lcd.setCursor(0,1);
  printLcdFromSerial();
}

void backward() {
  Serial.print('2');
  delay(10);
  clearLine(1);
  lcd.setCursor(0,1);
  printLcdFromSerial();
}

void left() {
  Serial.print('3');
  delay(10);
  clearLine(1);
  lcd.setCursor(0,1);
  printLcdFromSerial();
}

void right() {
  Serial.print('4');
  delay(10);
  clearLine(1);
  lcd.setCursor(0,1);
  printLcdFromSerial();
}

void end() {
  // Sends terminating condition for SerialIO C program to stop listening/writing to serial ports
  Serial.print('X');
  clearLine(1);
  lcd.setCursor(2,1);
  lcd.print("Disconnected");
}

