/* Quadrature encoder Switch
	for Arduino UNO, Mini, Micro etc. with two external interrupt pins (ATMEGA128,ATMEGA328)
	MUST connect encoder switch output A and B to int0 and int1 (Arduino Pins 2 and 3) and is therefore
	limited to 1 encoder!
	implement center button with debounce library <debounce.h>
	michael@ruck.com, feb. 2015
*/
#include "QuadratureEncoderSwitch.h"

QuadratureEncoderSwitch::QuadratureEncoderSwitch(int16_t _limit_top, int16_t _limit_bottom){
	instance0_ = this;
	limit_top=_limit_top;
	limit_bottom=_limit_bottom;
	
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	attachInterrupt(0, isr_pin_a, FALLING);
	attachInterrupt(1, isr_pin_b, FALLING);
}

QuadratureEncoderSwitch::~QuadratureEncoderSwitch(){
	//nothing
}

int16_t QuadratureEncoderSwitch::read(){
	return count;
}

void QuadratureEncoderSwitch::counter(int8_t increment)
{
  if (increment != 0)
  {
    if ((count + increment <= limit_top) & (count + increment >= limit_bottom)) count = count + increment;
    else if (count + increment > limit_top) count = limit_bottom;
    else if (count + increment < limit_bottom) count = limit_top;
  }
}

void QuadratureEncoderSwitch::isr_pin_a()
{
  byte state_b = digitalRead(3);
  instance0_->count_old = instance0_->count;
  if (state_b == LOW) instance0_->counter(instance0_->increment);
  instance0_->increment = 0;
  if (state_b == HIGH) instance0_->increment = 1;
}

void QuadratureEncoderSwitch::isr_pin_b()
{
  byte state_a = digitalRead(2);
  instance0_->count_old = instance0_->count;
  if (state_a == LOW) instance0_->counter(instance0_->increment);
  instance0_->increment = 0;
  if (state_a == HIGH) instance0_->increment = -1;
}

QuadratureEncoderSwitch * QuadratureEncoderSwitch::instance0_;

void QuadratureEncoderSwitch::reset(int16_t reset_val){
	count=reset_val;
}

void QuadratureEncoderSwitch::setLimits(int16_t _limit_top, int16_t _limit_bottom){
	limit_top=_limit_top;
	limit_bottom=_limit_bottom;
}