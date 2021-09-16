#include "LedControl.h"

LedControl lc=LedControl(11,13,10,2);

const int btred = 7;
const int btwhite = 6;
unsigned long delaytime=100;

unsigned long long btredtime;
unsigned long long btwhitetime;

int lastbtred = LOW;
int lastbtwhite = LOW;

int currentbtred;
int currentbtwhite;

int delaytimeball = 50;

int barspot = 3;
bool balldirectionup = true; //1=goup 2=godown
bool balldirectionright = true; // 1= ritght 2 = left

int ballspotX = 2,ballspotY = 2,balladdress = 1;
int ballspotXX = ballspotX;

void erase_ball(int ballspotX,int ballspotY, int balladdress){
  lc.setLed(balladdress,ballspotY,ballspotX,false);
  lc.setLed(balladdress,ballspotY,ballspotX,false);
}

void erase_bar(int barspot,int address){
  lc.setLed(address,barspot,0,false);
  lc.setLed(address,barspot+1,0,false);
  lc.setLed(address,barspot+2,0,false);
}

void setup(){
  int devices=lc.getDeviceCount();
  Serial.begin(19200);
  for(int address=0;address<devices;address++){
    lc.shutdown(address,false);
    lc.setIntensity(address,8);
    lc.clearDisplay(address);
  }
  pinMode(btred,INPUT_PULLUP);
  pinMode(btwhite,INPUT_PULLUP);
}

void loop(){
  int devices = lc.getDeviceCount();
  barpong();
  pongmovement();
  barbot();
  int barspot1 = barspot;
  int barspot2 = barspot+1;
  int barspot3 = barspot+2;
  Serial.println(balldirectionright);
}

void barbot(){
  int address = 0;
  for(int i = 0; i<8;i++)
  {
    lc.setLed(address,i,7,true);
  }
}

void barpong(){
  currentbtred = digitalRead(btred);
  currentbtwhite = digitalRead(btwhite);
  const int address = 1;
  if(currentbtred == HIGH && lastbtred == LOW && millis() - btredtime > 100)
  {
    btredtime = millis();
    if(barspot > 0){
      erase_bar(barspot,address);
      barspot--;
      delay(20);
      lc.setLed(address,barspot,0,true);
      lc.setLed(address,barspot+1,0,true);
      lc.setLed(address,barspot+2,0,true);
    }
  }
  lastbtred = currentbtred;
  if(currentbtwhite == HIGH && lastbtwhite == LOW && millis() - btwhitetime > 100)
  {
    btwhitetime = millis();
    
    if(barspot < 5){
      erase_bar(barspot,address);
      barspot++;
      delay(20);
      lc.setLed(address,barspot,0,true);
      lc.setLed(address,barspot+1,0,true);
      lc.setLed(address,barspot+2,0,true);
    }
  }
  lastbtwhite = currentbtwhite;
}

