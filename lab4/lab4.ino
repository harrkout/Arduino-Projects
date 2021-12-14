#include <LiquidCrystal.h>

#define sensorIn A0
#define sensorOut A1

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

//buttons
int button1 = 2;
int button2 = 3;

//buzzer
int piezo = 13;

//leds
int led3 = 3;
int led2 = 3;
int led1 = 10;

//sensor
int trig = 11;
int echo = 12;

//light detector
int ldr = A5;  

//temperature
float celsius;
int temp = A0;
float tempValue;

//flags
int flag_yo=0;
int flag = 0;
int state = 0;
int flag_intruder = 0;
int intruder_wants_in = 0;
int intruder_got_in = 0;

void setup() {
  
  pinMode(piezo, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT); 
  pinMode(A3, INPUT); 

  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  
  
  //-------------------------------------------------
    //Temperature
    int tempInside = analogRead(sensorIn);
    int tempOutside = analogRead(sensorOut);

    // Convert the reading into voltage:
    float voltageIn = tempInside * (5000 / 1024.0);
    float voltageOut = tempOutside * (5000 / 1024.0);

    // Convert the voltage into the temperature in degree Celsius:
    float celsiusIn = voltageIn / 10;
    float celsiusOut = voltageOut / 10;

    lcd.setCursor(0, 0);
    lcd.print("TempIn:");
    lcd.print(celsiusIn);
    lcd.setCursor(0, 1);
    lcd.print("TempOut:");
    lcd.print(celsiusOut);
    delay(3000);
  
  //----------------------------------------   
    //Light detection

    if(analogRead(ldr) < 150)		//255 max for analog
       digitalWrite(led1, !state);
    else if(analogRead(ldr) > 150)
       digitalWrite(led1, state);


  //-------------------------------------------------
  //Intruder alert
  
    digitalWrite(trig, LOW);
    //delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    //delayMicroseconds(10);
    digitalWrite(trig, LOW);

  
    unsigned long duration = pulseIn(echo, HIGH);

    int distance = duration / 29 / 2;


    if(distance <100 && flag_intruder == 0){
      lcd.clear();
      flag=1;
      digitalWrite(trig, 10);
      delayMicroseconds(2);
      tone(piezo, 2000, distance*10);
      lcd.setCursor(0, 0);
      lcd.print( "Intruder at: " + String(distance)+"\r\n" );
      lcd.setCursor(0, 1);
      lcd.print("cm.");
      intruder_wants_in = 1;
      delay(3000);

    if (digitalRead(button1) == 1 && intruder_wants_in == 1){
      digitalWrite(led1, !state);
      lcd.setCursor(0, 0);
      lcd.print( "Intruder wants\n");
      lcd.setCursor(0, 1);
      lcd.print("in");
      tone(piezo, 100, 200);
      delay(3000);
      intruder_got_in = 1;

    if (digitalRead(button2) == 1)
    {
      if(intruder_got_in == 1)
      {
        analogWrite(led1, !state);
        analogWrite(led2, 1);
        analogWrite(led3, 1);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Run!");
        delay(2000);
        flag_yo=1;
      }
    }
   }
  lcd.print(millis() / 1000);
  }
}