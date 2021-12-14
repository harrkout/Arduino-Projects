#include <Wire.h>

int ldr;
int flag=1;

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);     
  while(!Serial);

  Wire.begin(127);

  Wire.onRequest(reqEvt); 
}

void loop()
{
  int ldr = analogRead(A0);
  Serial.println(ldr);
  delay(100);
  
  if(ldr> 300){
      Serial.println("----------------------");
      Serial.println("Day \nLight Disabled");
      flag=0;
      delay(100);
  }
  if(ldr< 300){
      Serial.println("----------------------");
      Serial.println("Night \nLight Enabled");
      flag=1;
      delay(100);
  }

}
void reqEvt()
{
  Wire.write(flag); 
}
