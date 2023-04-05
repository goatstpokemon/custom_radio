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
String payload;

int volume=5;

VS1053 mp3(VS1053_CS, VS1053_DCS, VS1053_DREQ, VSPI, VS1053_MOSI, VS1053_MISO, VS1053_SCK);
Routes route;


//The setup function is called once at startup of the sketch
void setup() {
    
    Serial.begin(115200);
    SPI.begin();
    //SD.begin();
    
    WiFi.disconnect();
    WifiScanner();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    
    
    while (WiFi.status() != WL_CONNECTED) delay(1500);
    Serial.print("Connected To:");
    Serial.println(ssid);
    mp3.begin();
    //  mp3.loadUserCode(); // FLAC plugin
    mp3.setVolume(volume);
    
    //  String payload = route.GetAllCountries();   
     
    
    //  JSONVar output = JSON.parse(payload);
    //  String name = output["data"][1]["name"];
    //  Serial.print("payload: " );
    //  Serial.println(payload );
    //  Serial.print("output: " );
    //  Serial.println(name );
     mp3.connecttohost("http://opml.radiotime.com/Tune.ashx?id=s251199");
    // mp3.connecttohost("https://stream.slam.nl/web10_mp3");                 // mp3 192kb/s
    
}

// The loop function is called in an endless loop
void loop()
{
  
    mp3.loop();
   
  
  // delay(2000);
}


  
  


// next code is optional:
void vs1053_showstation(const char *info){          // called from vs1053
    Serial.println("STATION:      ");
    Serial.println(info);                           // Show station name
}
void vs1053_showstreamtitle(const char *info){      // called from vs1053
    Serial.print("STREAMTITLE:  ");
    Serial.println(info);                           // Show title
}
void vs1053_showstreaminfo(const char *info){       // called from vs1053
    Serial.print("STREAMINFO:   ");
    Serial.println(info);                           // Show streaminfo
}
