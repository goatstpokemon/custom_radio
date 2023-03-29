#ifndef ROUTES_H
#define ROUTES_H
#include <HTTPClient.h>
#include <Arduino.h>
#include <WiFi.h>
class Routes{
  private: 
    HTTPClient http;
    // const String baseURL = "https://radio.lukedixon.nl/api/";
    const String baseURL = "http://192.168.45.209/IPMEDT5_dashboard/public/api/";
    String request(String url);
  public:
    String AllStations();
    String AllCountryStations(const char* country_id);
    String AllGenreStations(const char* country_id);
    String GetRadioInfo();
    String GetRandomRadio();
    String PutRadioInfo(const char* stationID);
    String GetAllCountries();
    String GetCountryById(const char* countryId);
    String GetFavorites(const char* user_id);
    String PostNewFavorite(const char* user_id, const char* favorite_id);
    String DeleteFavorite(const char* user_id, const char* favorite_id);
    String GetSettings(const char* user_id); 
    String UpdateVolume(const char* user_id, int volume);
};

#endif