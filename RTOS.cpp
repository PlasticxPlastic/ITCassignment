#include <Arduino_FreeRTOS.h>
#include "queue.h"

const int ledr = 5;
const int ledy = 6;
const int ledg = 7;

const int btr = 8;
const int bty = 11;
const int btg = 12;


long ledrtime = 0;
long ledgtime = 0;

float delaybtg;

int pressedbty = 0;
int pressedbtg = 0;

QueueHandle_t ledQueue;

void setup()
{
  Serial.begin(9600);
  ledQueue =  xQueueCreate(6, sizeof(int32_t)); 

  xTaskCreate(Sender, "Sender Task btr", 128, btr, 1, NULL);
  xTaskCreate(Sender, "Sender Task bty", 128, bty, 1, NULL);
  xTaskCreate(Sender, "Sender Task btg", 128, btg, 1, NULL);
  xTaskCreate(Receiver, "Receiver Task ledr", 128, ledr, 1, NULL);
  xTaskCreate(Receiver, "Receiver Task ledy", 128, ledy, 1, NULL);
  xTaskCreate(Receiver, "Receiver Task ledg", 128, ledg, 1, NULL);
}

void Sender(void *pvParameters)
{
  int32_t valueToSend = 0;
  int BT = (int32_t)pvParameters;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(BT, INPUT_PULLUP);
  
  while (1)
  {
    if (digitalRead(BT) == HIGH) 
      valueToSend = BT;
    else
      valueToSend = 0;

    if (valueToSend)
    {
      xQueueSend(ledQueue, &valueToSend, xTicksToWait);
      vTaskDelay(20);
      if( BT == btg )
      {
        delaybtg = millis();
        while(millis() - delaybtg < 3000);
      }
    }
  }
}
void Receiver(void *pvParameters)
{
  int32_t valueReceived;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  int LED = (int32_t)pvParameters;

  pinMode(ledr, OUTPUT); 
  digitalWrite(ledr, LOW); 
  pinMode(ledy, OUTPUT);
  digitalWrite(ledy, LOW); 
  pinMode(ledg, OUTPUT);
  digitalWrite(ledg, LOW); 

  int pressedby = 0;
  int pressedbg = 0;
  long ledrtime = 0;
  long ledgtime = 0;
  while (1)
  {
    qStatus = xQueueReceive(ledQueue, &valueReceived, xTicksToWait);
    if (qStatus  == pdPASS)
    {
      if (valueReceived == btr && LED == ledr)
      {
        digitalWrite(ledr, HIGH);
        ledrtime = millis();
        while(millis()-ledrtime < 3000);
        digitalWrite(ledr, LOW);
      }
      else if (valueReceived == bty && LED == ledy)
      {
        pressedbty = !pressedbty;
      }
      
       else if ( valueReceived == btg && LED == ledg )
      {
        
        pressedbtg = 1;
        ledgtime = millis();
        digitalWrite(ledg, HIGH);
        while(millis() - ledgtime  < 500);
            ledgtime = millis();
            digitalWrite(ledg, LOW);
        while(millis() - ledgtime < 500);
            ledgtime = millis();
            digitalWrite(ledg, HIGH);
        while(millis() - ledgtime < 500);
            ledgtime = millis();
            digitalWrite(ledg, LOW);
        while(millis() - ledgtime < 500);
            ledgtime = millis();
            digitalWrite(ledg, HIGH);
        while(millis() - ledgtime < 500);
            ledgtime = millis();
            digitalWrite(ledg, LOW);
        while(millis() - ledgtime < 500);
            pressedbtg = 0;
      }
      else if (valueReceived == btg|| pressedbtg == 0 )
      {
        int32_t valueToSend = valueReceived;
        xQueueSend(ledQueue, &valueToSend, xTicksToWait);
        vTaskDelay(1); 
      }
    }
    if (pressedbty && LED == ledy)
      {
      digitalWrite(ledy, HIGH);
      vTaskDelay(10);
      digitalWrite(ledy, LOW);
      vTaskDelay(10);
      }
    }
  }


void loop() {}
