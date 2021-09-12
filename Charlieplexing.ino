
void setup() {
  // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
   for(int i=1;i<=10;i++)
   {
    if(i==1){
      pinMode(6,OUTPUT);
      digitalWrite(6, LOW);
      pinMode(5, OUTPUT);
      digitalWrite(5, HIGH);
      delay(500);
    }
    else if(i==2||i==10){
      pinMode(6, OUTPUT);
      digitalWrite(6, HIGH);
      pinMode(5, OUTPUT);
      digitalWrite(5, LOW);
      delay(500);
    }
    else if(i==3||i==9){
      pinMode(4, OUTPUT);
      digitalWrite(4, HIGH);
      pinMode(5, OUTPUT);
      digitalWrite(5, LOW);
      delay(500);
    }
    else if(i==4 || i==8){
      pinMode(4, OUTPUT);
      digitalWrite(4, LOW);
      pinMode(5, OUTPUT);
      digitalWrite(5, HIGH);
      delay(500);
    }
    else if(i==5 || i==7){
      pinMode(4, OUTPUT);
      digitalWrite(4, HIGH);
      pinMode(6, OUTPUT);
      digitalWrite(6, LOW);
      delay(500);
    }
    else if(i==6){
      pinMode(4, OUTPUT);
      digitalWrite(4, LOW);
      pinMode(6, OUTPUT);
      digitalWrite(6, HIGH);
      delay(500);
    }
    pinMode(6, INPUT);
    pinMode(5, INPUT);
    pinMode(4, INPUT);
   }
   
   
}
