#include "SoftwarePWM.h"


uint8_t j;
PWM * PwM;


void PWM::CreatePWM(PWM * pr)
{
	PwM = pr;
}


PWM::PWM(uint8_t n, uint8_t OF, unsigned int PF, uint8_t pre)
{
	ICR = ((OF*MillionFactor)/(PF*pre))-1;
	//one_over_accuracy = (OF*MillionFactor)/(pre*MillionFactor);
	NumberOfPWM = n;
	flag = (bool*) malloc(NumberOfPWM);
	PWMs = (EachPWM*) malloc(NumberOfPWM);
	Timer1_init();
}


bool PWM::getflags(uint8_t i)
{
	return flag[i];
}
void PWM::setflags(uint8_t i, bool tf)
{
	flag[i] = tf;
}



void PWM::Timer1_init()
{
	TCCR1B |= (1 << WGM12)|(1 << WGM13)|(1 << CS11);
	if(ICR <= 65535) ICR1 = ICR;
	TIMSK1 |= (1 << OCIE1A)|(1 << OCIE1B);
}


void PWM::SetPWM_DutyCycle(unsigned int dc, uint8_t indexOfPWM)
{
	PWMs[indexOfPWM].current_pwm_dutyCycle = dc; // dc*one_over_accuracy;
}

void PWM::attachPWM(uint8_t indexOfPWM, volatile uint8_t * port, volatile uint8_t * dir, uint8_t pin, unsigned int _max, unsigned int _min)
{
	PWMs[indexOfPWM].port = port;
	PWMs[indexOfPWM].pin = pin;
	*dir |= (0x01 << pin);
	PWMs[indexOfPWM].max = _max;
	PWMs[indexOfPWM].current_pwm_dutyCycle = (_min + _max)/2; // ((_min + _max)/2)*one_over_accuracy;
}

void PWM::startPWM()
{
	flag[0] = true;
	for (uint8_t i = 1; i < NumberOfPWM; i++)
	{
		flag[i] = false;
	}
	unsigned int sum = 0;
	for(uint8_t i = 0; i < NumberOfPWM; i++)
	{
		sum += PWMs[i].max; //(PWMs[i].max * one_over_accuracy);
	}
	space = (((ICR+1) - sum)/(NumberOfPWM+1));
	uint8_t index = 0;
	for(unsigned int i = 0; i <= ICR; i = i+PWMs[index-1].max+space)
	{
		if(index != NumberOfPWM)
		{
			PWMs[index].start = i+space;
			index++;
		}
		else break;
	}
	OCR1B = PWMs[0].start;
}


ISR(TIMER1_COMPB_vect)
{
	for(j = 0; j < PwM->NumberOfPWM; j++)
	{
		if(PwM->getflags(j))
		{
			*(PwM->PWMs[j].port) |= (1 << PwM->PWMs[j].pin);
			OCR1A = PwM->PWMs[j].start + PwM->PWMs[j].current_pwm_dutyCycle;
			break;
		}
	}
}
ISR(TIMER1_COMPA_vect)
{
	for(j = 0; j < PwM->NumberOfPWM; j++)
	{
		*(PwM->PWMs[j].port) &= ~(1 << PwM->PWMs[j].pin);
		if(PwM->getflags(j))
		{
			PwM->setflags(j, false);
			if(j != PwM->NumberOfPWM-1)
			{
				PwM->setflags(j+1, true);
				OCR1B = PwM->PWMs[j+1].start;
			}
			else
			{
				PwM->setflags(0, true);
				OCR1B = PwM->PWMs[0].start;
			}
			break;
		}
	}
}
