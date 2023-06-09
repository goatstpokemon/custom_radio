#include <HTTPClient.h>
#include <Arduino.h>
#include <WiFi.h>
#include "routes.h"
#include <Arduino_JSON.h>


    
    String Routes::request(String url) {
      
      http.begin(url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          
          return http.getString();
        }
      }
      return "Error" + String(httpCode) ;
    }


    // Retrieve all radio stations
    String Routes::AllStations() {
      String payload;
      payload = request(baseURL + "stations");
      JSONVar getRadioInfo = JSON.parse(payload);
      String radioArr = JSON.stringify(getRadioInfo["data"]);
      return radioArr;
    }

   

    

    // Retrieve data of a station
    String Routes::GetRadioInfo(const int stationID) {      
      String payload;
      
        payload = request(baseURL + "stations/" + stationID);
        Serial.print(payload);
        JSONVar output = JSON.parse(payload);
        Serial.println("output");
        Serial.print(output);
        String name = output["data"]["output"];
        return name;
    }
    // Retrieve data of a station
    String Routes::GetPlayingStation() {      
      Serial.print("test");
        String payload;
        payload = request(baseURL + "stations?is_playing=1" );
       Serial.print(payload);
        JSONVar output = JSON.parse(payload); 
        Serial.println(output["data"][0]);
        String name = output["data"][0]["output"];
        
        return name;
    }

    // Retrieve data of a station
    String Routes::GetRandomRadio() {      
        String payload;
        payload = request(baseURL + "stations/discover");
        JSONVar output = JSON.parse(payload);

        String name = output["data"]["output"];
        return name;
    }

    // Send data to front-end about currently playing station
    String Routes::PutRadioInfo(const int stationID) {
      http.begin(baseURL + "stations/" + stationID);
      int httpCode = http.PUT("playing=1");
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          return http.getString();
        }
      }
      return "Error";
    }

    

    // Get all favorites
    String Routes::GetFavorites(const int user_id) {      
      String payload;
      payload = request(baseURL + "users/" + user_id + "/favourites");
      
      JSONVar parsedFavorites= JSON.parse(payload);
      String favoritesArr = JSON.stringify(parsedFavorites["data"]);
      return favoritesArr;
     
    }

    // Add favorite to database
    String Routes::PostNewFavorite(const int user_id, const int station_id) {
      http.begin(baseURL + "users/" + user_id + "/favourites");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String payload = "station=";
      payload.concat(station_id);
      payload.concat("favourite=");
      payload.concat(1);
      Serial.print(payload);
      int httpCode = http.PUT(payload);
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          Serial.print("Added favorite");
          return http.getString();
        }
      }
      return "Error toevoegen niet gelukt";
    }

    // Delete favorite from database
    String Routes::DeleteFavorite(const int user_id, const int favorite_id) {
      http.begin(baseURL + "users/" + user_id + "/favourites/" + favorite_id);
      int httpCode = http.sendRequest("DELETE");
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          return http.getString();
        }
      }
      return "Error verwijderen niet gelukt";
    }

    // Get all settings for a user
    int Routes::GetSettings(const int user_id) {      
      
        String payload;
        // String name;
        payload = request(baseURL + "users/" + user_id + "/settings");
        JSONVar output = JSON.parse(payload);
        int parsed = output["data"]["volume"];                  
        return parsed;
        
      
    }
    // PUT /api/users/{user_id}/settings?volume={volume}
    // Update the volume
    String Routes::UpdateVolume(const int user_id, const int volume) {
      http.begin(baseURL + "users/" +  user_id  + "/settings");      
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String payload = "volume=";
      payload.concat(volume); 

      Serial.println(payload); 
      int httpCode = http.POST(payload);
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          Serial.println(http.getString());
          return http.getString();
        }
      }
      Serial.println("ik ben hier");
      return "Error";
    }

