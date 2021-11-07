int led = 13;
int btn = 8;

int state = 0;
int flag = 0;
int flag_prev = 0;


void setup() {
  
  pinMode(btn, INPUT_PULLUP);
  
  pinMode(led, OUTPUT);
  
}

void loop() {
  
  if ( digitalRead(btn) == 0 & flag == 0 )
  {
    flag = 1;
    
    if(flag_prev==1)
       state = !state;
    
    flag_prev = 0;

  }
  else if (digitalRead(btn) == 1 & flag == 1 )
  {
    flag = 0;
    if(flag_prev==0)
       state = state;

    flag_prev = 1;
  }
    
  digitalWrite(led, state);
  delay(250);

}
