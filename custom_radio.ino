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


String payload;



VS1053 mp3(VS1053_CS, VS1053_DCS, VS1053_DREQ, VSPI, VS1053_MOSI, VS1053_MISO, VS1053_SCK);
Routes route;

int getVolume;
unsigned long previousMillis = 0;
const unsigned long interval = 20000;
String oldStation;

int oldVolume = 5;
JSONVar PlayingRadio;
int currentRadioId;
//The setup function is called once at startup of the sketch
void setup() {    
    Serial.begin(115200);    
    SPI.begin();   
    WiFi.disconnect();    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);    
    while (WiFi.status() != WL_CONNECTED) delay(1500);
    Serial.print("Connected To:");
    Serial.println(ssid);    
    mp3.begin();  
    
    mp3.setVolume(5);   
    String stationRaw = route.GetPlayingStation();
    PlayingRadio = JSON.parse(stationRaw);

    Serial.print("playing radio");
    Serial.println(PlayingRadio);    
    Serial.print("Listening To:");
    Serial.println(JSON.stringify(PlayingRadio["output"]));    
    mp3.connecttohost(JSON.stringify(PlayingRadio["output"]));   
    oldStation = JSON.stringify(PlayingRadio["output"]);            
            
}

// The loop function is called in an endless loop
void loop()
{    
  mp3.loop();  
   
   
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {  // check if the interval has elapsed
    previousMillis = currentMillis;  
    getVolume = route.GetSettings(1);
    if(oldVolume != getVolume){     
      mp3.setVolume(getVolume);
      oldVolume = getVolume; 
      Serial.println("Old Volume");
      Serial.println(oldVolume);
      Serial.println("Get Volume");
      Serial.println(getVolume);     
    }
    
     

    String stationRaw = route.GetPlayingStation();
    PlayingRadio = JSON.parse(stationRaw);
    String currentRadioURL = JSON.stringify(PlayingRadio["output"]);
    currentRadioId = PlayingRadio["id"];  
    String nowPlaying = PlayingRadio["now_playing"];
      Serial.println("Now Playing...");
      Serial.println(nowPlaying);
    if(currentRadioURL != oldStation){
      mp3.connecttohost(currentRadioURL);
       oldStation = currentRadioURL;     
       Serial.println("Old Station");
       Serial.println(oldStation);
       Serial.println("Get Station");
       Serial.println(currentRadioURL);
       }
  }
  
}

 


// next code is optional:
void vs1053_showstation(const char *info){          // called from vs1053
    Serial.println("STATION:      ");
    Serial.println(info);                           // Show station name

}
void vs1053_showstreamtitle(const char *info){      // called from vs1053
  String stationRaw = route.GetPlayingStation();
    PlayingRadio = JSON.parse(stationRaw);    
    currentRadioId = PlayingRadio["id"];
    Serial.print("STREAMTITLE: ");
    Serial.println(info);                           // Show title
    route.updateSong(currentRadioId, info);
    
}
void vs1053_showstreaminfo(const char *info){       // called from vs1053
    // Serial.print("STREAMINFO:   ");
    // Serial.println(info);                           // Show streaminfo
  
}
