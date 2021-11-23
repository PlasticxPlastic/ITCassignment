const int car_N = 7;
const int car_E = 6;
const int human = 5;


const int red_W = 13;
const int yellow_W = 12;
const int green_W = 11;


const int red_human = 10;
const int green_human = 9;


const int red_S = 4;
const int yellow_S = 3;
const int green_S = 2; 

#define goW 0
#define waitW 1
#define goS 2
#define waitS 3
#define goH 4
#define waitHu1 5
#define waitHd1 6
#define waitHu2 7
#define waitHd2 8
#define waitHu3 9
#define waitHd3 10

struct State{
  unsigned long ST_Out;
  unsigned long Time;
  unsigned long Next[8]; //000 001 010 011 ---- 111
};

typedef const struct State SType;

SType FSM[11]={
  {B00110010,3000,{goW,waitW,waitW,waitW,goW,waitW,waitW,waitW}},
  {B01010010,500,{goS,goH,goS,goS,goS,goH,goS,goS}},
  {B10000110,3000,{goS,waitS,goS,waitS,waitS,waitS,waitS,waitS}},
  {B10001010,500,{goH,goH,goH,goH,goW,goH,goW,goH}},
  {B10010001,3000,{goH,goH,waitHu1,waitHu1,waitHu1,waitHu1,waitHu1,waitHu1}},
  {B10010011,100,{waitHd1,waitHd1,waitHd1,waitHd1,waitHd1,waitHd1,waitHd1,waitHd1}},
  {B10010001,100,{waitHu2,waitHu2,waitHu2,waitHu2,waitHu2,waitHu2,waitHu2,waitHu2}},
  {B10010011,100,{waitHd2,waitHd2,waitHd2,waitHd2,waitHd2,waitHd2,waitHd2,waitHd2}},
  {B10010001,100,{waitHu3,waitHu3,waitHu3,waitHu3,waitHu3,waitHu3,waitHu3,waitHu3}},
  {B10010011,100,{waitHd3,waitHd3,waitHd3,waitHd3,waitHd3,waitHd3,waitHd3,waitHd3}},
  {B10010001,100,{goW,goW,goS,goS,goW,goW,goW,goW}}
};

unsigned long S=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(red_W,OUTPUT);
  pinMode(yellow_W,OUTPUT);
  pinMode(green_W,OUTPUT);
  pinMode(car_E,INPUT_PULLUP);

  pinMode(red_S,OUTPUT);
  pinMode(yellow_S,OUTPUT);
  pinMode(green_S,OUTPUT);
  pinMode(car_N,INPUT_PULLUP);

  pinMode(red_human,OUTPUT);
  pinMode(green_human,OUTPUT);
  pinMode(human,INPUT_PULLUP);
}
int input,input1,input2,input3;

void loop() {
  // put your main code here, to run repeatedly:  
  digitalWrite(red_W,FSM[S].ST_Out & B10000000);
  digitalWrite(yellow_W,FSM[S].ST_Out & B01000000);
  digitalWrite(green_W,FSM[S].ST_Out & B00100000);

  digitalWrite(red_S,FSM[S].ST_Out & B00010000);
  digitalWrite(yellow_S,FSM[S].ST_Out & B00001000);
  digitalWrite(green_S,FSM[S].ST_Out & B00000100);
  
  digitalWrite(red_human,FSM[S].ST_Out & B00000010);
  digitalWrite(green_human,FSM[S].ST_Out & B00000001);

  delay(FSM[S].Time);

  input1 = digitalRead(car_E); //1
  input2 = digitalRead(car_N); //0
  input3 = digitalRead(human);//1

  input = (input1)*2+(input2)*4+(input3);
  S = FSM[S].Next[input];
  Serial.println(input);
}
