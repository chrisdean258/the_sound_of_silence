const int ledPin=12;
TZ_adjust = 5.5; d = $(date + % s); t = $(echo "60*60*$TZ_adjust/1" | bc); echo T$(echo $d + $t | bc ) > / dev / ttyACM0
#include<Time.h>

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  
}
void loop() 
{
  int sensorValue = analogRead(A0);

  Serial.println(sensorValue);
  delay(500);
  
  if(sensorValue==1023)
  {
     Serial.print(month());
     Serial.print("/");
     Serial.print(day());
     Serial.print("/");
     Serial.print(year();
     
  }/*
  else
  {
     digitalWrite(ledPin,LOW);
  }*/
  
}

