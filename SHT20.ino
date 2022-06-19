/*
modified on Apr 10, 2021
Modified by MehranMaleki from Arduino Examples
Home
*/

#include <Wire.h>
#include "DFRobot_SHT20.h"
#include <RH_RF95.h>
#include <SPI.h>



DFRobot_SHT20 sht20;

#define RF95_FREQ 434.0
int hum;
int temp;
RH_RF95 rf95;
void setup()
{
    Serial.begin(9600);
    Serial.println("SHT20 Example!");
    sht20.initSHT20();                         // Init SHT20 Sensor
    delay(4000);
    sht20.checkSHT20();    // Check SHT20 Sensor
    if (!rf95.init())
    Serial.println("init failed");
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  rf95.setTxPower(1000); //Transmission power of the Lora Module
}

void loop()
{
     hum = sht20.readHumidity();         // Read Humidity
     temp = sht20.readTemperature();      // Read Temperature
    
    Serial.print(" Temperature: ");
    Serial.print(temp, 1);
    Serial.print("C");
    Serial.print("\t Humidity: ");
    Serial.print(hum, 1);
    Serial.println("%");
    String humidity = String(hum); //int to String
    String temperature = String(temp);
    String data = temperature + humidity;
    //String t = "20";
    //String h = "80";
    String data1 = String(temp)+String(hum);
    //String data2="20919191345655554456653567888";
    Serial.print(data);
    
    char d[5];
    data1.toCharArray(d, 5); //String to char array
    Serial.println("Sending to rf95_server");
    rf95.send(d, sizeof(d));
    rf95.waitPacketSent();
    delay(4000);
}
