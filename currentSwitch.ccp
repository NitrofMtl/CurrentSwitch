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


#include "Arduino.h"
#include "currentSwitch.h"


void currentSwitch::initCurrentSwitch(int setReso){ //setup the input resolution, bias = resolution /2
	reso = setReso;
	if (setReso == 12){ //resolution set to 12 bit for arduino due
		reso = 4096;
		bias = 2048; //bias = reso /2
	}
}

void currentSwitch::setCurrentSwitch(int channelId, int Irange, int Itrigger){ // initiate an input, param: analog input, current max of sensor, trigger expected to trigger true
	inputSet[channelId] = true;  //set that this input have benn setup
	triggerBit[channelId] = Itrigger * reso/2 / Irange / 2  ;  // the last 2 divider is to higher the sensivity of the trigger
}

void currentSwitch::update(){ 

	if ((lastMillis - millis()) >= 3){ //timer check to scan every 3 miliseconde
		for (int i = 0; i <= 11; i++){ //scan all analog input
			if(inputSet[i]){ // if analog input a been activated
				triggerLog[i] += inputRead(i); // do the check function and log it in to buffer
				triggerLog[i] = constrain(triggerLog[i],0,10); // constrain buffer 
			}
		}
		lastMillis = millis(); // setup the next check
	}
}

int currentSwitch::inputRead(int input){ 
	int reading = analogRead(input);
	int output = 0;
	if ( (reading < (bias-triggerBit[input])) || (reading > (bias+triggerBit[input])) ){ // compare analog reading to the trigger set each side of the bias
		output = 1; 
	}
	else {
		output = -1;
	}
	return output; // return 1 if bigger or -1 if smaller
}

boolean currentSwitch::workProof(int input){ // check if the trigger buffer have store workingProof
	boolean matrixScan = false;
	if (triggerLog[input] >= 3){ // if input read have return at least 3 time true, return true
		matrixScan = true;
	}
	return matrixScan;
}
