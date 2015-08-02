/*

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


#ifndef currentSwitch_h
#define currentSwitch_h
#include "Arduino.h"

class currentSwitch
{
  public:

    void initCurrentSwitch(int setReso); // initiation function
    void setCurrentSwitch(int channelId, int Irange, int Itrigger); // star an analog input
    void update(); // realtime input monitoring
    boolean workProof(int input); //output return function

  private:
    int reso = 1024;  	// input resolution
    int bias = 512;  //bias = resolution /2
    int	lastMillis = 0; //timer for reading update
    int triggerBit[12]; // store value that will trigger the output
    int triggerLog[12]; //store tigger true to debounce output
    boolean inputSet[12] = {false, false, false, false, false, false, false, false, false, false, false, false}; // input started var

    int inputRead(int input); //reading analog input
};

#endif
