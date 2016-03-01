/* Quadrature encoder Switch
	for Arduino UNO, Mini, Micro etc. with two external interrupt pins (ATMEGA128,ATMEGA328)
	MUST connect encoder switch output A and B to int0 and int1 (Arduino Pins 2 and 3) and is therefore
	limited to 1 encoder!
	implement center button with debounce library <debounce.h>
	michael@ruck.com, feb. 2015
*/
#ifndef QUADRATUREENCODERSWITCH_H
#define QUADRATUREENCODERSWITCH_H
#include <Arduino.h>

class QuadratureEncoderSwitch{
	static void isr_pin_a();
	static void isr_pin_b();
	static QuadratureEncoderSwitch * instance0_;
	
	public:
		QuadratureEncoderSwitch(int16_t _limit_top=20, int16_t _limit_bottom=0);
		~QuadratureEncoderSwitch();
		int16_t read();
		operator int16_t() {
			return read();
		};
		
		void reset(int16_t reset_val=0);
		void setLimits(int16_t _limit_top=20, int16_t _limit_bottom=0);
		
	private:
	int16_t count=0, count_old = 0, limit_bottom, limit_top;
	int8_t increment = 0;
	void counter(int8_t increment);		
};
#endif