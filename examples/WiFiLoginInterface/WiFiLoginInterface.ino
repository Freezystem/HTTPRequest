#include <Arduino.h>
#include <WiFi101.h>

#include "WiSer.h"
#include "arduino_secret.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int availableSSID = -1;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Access Point Web Server");

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  availableSSID = WiFi.scanNetworks();
  
  Serial.println("Creating access point named: " + String(ssid));

  status = WiFi.beginAP(ssid, pass);
  if (status == WL_AP_FAILED) {
    Serial.println("Creating access point failed");
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();
}

void loop() {
  if (status != WiFi.status()) {
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      Serial.println("Device connected to AP");
    } 
    else {
      Serial.println("Device disconnected from AP");
      availableSSID = WiFi.scanNetworks();
    }
  }
  
  WiFiClient client = server.available();
  
  if (client) {
    WiSerAPRequest req = WiSerAPRequest(client);
    
    req.catchRequest(callback);

    // close the connection:
    client.stop();
  }
}

void callback(WiSerAPRequest& req) {
  Serial.print(String("\nmethod:" + WiSerHelpers::methodToString(req.getMethod()) + "\n"));
  WiFiClient& client = req.getClient();
  WiSerAPResponse res = WiSerAPResponse(client);
    
  switch(req.getMethod()) {
    case HttpMethod::GET : {
      String content = "<!doctype html>"
                       "<html>"
                         "<head>"
                           "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, shrink-to-fit=no\">"
                           "<title>WiFi Login Interface</title>"
                         "</head>"
                         "<body>"
                           "<form method=\"POST\" action=\"/\">"
                             "<p>Enter your Wifi SSID and password</p>"
                             "<input type=\"text\" name=\"ssid\" placeholder=\"SSID\" required/>"
                             "<br/><input type=\"password\" name=\"password\" placeholder=\"password\"/><br/>"
                             "<input type=\"submit\" value=\"submit\"/>"
                           "</form>"
                         "</body>"
                       "</html>";
      
      res.setStatus(HttpCode::OK)
         .setHeader("Content-type", "text/html")
         .setHeader("Connection", "close")
         .setContent(content)
         .send();
      break;
    }
    case HttpMethod::POST : {
      String content = "<!doctype html>"
                       "<html>"
                         "<head>"
                           "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, shrink-to-fit=no\">"
                           "<title>WiFi Login Interface</title>"
                         "</head>"
                         "<body>"
                           "<p>Login, Please wait...</p>"
                         "</body>"
                       "</html>";
      
      res.setStatus(HttpCode::OK)
         .setHeader("Content-type", "text/html")
         .setHeader("Connection", "close")
         .setContent(content)
         .send();
      break;
    }
  }
}
