#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Blynk.h>
#include "ESP8266WiFi.h"
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <SimpleTimer.h>

#define BLYNK_PRINT Serial
#define REPORTING_PERIOD_MS 1000
#define DHTTYPE DHT11
#define dht_dpin 14
DHT dht(dht_dpin, DHTTYPE); 
SimpleTimer timer;

char auth[] = "ZmydeN3e0sCTTTAmVz_2P10S2PEXlxSO";             // You should get Auth Token in the Blynk App.
char ssid[] = "Effordea.com";                                     // Your WiFi credentials.
char pass[] = "gr@bApep$!";
float t;                                   // Declare the variables 
float h;

// Connections : SCL PIN - D1 , SDA PIN - D2 , INT PIN - D0
PulseOximeter pox;

float BPM, SpO2;
uint32_t tsLastReport = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(16, OUTPUT);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(2000, sendUptime);
    Serial.print("Initializing Pulse Oximeter..");

    if (!pox.begin())
    {
         Serial.println("FAILED");
         for(;;);
    }
    else
    {
         Serial.println("SUCCESS");
//        pox.setOnBeatDetectedCallback(onBeatDetected);
    }

    // The default current for the IR LED is 50mA and it could be changed by uncommenting the following line.
     //pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

}

void sendUptime()
{
  
}

void loop()
{
    pox.update();
    Blynk.run();
    timer.run();

    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        Serial.print("Heart rate:");
        Serial.print(BPM);
        Serial.print(" bpm / SpO2:");
        Serial.print(SpO2);
        Serial.println(" %");

        Blynk.virtualWrite(V7, BPM);
        Blynk.virtualWrite(V8, SpO2);

        tsLastReport = millis();
    }
}
