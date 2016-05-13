# Software-PWM

## About

This library is designed to work with AVR Micro-controllers: ATmega48A/PA/88A/PA/168A/PA/328/P,
So you can use it directly with Arduino UNO, Duemilanove and other boards with those micro-controllers.
It enables you to generate multiple PWMs with the same frequency with different duty cycles on any I/O pin.
It has different technique from "Servo.h" in Arduino libraries.
Number of valid generated PWMs depends on frequency chosen, duty cycles chosen for each PWM and -of course- the number of available I/O pins.

## How to use it?

1- You are limited to create only one instance(object) of the PWM class in your code.
```C
PWM object_name(number_of_PWMs, operating_frequency_of_microcontroller, PWM_frequency, prescalar);
```
2- You MUST do this step in your code.
```C
object_name.CreatePWM(&object_name);
```
3- Create a PWM.
```C
object_name.attachPWM(index_of_PWM, address_of_desired_PORT, address_of_desired_DDR, pin_number, max_duty_cycle, min_duty_cycle);
```
=> `index_of_PWM`: 0...n ;where n = ```number_of_PWMs``` - 1

=> `address_of_desired_PORT`: e.g. &PORTB

=> `address_of_desired_DDR`: e.g. &DDRB


4- Start generation of PWMs.
```C
object_name.startPWM();
```
5- You can change duty cycle of any PWM at run time.
```C
object_name.SetPWM_DutyCycle(new_duty_cycle, index_of_PWM);
```

## Further Development

Library will support more AVR micro-controllers.

## Copyright

Copyright 2016 Yousef Ahmed Kamal Abbas

   Licensed under the Apache License, Version 2.0 (the "License");
   
   you may not use this file except in compliance with the License.
   
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
