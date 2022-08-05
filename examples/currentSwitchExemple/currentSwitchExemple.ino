

/*

CurrentSwitch Is a library to use non invasive current probe to use it a a 'working proof'. 
This skecht use a SCT-013-000. Interface with arduino here and original emonLib library:
 ***************  https://github.com/openenergymonitor/EmonLib  *************

Instead of emonLib that read real current, this on only return 'true' if there is 'some current'. 
This is usefull usefull as workproof and very weightless compare to emonLib.

  Copyright (c) 31/07/2015

    By Nitrof

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  */


#include <TimerOne.h>
#include <currentSwitch.h>



#define INPUT1 0 //var for analog input
#define CURRENT_SCALE 100
#define CURRENT_TRESHOLD 10


#define SECTOR_FREQUENCY 60 // or 50Hz in some country

//use ANALOG_RESO_12 if you use 12 bit ADC
CurrentSwitch test1(ANALOG_RESO_10, CURRENT_SCALE, CURRENT_TRESHOLD); //start an instance (analog intput pin, sensor current range, current level trigger)

void setup() {
  Serial.begin(9600);
  //analogReadResolution(12); // for 12bit analog resolution
  

    //Monitoring of sensor is done trough an interrupt timer
  Timer1.initialize(test1.currentSamplingPeriod(SECTOR_FREQUENCY));
  Timer1.attachInterrupt(readCurrentISR); // handle monitoring of all CurrentSwitch instance
}

void loop() {
  //use the workProff function to trigger something
  if (test1.workProof()) { //if working
    Serial.println("input working");
  }
  else if (!test1.workProof()) { //if not working
    Serial.println("input not working");
  }

  if (test1.rised()) {
    Serial.println("The load started!");
  }

  if (test1.droped()) {
    Serial.println("The load stoped!")
  } 

  if (test1.changed() == RISE) {
    Serial.println("The load started!");
  }
  else if (test1.changed() == DROP) {
    Serial.println("The load stoped!");
  }

  delay(1000);
}

void readCurrentISR()
{
  //read all currentSwitch into the ISR
  test1.read(analogRead(INPUT1));
  //other CurrentSwitch.read( [INPUT] );
}
