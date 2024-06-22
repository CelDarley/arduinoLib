
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
int botao = 13;

const char* ssid = "Marcela24";
const char* password = "Lolina2501";

//Your Domain name with URL path or IP address with path

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 1000;

void setup() {
  
  Serial.begin(115200); 
  pinMode(botao, INPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      String serverName = "http://192.168.0.49:8000/api/fluxo/";
      String serverPath = serverName + "";
          int estado = digitalRead(botao);
          Serial.println(estado);
         // if(estado==1){
            String sensor = "1";
            String litros="34";
             http.begin(client, serverPath.c_str());
             http.addHeader("Content-Type", "application/json");
             String httpRequestData = "{\"sensor\":\"" + sensor + "\",\"litros\":\"" + litros + "\"}"; 
             int httpResponseCode = http.POST(httpRequestData);
             if (httpResponseCode>0) {
              Serial.print("HTTP Response code: ");
              Serial.println(httpResponseCode);
              String payload = http.getString();
              Serial.println(payload);
             // http.begin(client, serverPath.c_str());
             // httpResponseCode = http.POST();
            }
            else {
              Serial.print("Error code: ");
              Serial.println(httpResponseCode);
            }
            // Free resources
            http.end();
      //    }
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
