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


#ifndef CurrentSwitch_h
#define CurrentSwitch_h
#include "Arduino.h"


class CurrentSwitch
{
  public:
    CurrentSwitch(int channelId, int Irange, int Itrigger); // star an analog input
    ~CurrentSwitch();
    static void handler(); // realtime input monitoring
    boolean workProof(int input); //output return function
    static void reso(int reso);
    void trigger(int Itrigger);

  private:
    static const uint8_t containerSize = 6;
    static CurrentSwitch* container[containerSize];
    static int _reso;  	// analog resolution resolution
    static int bias;  //bias = resolution /2
    static unsigned long	lastMillis; //timer for reading update
    int triggerBit; // store value that will trigger the output
    int triggerLog; //store tigger true to debounce output
    uint8_t input;
    int inputRead(int input); //reading analog input
    int _Irange;
    int _Itrigger;
};

#endif
