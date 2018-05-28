

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



int input1 = 0; //var for analog input
CurrentSwitch test1(input1, 100, 10); //start an instance (analog intput pin, sensor current range, current level trigger)

void setup() {
  Serial.begin(9600);
  //analogReadResolution(12); //arduino DUE only for 12bit analog resolution
  //CurrentSwitch::reso(12); //arduino DUE only for 12bit analog resolution

    //Monitoring of sensor is done trough an interrupt timer
  Timer1.initialize(1000000);//run timer at 10Hz
  Timer1.attachInterrupt(CurrentSwitch::handler); // handle monitoring of all CurrentSwitch instance
}

void loop() {
  //use the workProff function to trigger something
  if (test1.workProof(input1)) { //if working
    Serial.println("input working");
  }
  else if (!test1.workProof(input1)) { //if not working
    Serial.println("input not working");
  }

 // test1.trigger(15);//change the value of current trigger at anytime, 
        //when changing, reading buffer is reset so it will return false at first

  delay(1000);
}
