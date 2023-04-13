#include <Arduino_JSON.h>


#include <WiFi.h>
#include "Arduino.h"
#include <SPI.h>
#include "vs1053_ext.h"
#include "wifiman.h"
#include "routes.h"
// Digital I/O used
#define VS1053_CS      2
#define VS1053_DCS     4
#define VS1053_DREQ   36

#define VS1053_MOSI   23
#define VS1053_MISO   19
#define VS1053_SCK    18

char* ssid =     "NS_Business";
char* password = "Hello112?";

#define RXp2 16
#define TXp2 17
String payload;

int volume=7;

VS1053 mp3(VS1053_CS, VS1053_DCS, VS1053_DREQ, VSPI, VS1053_MOSI, VS1053_MISO, VS1053_SCK);
Routes route;
String getVolume;

//The setup function is called once at startup of the sketch
void setup() {
    Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
    Serial.begin(115200);
    
    Serial.println("Serial Txd is on pin: "+String(TX));
    Serial.println("Serial Rxd is on pin: "+String(RX));
    SPI.begin();
    //SD.begin();

    
    
    WiFi.disconnect();
    WifiScanner();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    
    
    while (WiFi.status() != WL_CONNECTED) delay(1500);
    Serial.print("Connected To:");
    Serial.println(ssid);
    // getVolume = route.GetSettings(1);
    // JSONVar volumeRaw = JSON.parse(getVolume);
    // String nameRaw = volumeRaw["data"]["output"];  
    // Serial.println("nameRaw: " );
    // Serial.print(nameRaw);
    mp3.begin();
    mp3.setVolume(volume);    
    // String payload = route.GetRadioInfo();   
    String payload = route.AllStations();   
     JSONVar getRadioInfo = JSON.parse(payload);
    String radioRawName = getRadioInfo["data"][0]["output"];  
    String radioId = getRadioInfo["data"]["id"];
    Serial.print("payload");
    Serial.println(payload);
     Serial.print("Radio Naam: " );
     Serial.println(radioRawName );
     Serial.print("Radio id: " );
     Serial.println(radioId );
     
     
     
     
    //  Serial.print("name: " );
    //  Serial.println(payload );
    //  if(payload){
    //    mp3.connecttohost(payload);
    //  }
          
    //  int stationId = output["data"]["id"];
    //  Serial.print("Station ID: ");
    //  Serial.println(stationId);
    //  route.PutRadioInfo(stationId);
     
     

     Serial2.write("yoooo");
     
    mp3.connecttohost("https://stream.slam.nl/web10_mp3");                 // mp3 192kb/s
    
}

// The loop function is called in an endless loop
void loop()
{
    // Serial2.write("yoooo");
    //  mp3.loop();
    //  route.UpdateVolume(1, 7);
    Serial2.println(Serial.readString());
  Serial.println("sent");
  Serial2.write("STATION: ");
  Serial2.write(info);
  delay(2000);
  // Serial.print("STATION: ");
  // Serial.println("hfa;eohohewgwgoh");
}


  
  
// STATION        STATIONAAM
//  StationRaw = Station
// verwijder alle spaties 
// verwijder eerste 7

// next code is optional:
void vs1053_showstation(const char *info){          // called from vs1053
    Serial.println("STATION:      ");
    Serial.println(info);                           // Show station name
    Serial2.write("STATION: ");
    Serial2.write(info);
}
void vs1053_showstreamtitle(const char *info){      // called from vs1053
    Serial.print("STREAMTITLE: ");
    Serial.println(info);                           // Show title
    Serial2.write("STREAMTITLE: ");
    Serial2.write(info);
    
}
void vs1053_showstreaminfo(const char *info){       // called from vs1053
    // Serial.print("STREAMINFO:   ");
    // Serial.println(info);                           // Show streaminfo
    Serial2.write("STREAMINFO: ");
    Serial2.write(info);
}
