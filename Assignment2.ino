//Three Switch toggle Red Green Blink Yellow

const int buttonPin1 = 11;
const int buttonPin2 = 10;
const int buttonPin3 = 9;

const int ledPin1 = 5;
const int ledPin2 = 4;
const int ledPin3 = 3;

int buttonState1;
int buttonState2;
int buttonState3;

long debounceDelay = 50;

long lastDebounceTime1 = 0;
long lastDebounceTime2 = 0;
long lastDebounceTime3 = 0;

int lastButtonState1 = LOW;
int lastButtonState2 = LOW;
int lastButtonState3 = LOW;

unsigned long CledTime1;
unsigned long CledTime2;
unsigned long CledTime3;

int debouncedelay = 50;

int lastbutton1 = LOW;
int lastdebouncetime1;
unsigned long currentdebouncetime1;

int lastbutton3 = HIGH;
int lastdebouncetime3;
unsigned long currentdebouncetime3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin3, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);

  int reading1 = digitalRead(buttonPin1);
  int reading3 = digitalRead(buttonPin3);
  
//----------------------------------------------------------------------------------//
  if(reading1 != lastbutton1){
    currentdebouncetime1 = millis();
  }
  if(millis() - currentdebouncetime1 >= 200){
    if(buttonState1 == HIGH){
      CledTime1 = millis();
      if(digitalRead(ledPin1) == LOW){
        digitalWrite(ledPin1, HIGH);
      }
      else{
        digitalWrite(ledPin1, LOW);
      }
    }
    if(millis() - CledTime1 >= 3000){
      digitalWrite(ledPin1, LOW);
    }
  }
  lastbutton1 = digitalRead(buttonPin1);
    

//---------------------------------------------2-----------------------------------//
  if (buttonState2 == LOW && digitalRead(ledPin1) == LOW && digitalRead(ledPin3) == LOW){
    digitalWrite(ledPin2,HIGH);
    delay(30);
    digitalWrite(ledPin2,LOW);
    delay(500);
    digitalWrite(ledPin2,HIGH);
    delay(30);
    digitalWrite(ledPin2,LOW);
    delay(500);
    digitalWrite(ledPin2,HIGH);
    delay(30);
    digitalWrite(ledPin2,LOW);
    delay(500);
    digitalWrite(ledPin2,HIGH);
    delay(30);
    digitalWrite(ledPin2,LOW);
  }


//---------------------------------------------3-----------------------------------//
  if(reading3 != lastbutton3){
    currentdebouncetime3 = millis();
  }
  if(millis()-currentdebouncetime3 >= 200){
    if(buttonState3 == LOW)
    {
      CledTime3 = millis();
      if(digitalRead(ledPin1)!= HIGH && digitalRead(ledPin3) == LOW){
        digitalWrite(ledPin3, HIGH);
      }
      else{
        digitalWrite(ledPin3,LOW);
      }
    }
    
    if (millis() - CledTime3 >= 3000)
    {
      digitalWrite(ledPin3, LOW);
    }
    if(reading3 != buttonState3){
      buttonState3 = reading3;
    }
  }
  lastbutton3 = digitalRead(buttonPin3);
  Serial.println(millis() - currentdebouncetime1);
}
