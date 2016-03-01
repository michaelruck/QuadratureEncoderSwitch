/* Quadrature encoder Switch
	for Arduino UNO, Mini, Micro etc. with two external interrupt pins (ATMEGA128,ATMEGA328)
	MUST connect encoder switch output A and B to int0 and int1 (Arduino Pins 2 and 3) and is therefore
	limited to 1 encoder!
	implement center button with debounce library <debounce.h>
	michael@ruck.com, feb. 2015
*/
#include <QuadratureEncoderSwitch.h>
#include <debounce.h>

QuadratureEncoderSwitch encoder(10, -10);
DEBOUNCE button(4);

void setup() {
  Serial.begin(9600);
  encoder.setLimits(100);
}

void loop() {
  
  static int b_old;
  int b=encoder;
  if (b != b_old) Serial.println(b);
  b_old=b;
  if(button==LOW) encoder.reset();
}
