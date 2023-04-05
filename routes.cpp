#include <HTTPClient.h>
#include <Arduino.h>
#include <WiFi.h>
#include "routes.h"



    
    String Routes::request(String url) {
      
      http.begin(url);
      int httpCode = http.GET();
     http.addHeader("Content-Type", "audio/x-mpegurl");
     http.addHeader("Set-Cookie", "__cf_bm=LRKywEzgZAhQpcjCyFJULpciGHYX0bsJrbk7DVOAipk-1680684134-0-ATeg8tnV0/dZq62qpAcWJHoRuwCkJekGfBPeaIXgfFaw/lXPxSbyak+3yCQ7VDqmO6lhgU5LLRgAGUNDz+/3Wyw=; path=/; expires=Wed, 05-Apr-23 09:12:14 GMT; domain=.radiotime.com; HttpOnly; SameSite=None");
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          
          return http.getString();
        }
      }
      return String(httpCode) + "Error" ;
    }


    // Retrieve all radio stations
    String Routes::AllStations() {
      
      return request(baseURL + "stations");
    }

    // Retrieve all radio stations from one country
    String Routes::AllCountryStations(const char* country_id) {      
      return request(baseURL + "stations?country=" + country_id);
    }

    // Retrieve all radio stations from one genre
    String Routes::AllGenreStations(const char* genre_id) {
      return request(baseURL + "stations?genre=" + genre_id);
    }

    // Retrieve data of a station
    String Routes::GetRadioInfo() {      
      return request(baseURL + "stations?playing=true");
    }

    // Retrieve data of a station
    String Routes::GetRandomRadio() {      
      return request(baseURL + "stations/discover");
    }

    // Send data to front-end about currently playing station
    String Routes::PutRadioInfo(const char* stationID) {
      http.begin(baseURL + "stations/" + stationID);
      int httpCode = http.PUT("playing=true");
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
    String Routes::GetCountryById(const char* countryId) {      
      return request(baseURL + "countries/" + countryId);
    }

    // Get all favorites
    String Routes::GetFavorites(const char* user_id) {      
      return request(baseURL + "users/" + user_id + "/favorites");
    }

    // Add favorite to database
    String Routes::PostNewFavorite(const char* user_id, const char* station_id) {
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
    String Routes::DeleteFavorite(const char* user_id, const char* favorite_id) {
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
    String Routes::GetSettings(const char* user_id) {
      
      return request(baseURL + "users/" + user_id + "/settings");
    }
    // PUT /api/users/{user_id}/settings?volume={volume}
    // Update the volume
    String Routes::UpdateVolume(const char* user_id, int volume) {
      http.begin(baseURL + user_id );
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String payload = "?volume=";
      payload.concat(volume);    
      int httpCode = http.POST(payload);
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          return http.getString();
        }
      }
      return "Error";
    }

