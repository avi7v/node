#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial       
#include <BlynkSimpleEsp8266.h>
char auth[] = "RWKIdiOaHVLjC_ROeNDiW6B-j0z7rJRA";

/* WiFi credentials */
char ssid[] = "Saiguru";
char pass[] = "guru2008";

/* HC-SR501 Motion Detector */
#define pirPin D4                // Input for HC-S501
#define led D7                   // led pin D7 
const int buzzer = D8;           // buzzer pin D8 
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
    pinMode(pirPin, INPUT);
    pinMode(led,LOW);
    pinMode(buzzer, OUTPUT);
  }

void loop()
  {
     if (pinValue == HIGH)    
      {
        getPirValue();
        pinMode(led,HIGH);
          tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
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
