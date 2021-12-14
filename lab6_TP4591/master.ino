#include <Wire.h>

int val;
int pir=10;
int led_flag_master;
int flag2;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(10, INPUT);

  Serial.begin(9600);
 
  while(!Serial);
 
  Wire.begin(1);
  Wire.onRequest(reqEvt); 
}

void loop()
{
  Wire.requestFrom(127, 1);
  
  pir = digitalRead(10);
  
  if (Wire.available())
  {
    val = Wire.read ();

    if(val==1){
      Serial.print("----------------------\n");
      Serial.print("Night \nLight Enabled\n");
      Serial.println(val);	//slave flag for photoresistor
      flag2=1;
    }
    
    if(val==0){
      Serial.print("----------------------\n");
      Serial.print("Day \nLight Disabled\n");
      Serial.println(val);	//slave flag for photoresistor
      flag2=0;
  	}
    
    analogWrite(11, val);

    if(flag2==1 && pir == HIGH){
		led_flag_master=1;
        Serial.println("Sensor activated!");
      }
      else {
        led_flag_master=0;
        digitalWrite(13, LOW);
      }
  }
  
  delay(100);
}

void reqEvt()
{
  Wire.write(led_flag_master); 
}
