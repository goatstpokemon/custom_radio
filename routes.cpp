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
      
      return request(baseURL + "stations");
    }

    // Retrieve all radio stations from one country
    String Routes::AllCountryStations(const int country_id) {      
      return request(baseURL + "stations?country=" + country_id);
    }

    

    // Retrieve data of a station
    String Routes::GetRadioInfo() {      
      String payload;
        payload = request(baseURL + "stations/discover");
        JSONVar output = JSON.parse(payload);
        String name = output["data"]["output"];
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

    // Get all countries
    String Routes::GetAllCountries() {      
      return request(baseURL + "countries");
    }

    // Get country by countryId
    String Routes::GetCountryById(const int countryId) {      
      return request(baseURL + "countries/" + countryId);
    }

    // Get all favorites
    String Routes::GetFavorites(const int user_id) {      
      return request(baseURL + "users/" + user_id + "/favorites");
    }

    // Add favorite to database
    String Routes::PostNewFavorite(const int user_id, const int station_id) {
      http.begin(baseURL + "users/" + user_id + "/favorites");
      String payload = "station=";
      payload.concat(station_id);
      int httpCode = http.POST(payload);
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          return http.getString();
        }
      }
      return "Error";
    }

    // Delete favorite from database
    String Routes::DeleteFavorite(const int user_id, const int favorite_id) {
      http.begin(baseURL + "users/" + user_id + "/favorites/" + favorite_id);
      int httpCode = http.sendRequest("DELETE");
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          return http.getString();
        }
      }
      return "Error";
    }

    // Get all settings for a user
    String Routes::GetSettings(const int user_id) {
      
      return request(baseURL + "users/" + user_id + "/settings");
    }
    // PUT /api/users/{user_id}/settings?volume={volume}
    // Update the volume
    String Routes::UpdateVolume(const int user_id, const int volume) {
      http.begin(baseURL + "users/" +  user_id  + "/settings");      
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String payload = "volume=";
      payload.concat(volume); 

      Serial.println(payload); 
      int httpCode = http.PUT(payload);
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          Serial.println(http.getString());
          return http.getString();
        }
      }
      Serial.println("ik ben hier");
      return "Error";
    }

