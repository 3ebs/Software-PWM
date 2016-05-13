/*Copyright 2016 Yousef Ahmed Kamal Abbas

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.*/ 
   
   
#ifndef SOFTWAREPWM_H_
#define SOFTWAREPWM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define MillionFactor	1000000


class EachPWM
{
	public:
	unsigned int start;
	unsigned int current_pwm_dutyCycle;
	volatile uint8_t * port;
	uint8_t pin;
	unsigned int max;	
};

class PWM
{
private:
	bool * flag;
	unsigned int space;
	//uint8_t one_over_accuracy;
	unsigned int ICR;
    void Timer1_init();
	
	
public:
	EachPWM * PWMs;
	uint8_t NumberOfPWM;
	PWM(uint8_t n, uint8_t OF, unsigned int PF, uint8_t pre);
	void SetPWM_DutyCycle(unsigned int dc, uint8_t indexOfPWM);
	void attachPWM(uint8_t indexOfPWM, volatile uint8_t * port, volatile uint8_t * dir, uint8_t pin, unsigned int _max, unsigned int _min);
	bool getflags(uint8_t i);
	void setflags(uint8_t i, bool tf);
	EachPWM * returnPointer();
	void startPWM();
	void CreatePWM(PWM * pr);
};


#endif
