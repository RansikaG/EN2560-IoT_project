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
String temperature="90";
//String xml ="<?xml version = \"1.0\" ?><inputs><LED>checked</LED><LED>on</LED><analog>"+temperature+"</analog></inputs>";
String locset="True";
String country="Sri Lanka";
String city="Colombo";
String temp="30";
String humidity="150";
String status="ON";
String mode="AUTO";
//------------------------------------------
void XML()
{
  String xml="<?xml version = \"1.0\" ?><inputs><locset>"+locset+"</locset><loc><country>"+country+"</country><city>"+city+"</city></loc><sys><temp>"+temp+"</temp><humidity>"+humidity+"</humidity><status>"+status+"</status></sys><mode>"+mode+"</mode></inputs>";
  server.send(200,"text/XML",xml);
}
void webpage()
{
  server.send(200,"text/html", webpageCode);
  //XML_response();

}
void method(){
  if (server.hasArg("Auto")==true){ //Check if body received
            //server.send(200, "text/plain", "Body not received");
            Auto();
      }
  return;
}

void Auto(){
Serial.println("Auto");
}

void Manual(){
Serial.println("Manual");
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
  server.on("/method", method);
  server.on("/xml",XML);
  server.on("/location", Auto);
  server.begin();
}
//=================================================================
void loop()
{
  server.handleClient();
  //location();
}
