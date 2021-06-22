//============================================
//ESP8266 Web Server (HTML + CSS + JavaScript)
//============================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "webpage.h";
//------------------------------------------
ESP8266WebServer server(80);
//WiFiServer server(80);
const char* ssid = "RANSIKA";
const char* password = "RWIFI1234";
const char* xml ="<?xml version = \"1.0\" ?><inputs><LED>checked</LED><LED>on</LED><analog>5</analog></inputs>";
//------------------------------------------
void XML()
{
  server.send(200,"text/XML",xml);
}
void webpage()
{
  server.send(200,"text/html", webpageCode);
  location();
  XML_response();

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void location() { //Handler for the body path
      if (server.hasArg("country")== false){ //Check if body received
            //server.send(200, "text/plain", "Body not received");
            return;
      }
 
      String message = "Body received:\n";
             message += server.arg("country");
             message += "\n";
 
      //server.send(200, "text/plain", message);
      Serial.println("Country"+message);
      return;
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
  server.on("/xml",XML);
  server.begin();
}
//=================================================================
void loop()
{
  server.handleClient();
  //location();
}

void XML_response()
{
    float analog_val=1.0;            // stores value read from analog inputs
    int count;                 // used by 'for' loops
    boolean LED_state[2] = {0};
    Serial.print("<?xml version = \"1.0\" ?>");
    Serial.print("<inputs>");
    // checkbox LED states
    // LED1
    Serial.print("<LED>");
    if (LED_state[0]) {
        Serial.print("checked");
    }
    else {
        Serial.print("unchecked");
    }
    Serial.println("</LED>");
    // button LED states
    // LED3
    Serial.print("<LED>");
    if (LED_state[1]) {
        Serial.print("on");
    }
    else {
        Serial.print("off");
    }
    Serial.println("</LED>");
    
    analog_val = 20;
    Serial.print("<analog>");
    Serial.print(analog_val);
    Serial.print("</analog>");
    Serial.print("</inputs>");
}
