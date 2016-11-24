int loopCount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (loopCount > 4) {
    end();
  }
  
  // Tests
  forward();
  delay(500);

  backward();
  delay(500);

  left();
  delay(500);

  right();
  delay(500);

  stop();
  delay(2000);
  
  loopCount++;
}

void stop() {
  Serial.print('0');
}

void forward() {
  Serial.print('1');
}

void backward() {
  Serial.print('2');
}

void left() {
  Serial.print('3');
}

void right() {
  Serial.print('4');
}

void end() {
  // Sends terminating condition for SerialIO C program to stop listening/writing to serial ports
  Serial.print('X');
}

