//============================================
//ESP8266 Web Server (HTML + CSS + JavaScript)
//============================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "webpage.h";
//------------------------------------------
ESP8266WebServer server(80);
const char* ssid = "RANSIKA";
const char* password = "RWIFI1234";
//------------------------------------------
void webpage()
{
  server.send(200,"text/html", webpageCode);
  location();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void location() { //Handler for the body path
      if (server.hasArg("country")== false){ //Check if body received
 
            server.send(200, "text/plain", "Body not received");
            return;
 
      }
 
      String message = "Body received:\n";
             message += server.arg("country");
             message += "\n";
 
      server.send(200, "text/plain", message);
      Serial.println(message);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=++++++
//=================================================================
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED){delay(500);Serial.print(".");}
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  server.on("/", webpage);
  //server.on("/location",location);
  server.begin();
}
//=================================================================
void loop()
{
  server.handleClient();
  
}
