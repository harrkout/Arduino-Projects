#include <LiquidCrystal.h>


LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

int button1 = 2;
int button2 = 3;
int piezo = 13;
int led1 = 12;
int led2 = 11;
int led3 = 10;

int cnt;
int flag = 0;
int state = 0;

void setup() {
  
  pinMode(piezo, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
    
  lcd.begin(16, 1);
}

void loop() {
  
  if ( digitalRead(button1) == LOW && (flag == 0 || flag == 3)  ) 
  {
    digitalWrite(led1, !state);
    lcd.print("Melody 1!");
    tone(piezo, 500, 200);
    delay(100);
    flag = 1;
    digitalWrite(led1, state);
  }
  
  if ( digitalRead(button1) == LOW && flag == 1  ) 
  {
    lcd.print("Melody 2!");
    tone(piezo, 1500, 200);
    delay(100);
    digitalWrite(led2, !state);
    flag = 2;
    digitalWrite(led2, state);
  }

  if ( digitalRead(button1) == LOW && flag == 2  ) 
  {
    digitalWrite(led3, !state);
    lcd.print("Melody 3!");
    tone(piezo, 2000, 200);
    flag = 3;
    delay(100);
    digitalWrite(led3, state);
  }
  
 
  
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}
