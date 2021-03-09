/*************************************************************
visit for this project https://nhjamali.blogspot.com/2021/03/patient-telemetry-monitoring-system.html
visit https://nhjamali.blogspot.com/ for more projects
App project setup:
    Value Display widget attached to V7
    Value Display widget attached to V8
 *************************************************************/
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <MAX30100_PulseOximeter.h>

char auth[] = "YourAuthToken";              // You should get Auth Token in the Blynk App. Go to the Project Settings (nut icon).
char ssid[] = "YourNetworkName";            // Your WiFi credentials.
char pass[] = "YourPassword";               // Set password to "" for open networks.

PulseOximeter pox;
BlynkTimer timer;

// This function sends ESP8266's up time every second to Virtual Pin (7).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float BPM = pox.getHeartRate();
  float SpO2 = pox.getSpO2();
  
  if (!pox.begin())
    {
         Serial.println("FAILED to connect with Pulse-Oximeter MAX30100");
         for(;;);
    }
    else
    {
         Serial.println("Successfully connected to sensor");
    }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V7, BPM);
  Blynk.virtualWrite(V8, SpO2);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  pox.update();
}
