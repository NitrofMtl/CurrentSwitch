#include "Arduino.h"
#include "CurrentSwitch.h"

uint16_t CurrentSwitch::offset = 0;

CurrentSwitch::CurrentSwitch(bool reso, int IRange, int treshold)
{
  if ( ANALOG_RESO_12 ) offset = 4096/2 -1;
  else offset = 1024/2 -1;
  if ( treshold <= 1 ) treshold = 2; //safegard, minimum amp reading of 2A
  ITreshold = (offset+1) * (treshold/2) / IRange; //set the treshold half to be more sensible
}

void CurrentSwitch::read(uint16_t aIn)
{
  if ( aIn >= ( offset+ITreshold ) || aIn <= ( offset-ITreshold ) ) workProofDecount = WORKPROFF_DECOUNT_SIZE;
  else if ( workProofDecount ) workProofDecount--;
  //check if the workProof bit is still the same, if not return
  if ( !( (changeTracker & ~CHANGE_FLAG) ^ workProof() ) ) return;
  changeTracker = workProof() |  CHANGE_FLAG;
}

bool CurrentSwitch::workProof() const
{
  return workProofDecount;
}

uint32_t CurrentSwitch::currentSamplingPeriod(int baseF) //period in uSec
{ //sampling at 1 and 2/3 of the monitored frequency,
  float basePeriod = 1000000./baseF;
  return basePeriod/3*2 + basePeriod;
}

bool CurrentSwitch::rised()
{
  if ( !(CHANGE_FLAG & changeTracker) || !(changeTracker & ~CHANGE_FLAG) ) return false;
  changeTracker &= ~CHANGE_FLAG;
  return true;
}

bool CurrentSwitch::droped()
{
  if ( !(CHANGE_FLAG & changeTracker) || (changeTracker & ~CHANGE_FLAG) ) return false;
  changeTracker &= ~CHANGE_FLAG;
  return true;
}

int CurrentSwitch::changed()
{
  if ( !(CHANGE_FLAG & changeTracker) ) return 0;
  changeTracker &= ~CHANGE_FLAG;
  if (changeTracker) return RISE;
  return DROP;
}