#include <Wire.h>

#define LED 11

int led_flag_slave;
int led_state=0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);     
  while(!Serial);
  
  Wire.begin(1);
}

void loop()
{
  Wire.requestFrom(1, 1);

  if (Wire.available())
  {
    led_flag_slave = Wire.read ();

    if(led_flag_slave==1){
      digitalWrite(11, HIGH);
      Serial.print("----------------------\n");
      Serial.print("Led Is Activated\n");
    }
    else{
      Serial.print("----------------------\n");
      Serial.print("Led Is Deactivated\n");
    }
  }
}

void reqEvt()
{
  Wire.write(led_flag_slave); 
}