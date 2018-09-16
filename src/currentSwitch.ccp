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

#include "Arduino.h"
#include "CurrentSwitch.h"


CurrentSwitch* CurrentSwitch::container[containerSize] = {NULL,NULL,NULL,NULL,NULL,NULL};
int CurrentSwitch::_reso = 1023; //10 bit resolotion
int CurrentSwitch::bias = _reso = 511; //reso / 2
unsigned long CurrentSwitch::lastMillis = 0;

CurrentSwitch::CurrentSwitch(int channelId, int Irange, int Itrigger) : input(channelId), _Itrigger(Itrigger), _Irange(Irange)
 { // initiate an input, param: analog input, current max of sensor, trigger expected to trigger true
  for(int i = 0; i < containerSize; i++){
    if(!container[i]) {
      container[i] = this;
      //_Irange = Irange;
      triggerBit = Itrigger * _reso/2 / _Irange / 2  ;  // the last 2 divider is to higher the sensivity of the trigger
      break;
    }
  }
}

CurrentSwitch::~CurrentSwitch(){
  for(int i = 0; i < containerSize; i++){
    if(this == container[i]) {
      container[i] = NULL;
      break;
    }
  }
}

void CurrentSwitch::handler(){
  if (lastMillis > millis()) lastMillis = millis(); //millis rool back chk 
  if (!(lastMillis - millis()) >= 3) return;//timer check to scan every 3 miliseconde
  for (int i = 0; i <= containerSize; i++){ //scan all analog input
    if(!container[i]) continue; //do nothing if container emty
    CurrentSwitch* instance = container[i];    
    instance->triggerLog += instance->inputRead(instance->input); // do the check function and log it in to buffer
    instance->triggerLog = constrain(instance->triggerLog,0,10); // constrain buffer 
  }
  lastMillis = millis(); // setup the next check
}

void CurrentSwitch::reso(int reso) {
  if (12 == reso){
    _reso = 4095;
    bias = 2047;
  }
  else if (10 == reso){
    _reso = 1023;
    bias = 511;
  }
  for (int i = 0; i <= containerSize; i++){ //apply new bit value to all trigger
    if(!container[i]) continue; //do nothing if container emty
    CurrentSwitch* instance = container[i];
    instance->triggerBit = instance->_Itrigger * _reso/2 / instance->_Irange / 2  ;
  }
}

int CurrentSwitch::inputRead(int input){ 
  int reading = analogRead(input);
  int output = 0;
  if ( (reading < (bias-triggerBit)) || (reading > (bias+triggerBit)) ){ // compare analog reading to the trigger set each side of the bias
    output = 1; 
  }
  else {
    output = -1;
  }
  return output; // return 1 if bigger or -1 if smaller
}

boolean CurrentSwitch::workProof(int input){ // check if the trigger buffer have store workingProof
  boolean buffer = false;
  if (triggerLog >= 3){ // if input read have return at least 3 time true, return true
    buffer = true;
  }
  return buffer;
}

void CurrentSwitch::trigger(int Itrigger){
  triggerBit = Itrigger * _reso/2 / _Irange / 2  ;  // the last 2 divider is to higher the sensivity of the trigger
  triggerLog = 0; //reset buffer when changing trigger value
}
