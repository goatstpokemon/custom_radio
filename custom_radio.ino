#include "Arduino.h"
#include <SPI.h>
#include <WiFi.h>
#include "vs1053_ext.h"
#include "wifiman.ino"
// Digital I/O used
#define VS1053_CS      2
#define VS1053_DCS     4
#define VS1053_DREQ   36

#define VS1053_MOSI   23
#define VS1053_MISO   19
#define VS1053_SCK    18

String ssid =     "thenoonoo";
String password = "XnpcVQeuutaA";

int volume=5;

VS1053 mp3(VS1053_CS, VS1053_DCS, VS1053_DREQ, VSPI, VS1053_MOSI, VS1053_MISO, VS1053_SCK);

//The setup function is called once at startup of the sketch
void setup() {

    Serial.begin(115200);
    SPI.begin();
    //SD.begin();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) delay(1500);
    mp3.begin();
    //  mp3.loadUserCode(); // FLAC plugin
    mp3.setVolume(volume);
    // mp3.connecttohost("https://22663.live.streamtheworld.com/SKYRADIO.mp3?dist=tunein&DIST=TuneIn&TGT=TuneIn&maxServers=2&partnertok=eyJhbGciOiJIUzI1NiIsImtpZCI6InR1bmVpbiIsInR5cCI6IkpXVCJ9.eyJ0cnVzdGVkX3BhcnRuZXIiOnRydWUsImlhdCI6MTY3OTE2NTI1NSwiaXNzIjoidGlzcnYifQ.T_c4W8eLF3DcTAAycNzJa78vlgqVM9tesZD0XzIlu9o");
    mp3.connecttohost("https://stream.slam.nl/slam");                 // mp3 192kb/s
 
}

// The loop function is called in an endless loop
void loop()
{
    mp3.loop();
}

// next code is optional:
void vs1053_showstation(const char *info){          // called from vs1053
    Serial.print("STATION:      ");
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
