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
int n=0;
String temperature="90";
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
  
  city="Colombo"+String(n);
  String xml="<?xml version = \"1.0\" ?><inputs><locset>"+locset+"</locset><loc><country>"+country+"</country><city>"+city+"</city></loc><sys><temp>"+temp+"</temp><humidity>"+humidity+"</humidity><status>"+status+"</status></sys><mode>"+mode+"</mode></inputs>";
  server.send(200,"text/XML",xml);
  Serial.println("xml sent");
  n=n+1;
}
void webpage()
{
  server.send(200,"text/html", webpageCode);

}
void method(){
    Serial.println("method invoked");
    if (server.arg("Auto")=="true"){
            Auto();
            return;
      }
    else if (server.arg("Auto")=="true"){ 
            Manual();
            return;
      }
    else{
      return;
    }

}

void Auto(){
Serial.println("Auto");
server.send(200,"text/plain","Set to Auto");
String mode="AUTO";
}

void Manual(){
Serial.println("Manual");
server.send(200,"text/plain","Set to Manual");
String mode="MANUAL";
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void location() { //Handler for the body path
      if (server.hasArg("country")== false){ //Check if body received
            return;
      }
    city=server.arg("city");
    country=server.arg("country");
    Serial.println("Location set to"+country+" "+city);
    server.send(200,"text/plain","Location set to"+country+" "+city);
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
  server.on("/location", location);
  server.begin();
}
//=================================================================
void loop()
{
  server.handleClient();
}
