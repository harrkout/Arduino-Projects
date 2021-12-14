#include <Servo.h>

Servo watering;     //servo for watering
Servo filling;      //servo for refilling water tank

int trig = 11;
int echo = 12;
int water_supply = 500;
int i=0;
int flag=0;
int water_flag=0;

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);     //temperature sensor
  pinMode(A5, INPUT);     //ldr sensor
  pinMode(2, OUTPUT);     //
  pinMode(3, OUTPUT);     //h-bridge for cooler DC-motor
  digitalWrite(4, HIGH);  //
  
  pinMode(9, OUTPUT);    //
  pinMode(10, OUTPUT);   //h-bridge for heater DC-motor
  pinMode(8, OUTPUT);    //
  
  pinMode(6, OUTPUT);    //watering servo
  pinMode(7, OUTPUT);    //refilling servo
  watering.attach(6);
  filling.attach(7);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop()
{ 
  int temp = analogRead(A0);
  int ldr = analogRead(A5);

  Serial.print("Temperature : ");
  float tempVolt = (float(temp) / 1024)*5.0;
  float tempCelsius = (tempVolt * 100)-50;     //converts temperature to celsius
  Serial.println(tempCelsius);
  delay(0);
  
  Serial.print("LDR: ");       //light sensor value
  Serial.println(ldr);
  delay(0);
  
  //Day
  if(analogRead(A5) > 300){
      Serial.println("Day");
      if(tempCelsius > 21){	        //Cooler DC-Motor
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        Serial.println("Cooler on");   //Turns cooler on if temperature is higher>21C
        Serial.println("Temperature hypothetically lower than 21 ");
        delay(1000);
        Serial.println("------------------------");
  	  }

      else if(tempCelsius < 15)	{	//Heater DC-Motor
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          analogWrite(10, 255);
          Serial.println("Heater on");  //Turns heater on if temperature is lower<15C
          Serial.println("Temperature hypothetically higher than 15 ");
          delay(1000);
          Serial.println("------------------------");
      }
    
    
    //Watering
      if(flag==0){                  //Watering and refilling is done once a day 
       watering.write(90);          //The flag checks if there was a transition to night
       watering.write(0);
       water_supply = 100;          //Watering requires 400 litres (500-400)
       Serial.println("Watering");
       watering.write(90);
       watering.write(0);
       Serial.println("Watering Complete");
       delay(1000);
       Serial.println("------------------------");
      }

       //Refilling water tank
       if(digitalRead(trig) < 100 && flag == 0){   //Refilling is done only after watering
         digitalWrite(trig, 10);
         filling.write(90);
         water_supply=500;               //Water tank is refilled to 500 litres
         flag=1;                         //Flag checks that water is done for the day
         filling.write(0);
         Serial.println("Refilling");
         watering.write(90);
         watering.write(0);
         Serial.println("Refilling Complete");
         delay(1000);
         Serial.println("------------------------");
       }
  }
        
  //Night
   if(analogRead(A5) < 200){
     Serial.println("Night");
  	 if(tempCelsius > 12){      	//Cooler DC-Motor
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        Serial.println("Cooler on");    //Turns cooler on if temperature is higher>12C   
        Serial.println("Temperature hypothetically lower than 12");
        flag = 0;
        delay(1000);
        Serial.println("------------------------");
 	 }

    else if(tempCelsius < 10){	  //Heater DC-Motor
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        analogWrite(10, 255);
        Serial.println("Heater on");    //Turns heater on if temperature is lower<10C
        Serial.println("Temperature hypothetically higher than 10 ");
        flag = 0;
        delay(1000);
        Serial.println("------------------------");
    }
  }   
}
