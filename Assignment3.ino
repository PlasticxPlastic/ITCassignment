int number = 0;
byte bitpattern[9]= {0xF9, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
const byte numpin = 8;
const int segmentpin[8] = {8, 7, 4, 5, 6, 9, 10, 3};

const int buttonA = 11;
const int buttonB = 13;

const int ledRed = 2;

byte bitpatternAlphabet[2] = {0x42, 0x47};

int randomnumber;

int lastbtA = LOW;
int currentbtA;
int lastbtB = LOW;
int currentbtB;
int segment;

unsigned long long btAtime = 0;
unsigned long long btBtime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  for(int i = 0; i< numpin;i++)
  {
    pinMode(segmentpin[i], OUTPUT);
  }
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRed, LOW);
  randomSeed(analogRead(A0));
  randomnumber = random(1,10);
}

void loop() {
  // put your main code here, to run repeatedly:
  btA();
  btB();
  Serial.println(randomnumber);
}

void btA()
{
  currentbtA = digitalRead(buttonA);
  if(currentbtA == HIGH && lastbtA == LOW && millis() - btAtime > 100)
  {
    btAtime = millis();
    boolean isbitset;
    number++;
    if(number >= 10)
    {
      number = 1;
    }
    for(segment = 0; segment < 8; segment++)
    {
      isbitset = bitRead(bitpattern[number-1], segment);
      digitalWrite(segmentpin[segment], isbitset);
    }
  }
  lastbtA = currentbtA;
}

void btB()
{
  currentbtB = digitalRead(buttonB);
  if(currentbtB == HIGH && lastbtB == LOW && millis() - btBtime > 100)
  {
    btBtime = millis();
    if(number > randomnumber)
    {
      boolean isbitset;
      for(segment = 0; segment < 8; segment++)
      {
        isbitset = bitRead(bitpatternAlphabet[0], segment);
        digitalWrite(segmentpin[segment], isbitset);
      }
    }
    if(number < randomnumber)
    {
      boolean isbitset;
      for(segment = 0; segment < 8; segment++)
      {
        isbitset = bitRead(bitpatternAlphabet[1], segment);
        digitalWrite(segmentpin[segment], isbitset);
      }
    }
    if(number == randomnumber)
    {
      for(int i=0;i<10;i++)
      {
        boolean isbitset;
        for(segment = 0;segment < 8;segment++)
        {
          isbitset = bitRead(bitpattern[i], segment);
          digitalWrite(segmentpin[segment], isbitset);
        }
        delay(50);
      }
      randomnumber = random(1,10);
      boolean isbitset;
      for(segment = 0;segment < 8;segment++)
      {
        isbitset = bitRead(bitpattern[number-1], segment);
        digitalWrite(segmentpin[segment], isbitset);
      }
    }
  }
  lastbtB = currentbtB;
}
