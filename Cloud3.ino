#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// WiFi Parameters
const char* ssid = "Mortimer";
const char* password = "GizzmoIsFat";

//Arduino pin that strip is connected to.
#define PIN 5

//How many neoPixels needed:
#define NUMPIXELS 30

// How many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Blink Rate
int blinkRate = 1000;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  //Initialize neoPixel Library
  pixels.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=denver&appid=313405d34b97486aa16312fb902874fe");
    int httpCode = http.GET();
    //Check the returning code
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      Serial.println(payload);

      // Parsing
     const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 270;
DynamicJsonDocument doc(capacity);

const char* json = "{\"coord\":{\"lon\":-104.98,\"lat\":39.74},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"clear sky\",\"icon\":\"01d\"}],\"base\":\"stations\",\"main\":{\"temp\":292.05,\"feels_like\":288.67,\"temp_min\":290.93,\"temp_max\":293.15,\"pressure\":1022,\"humidity\":13},\"wind\":{\"speed\":0.45,\"deg\":38,\"gust\":2.68},\"clouds\":{\"all\":0},\"dt\":1588186843,\"sys\":{\"type\":3,\"id\":2004334,\"country\":\"US\",\"sunrise\":1588161726,\"sunset\":1588211522},\"timezone\":-21600,\"id\":5419384,\"name\":\"Denver\",\"cod\":200}";

deserializeJson(doc, json);

float coord_lon = doc["coord"]["lon"]; // -104.98
float coord_lat = doc["coord"]["lat"]; // 39.74

JsonObject weather_0 = doc["weather"][0];
int weather_0_id = weather_0["id"]; // 800
const char* weather_0_main = weather_0["main"]; // "Clear"
const char* weatherMain = weather_0["description"]; // "clear sky"
const char* weather_0_icon = weather_0["icon"]; // "01d"

const char* base = doc["base"]; // "stations"

JsonObject main = doc["main"];
float main_temp = main["temp"]; // 292.05
float main_feels_like = main["feels_like"]; // 288.67
float main_temp_min = main["temp_min"]; // 290.93
float main_temp_max = main["temp_max"]; // 293.15
int main_pressure = main["pressure"]; // 1022
int main_humidity = main["humidity"]; // 13

JsonObject wind = doc["wind"];
float wind_speed = wind["speed"]; // 0.45
int wind_deg = wind["deg"]; // 38
float wind_gust = wind["gust"]; // 2.68

int clouds_all = doc["clouds"]["all"]; // 0

long dt = doc["dt"]; // 1588186843

JsonObject sys = doc["sys"];
int sys_type = sys["type"]; // 3
long sys_id = sys["id"]; // 2004334
const char* sys_country = sys["country"]; // "US"
long sys_sunrise = sys["sunrise"]; // 1588161726
long sys_sunset = sys["sunset"]; // 1588211522

int timezone = doc["timezone"]; // -21600
long id = doc["id"]; // 5419384
const char* name = doc["name"]; // "Denver"
int cod = doc["cod"]; // 200

      Serial.print("current weather in ");
      Serial.print(name);
      Serial.print(" is ");
      Serial.println(weatherMain);

      //Close connection
  
  
  if(weatherMain = "clear"){
    for (int i =0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(0,200,255));
  }
  pixels.show();
}
 http.end();
 delay(60000);
 }
}
}
