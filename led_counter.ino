int ld1 = 13;
int ld2 = 12;

int btn = 2;

int state1 = LOW;
int state2 = LOW;

int flag = 0;
int i=0;
int count_of_fives = 0;

void setup()
{
  pinMode(btn, INPUT_PULLUP);
  pinMode(ld1, OUTPUT);
  pinMode(ld2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), lightLED, FALLING);
}

void loop()
{

  for(i=0;i<=24;i++){

    flag++;
    digitalWrite(ld1, state1);
    state1 = !state1;
    delay(300);
    
    if(flag%5==0){

        count_of_fives++;
        digitalWrite(ld2, state2);
	state2 = !state2;
        delay(0);
      
        if(count_of_fives==10) 		//για καποιο λογο το loop counter μετραει διπλα,
	    exit(0);			//οποτε επρεπε να το θεσω 10 αντι για 5
    }
  }	
}

void lightLED(void)
{
    digitalWrite(ld2, state2);
    state2 = !state2;
  
}

