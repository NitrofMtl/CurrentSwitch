/*
CurrentSwitch Is a library to use non invasive current probe to use it a a 'working proof'. 
This skecht use a SCT-013-000. Interface with arduino here and original emonLib library:
 ***************  https://github.com/openenergymonitor/EmonLib  *************

Instead of emonLib that read real current, this on only return 'true' if there is 'some current'. 
This is usefull usefull as workproof and very weightless compare to emonLib.


  Copyright (c) 05/08/2022

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

#define ANALOG_RESO_10 0
#define ANALOG_RESO_12 1

#define WORKPROFF_DECOUNT_SIZE 3

#define DROP -1
#define RISE 1
#define CHANGE_FLAG (1u << 1)

class CurrentSwitch
{
  public:
  CurrentSwitch(bool reso, int IRange, int ITreshold);
  void handler();
  bool workProof() const;
  void read(uint16_t);
  bool rised();
  bool droped();
  int changed();
  uint32_t currentSamplingPeriod(int baseF);
  private:
    static uint16_t offset;
    uint16_t ITreshold = 0;
    uint8_t workProofDecount = 0;
    int8_t changeTracker = 0;
};

#endif //CurrentSwitch_h
