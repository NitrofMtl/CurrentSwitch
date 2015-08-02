@@ -0,0 +1,66 @@
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



#include <currentSwitch.h>
#include <Scheduler.h>

int input1 = 0; //var for analog input
currentSwitch test1; //start an instance of the library

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  test1.initCurrentSwitch(12); // initiate library, analog resolution 10 or 12 for arduino DUE
  test1.setCurrentSwitch(input1, 100, 10); //start an analog intput, sensor current range, current trigger
  Scheduler.startLoop(inputMonitor);// start an instance of sceduler for real time input reading
}

void loop() {
  //use the workProff function to trigger something
  if (test1.workProof(input1)) { //if working
    Serial.println("input working");
  }
  else if (!test1.workProof(input1)) { //if not working
    Serial.println("input not working");
  }
  yield();
  delay(1000);
}

void inputMonitor() {
  test1.update(); //monitorize current sensor
  yield();
}