void pongmovement(){
  //goupp
  if(balldirectionup == true) //up
  {
    if(balldirectionright == true) //right
    {
      if(ballspotXX == 8 && ballspotY == 0)
          {
            erase_ball(7,1,1);
          }
      if(ballspotXX < 14) // nothitrightside
      {
        if(ballspotXX + 1 >=8 && ballspotXX + 1<=14) //balladdress0
        {
          ballspotX = ballspotXX - 8;
          balladdress = 0;
          if(ballspotY > 0) //nothittop
          {
            
            if(ballspotXX == 8)
            {
              erase_ball(7,ballspotY+1,1);
            }
            delay(delaytimeball);
            erase_ball(ballspotX,ballspotY,balladdress);
            ballspotY--;
            ballspotX++;
            ballspotXX++;
            lc.setLed(balladdress,ballspotY,ballspotX,true);
            
          }
          else //hittop
          {
            balldirectionup = false;
          }
        }
        else //balladdress1
        {
          ballspotX = ballspotXX;
          balladdress = 1;
          if(ballspotY > 0)//nohittop
          {
            if(ballspotXX == 7)
            {
              erase_ball(0,ballspotY+1,0);
            }
            delay(delaytimeball);
            erase_ball(ballspotX,ballspotY,balladdress);
            ballspotY--;
            ballspotX++;
            ballspotXX++;
            lc.setLed(balladdress,ballspotY,ballspotX,true);
          }
          else //hittop
          {
            balldirectionup = false;
          }
        }
      }
      else //hitrightside
      {
        balldirectionright = false; //turnleft
      }
    }
    else //left
    {
      if(ballspotXX > 1) // nothitleftside
      {
        if(ballspotXX - 1 >=8 && ballspotXX + 1<=15) //balladdress0
        {
          ballspotX = ballspotXX - 8;
          balladdress = 0;
          if(ballspotY > 0) //nothittop
          {
            if(ballspotXX == 8)
            {
              erase_ball(7,ballspotY+1,1);
            }
            delay(delaytimeball);
            erase_ball(ballspotX,ballspotY,balladdress);
            ballspotY--;
            ballspotX--;
            ballspotXX--;
            lc.setLed(balladdress,ballspotY,ballspotX,true);
          }
          else//hittop
          {
            balldirectionup = false;//godown
          }
        }
        else //balladdress1;
        {
          ballspotX = ballspotXX;
          balladdress = 1;
          if(ballspotY > 0) //nohittop
          {
            if(ballspotXX == 7)
            {
              erase_ball(0,ballspotY+1,0);
            }
            delay(delaytimeball);
            erase_ball(ballspotX,ballspotY,balladdress);
            ballspotY--;
            ballspotX--;
            ballspotXX--;
            lc.setLed(balladdress,ballspotY,ballspotX,true);
          }
          else//hittop
          {
            balldirectionup = false; //godown
          }
        } 
      }
      else //hitleftside
      {
        balldirectionright = true;//turnright
      }
    }
  }
  else //down
  {
    if(balldirectionright == true) //downright
    {
      if(ballspotXX < 14)//nohitright
      {
        if(ballspotXX + 1 >= 8 && ballspotXX + 1 <= 14) //balladdress0
        {
            ballspotX = ballspotXX - 8;
            balladdress = 0;
            if(ballspotY < 7) //nohitbottom
            {
              if(ballspotXX == 8)
              {
                erase_ball(7,ballspotY-1,1);
              }
              delay(delaytimeball);
              erase_ball(ballspotX,ballspotY,balladdress);
              ballspotY++;
              ballspotX++;
              ballspotXX++;
              lc.setLed(balladdress,ballspotY,ballspotX,true);
            }
            else //hitbottom
            {
                balldirectionup = true; //goup
            }
        }
        else //balladdress1
        {
            ballspotX = ballspotXX;
            balladdress = 1;
            if(ballspotY < 7)//nohitbottom
            {
              if(ballspotXX == 7)
              {
                erase_ball(0,ballspotY-1,0);
              }
                delay(delaytimeball);
                erase_ball(ballspotX,ballspotY,balladdress);
                ballspotY++;
                ballspotX++;
                ballspotXX++;
                lc.setLed(balladdress,ballspotY,ballspotX,true);
            }
            else //hitbottom
            {
                balldirectionup = true; //goup
            }
        }
      }
      else //hitrightside
      {
        balldirectionright = false; //turnleft
      }
    }
    else //downleft
    {
      if(ballspotXX > 1)//nohitleft
      {
        if(ballspotXX == 7 && ballspotY == 7)
          {
            erase_ball(0,6,0);
          }
          if(ballspotXX - 1 >= 8 && ballspotXX + 1 <= 15)//balladdress0
          {
              ballspotX = ballspotXX-8;
              balladdress = 0;
              if(ballspotY < 7)//nohittbottom
              {
                if(ballspotXX == 8)
                {
                  erase_ball(7,ballspotY-1,1);
                }
                delay(delaytimeball);
                erase_ball(ballspotX,ballspotY,balladdress);
                ballspotY++;
                ballspotX--;
                ballspotXX--;
                lc.setLed(balladdress,ballspotY,ballspotX,true);
              }
              else//hitbottom
              {
                  balldirectionup = true;//goup
              }
          }
          else //balladdress1
          {
            ballspotX = ballspotXX;
            balladdress = 1;
            if(ballspotY < 7) //nohitbottom
            {
              if(ballspotXX == 7)
              {
                erase_ball(0,ballspotY-1,0);
              }
              delay(delaytimeball);
              erase_ball(ballspotX,ballspotY,balladdress);
              ballspotY++;
              ballspotX--;
              ballspotXX--;
              lc.setLed(balladdress,ballspotY,ballspotX,true);
            }
            else //hitbottom
            {
                balldirectionup = true; //goup
            }
          }
      }
      else //hitleft
      {
        balldirectionright = true; //turnright
      }
    }
  }
}

void check_collision(int barspot1,int barspot2, int barspot3)
{
  
}
