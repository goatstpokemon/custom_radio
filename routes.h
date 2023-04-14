#ifndef ROUTES_H
#define ROUTES_H
#include <HTTPClient.h>
#include <Arduino.h>
#include <WiFi.h>
class Routes{
  private: 
    HTTPClient http;    
    const String baseURL = "http://192.168.27.31/api/";

    String request(String url);
  public:
    String AllStations();
    String AllCountryStations(const int country_id);  
    String GetRadioInfo(const int stationID);
    String GetPlayingStation();
    String GetRandomRadio();
    String PutRadioInfo(const int stationID);
    String GetAllCountries();
    String GetCountryById(const int countryId);
    String GetFavorites(const int user_id);
    String PostNewFavorite(const int user_id, const int favorite_id);
    String DeleteFavorite(const int user_id, const int favorite_id);
    int GetSettings(const int user_id); 
    String UpdateVolume(const int user_id, const int volume);
};

#endif