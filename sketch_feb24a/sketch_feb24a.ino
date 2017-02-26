const int ledPin=12;
void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}
void loop() 
{
  int sensorValue = analogRead(A0); 
  
  Serial.println(sensorValue);
  Serial.println("hi");
  //pauses every 1/4 second
  delay(250);
  
  if(sensorValue==1023)
  {
     digitalWrite(ledPin,HIGH);
  }
  else
  {
     digitalWrite(ledPin,LOW);
  }
  
}
