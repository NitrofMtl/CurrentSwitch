# CurrentSwitch
## Sketch to interface with arduino to use SCT-013-000 current sensor as a workproof


CurrentSwitch Is a library to use non invasive current probe to use it a a 'working proof'. 
This skecht use a SCT-013-000. Interface with arduino here and original emonLib library:

***  https://github.com/openenergymonitor/EmonLib  ***

Instead of emonLib that read real current, this on only return 'true' if there is 'some current'. 
This is usefull usefull as workproof and very weightless compare to emonLib.

### Download transmiter Shematic : 

https://www.dropbox.com/sh/vzn5upzlsvuat84/AADQE0GaEtgEIRmh-AHvIBM9a?dl=0

***

## New inversion 2.0

- Simpler, lighter API
- Add of on rise, on drop and on change function
- Could be use with other analog current sensor ( 0A have to be at center resolution: 512/1024 or 2048/4096)

***

## Usage

### Create an instance

````
CurrentSwitch myLoad(reso, IRange, ITreshold);
````

- Reso: The analog resolution of the ADC, ANALOG_RESO_10 OR ANALOG_RESO_12
- IRange: The range that the current sensor can read in ampere
- ITreshold: The current level of the load

### Put the handler into a timer
````
#define SECTOR_FREQUENCY 60

void setup() {
    //Monitoring of sensor is done trough an interrupt timer
  Timer1.initialize(myLoad.currentSamplingPeriod(SECTOR_FREQUENCY));
  Timer1.attachInterrupt(readCurrentISR); // handle monitoring of all CurrentSwitch instance
}

void readCurrentISR()
{
  //read all currentSwitch into the ISR
  myLoad.read(analogRead(INPUT1));
  //other CurrentSwitch.read( [INPUT] );
}
````

The "currentSamplingPeriod()" will calculate a sampling period of 1 and 2/3 the sector period. 
Change SECTOR_FREQUENCY to match your country electric distritution: 50 or 60 Hz.

Put into Your ISR all current input you want to monitor.

### Check to workproof
````
void loop() {
  //use the workProff function to trigger something
  if (myLoad.workProof()) { //if working
    Serial.println("input working");
  }
  else if (!myLoad.workProof()) { //if not working
    Serial.println("input not working");
  }
}
````

### Detect on Rise, on Drop and on Change front
````
if (myLoad.rised()) {
  Serial.println("The load started!");
}

if (myLoad.droped()) {
  Serial.println("The load stoped!")
}

if (myLoad.changed() == RISE) {
  Serial.println("The load started!");
}
else if (myLoad.changed() == DROP) {
  Serial.println("The load stoped!");
}
````

## Note:
The front detector only keep the last change until it is checked. If you do not call "rised()" before the load stop, it will return false.

Also, changed use the same status flag that droped and rised so the cannot be use un the same time. if one return non-0, the flag is reset and until another detection, all function will return 0;

***


  Copyright (c) 05/08/2022

    By Nitrof
