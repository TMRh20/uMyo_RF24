/*
Obtaining muscle data from uMyo via nRF24 module
Usage: attach nRF24 module using any tutorial
 - open Serial Plotter (or Serial Monitor) at 115200 speed
 - turn on uMyo device
 - switch it into RF24 mode if necessary (to switch, 
press button once or twice, depending on current mode until you see 3 pink blinks)
 - you should see muscle activity chart on a plot (or as serial output)
*/

#include <uMyo_RF24.h>


void setup() {
  Serial.begin(115200);
  uMyo.begin();
}

uint32_t last_print_ms = 0;
float lastValue[3];
uint32_t valueTimer = 0;
bool printDefault = true;

void loop() 
{
  uMyo.run(); //need to call this really often, therefore
  //no delays can be used in the code
  int dev_count = uMyo.getDeviceCount(); //if more than one device is present, show all of them
  if(millis() - last_print_ms > 30)
  {
    for(int d = 0; d < dev_count; d++)
    {
      float mLevel = uMyo.getMuscleLevel(d);

      if(mLevel == lastValue[0] && mLevel == lastValue[1] && mLevel == lastValue[2]){
        Serial.print("0");
      }else{
        Serial.print(mLevel);
      }
      if(millis() - valueTimer > 250){
          valueTimer = millis();
          lastValue[2] = lastValue[1];
          lastValue[1] = lastValue[0];
          lastValue[0] = mLevel;
      }
      if(d < dev_count-1) Serial.print(' ');
       else Serial.println();
    }
      last_print_ms = millis();    
  }
}
