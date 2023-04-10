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

char* ssid =     "";
char* password = "";

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
    getVolume = route.GetSettings(1);
    JSONVar volumeRaw = JSON.parse(getVolume);
    String nameRaw = volumeRaw["data"]["output"];  
    Serial.println("nameRaw: " );
    Serial.print(nameRaw);
    mp3.begin();
    //  mp3.loadUserCode(); // FLAC plugin
    mp3.setVolume(volume);
    
     String payload = route.GetRandomRadio();   
     
    
     
     
     
     Serial.print("name: " );
     Serial.println(payload );
     if(payload){
       mp3.connecttohost(payload);
     }
          
    //  int stationId = output["data"]["id"];
    //  Serial.print("Station ID: ");
    //  Serial.println(stationId);
    //  route.PutRadioInfo(stationId);
     
     

     //serial2.print()
     
    // mp3.connecttohost("https://stream.slam.nl/web10_mp3");                 // mp3 192kb/s
    
}

// The loop function is called in an endless loop
void loop()
{
  
     mp3.loop();
  //  route.UpdateVolume(1, 7);
    Serial2.println(Serial.readString());
  // delay(5000);
}


  
  


// next code is optional:
void vs1053_showstation(const char *info){          // called from vs1053
    Serial.println("STATION:      ");
    Serial.println(info);                           // Show station name
    Serial2.write("STATION:       ");
    Serial2.write(info);
}
void vs1053_showstreamtitle(const char *info){      // called from vs1053
    Serial.print("STREAMTITLE:  ");
    Serial.println(info);                           // Show title
    Serial2.write("STREAMTITLE:       ");
    Serial2.write(info);
    
}
void vs1053_showstreaminfo(const char *info){       // called from vs1053
    Serial.print("STREAMINFO:   ");
    Serial.println(info);                           // Show streaminfo
    Serial2.write("STREAMINFO:       ");
    Serial2.write(info);
}
