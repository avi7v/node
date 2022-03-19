#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

char auth[] = "BvvnZAgvZWjmsLKJaDZrgkYIeEXf9FAw";
char ssid[] = "Saiguru";
char pass[] = "guru2008";

#define pirPin D8
int pirValue;                   // Place to store read PIR Value
int pinValue;                   //Variable to read virtual pin

BLYNK_WRITE(V0)
{
 pinValue = param.asInt();    
} 

void setup()

{
    Serial.begin(115200);
    delay(10);
  Blynk.begin(auth, ssid, pass);
  servo.attach(2); // NodeMCU D4 pin
  pinMode(pirPin, INPUT);
 }
void loop()
{
       if (pinValue == HIGH)    
      {
        getPirValue();
      }
  Blynk.run();
}
void getPirValue(void)        //Get PIR Data
  {
   pirValue = digitalRead(pirPin);
    if (pirValue) 
     { 
       Serial.println("Motion detected");
       Blynk.notify("Motion detected");  
     }
  }
BLYNK_WRITE(V1)
{
   servo.write(param.asInt());
}
BLYNK_WRITE(V2)
{
  servo.write(0);
}
BLYNK_WRITE(V3)
{
  servo.write(150);
}
