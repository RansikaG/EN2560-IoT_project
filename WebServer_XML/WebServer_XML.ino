//============================================
//ESP8266 Web Server (HTML + CSS + JavaScript)
//============================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include "webpage.h";
//------------------------------------------
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);
const char* ssid = "RANSIKA";
const char* password = "RWIFI1234";

const char* mqtt_server = "test.mosquitto.org";
const char* outTopic = "ENTC/EN2560/out/180241M";
const char* inTopic = "ENTC/EN2560/in/180241M";

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

int n=0;
String temperature="90";
String locset="True";
String country="Sri Lanka";
String city="Colombo";
String country_nodered="SSSS";
String city_nodered="SSDDDd";
String temp="30";
String humidity="150";
String weather="Sunny";

String mode="AUTO";
//-----------MQTT functions---------------------------

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void callback(char* topic, byte* payload, unsigned int length) {
  String weatherDetails = "";
  for (int i = 0; i < length; i++) {
    weatherDetails += (char)payload[i];
  }
    temp = getValue(weatherDetails, ',', 0);
    humidity = getValue(weatherDetails, ',', 1);
    weather = getValue(weatherDetails, ',', 2);
    city_nodered = getValue(weatherDetails, ',', 3);
    country_nodered=getValue(weatherDetails, ',', 4);
    Serial.println("temp"+temp);
    //Serial.println("location"+location);
    char msgr[30]="got it";
    Serial.println(msgr);
    XML();
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
  //    client.publish(outTopic, "hello world");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//------------------------------------------
void XML()
{
  
  city="Colombo"+String(n);
  String xml="<?xml version = \"1.0\" ?><inputs><locset>"+locset+"</locset><loc><country>"+country_nodered+"</country><city>"+city_nodered+"</city></loc><sys><temp>"+temp+"</temp><humidity>"+humidity+"</humidity><weather>"+weather+"</weather></sys><mode>"+mode+"</mode></inputs>";
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
    if (server.arg("Auto")=="true"&&server.arg("Manual")=="false"){
            Auto();
            return;
      }
    else if (server.arg("Auto")=="false"&&server.arg("Manual")=="true"){ 
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
    String locdetails="{\"city\":\""+city+"\",\"country\":\""+country+"\"}" ;
    Serial.println(locdetails);
    locdetails.toCharArray(msg,locdetails.length()+1);
    Serial.println(msg);
    client.publish(outTopic,msg);
    Serial.println("Location set to"+country+" "+city);
    server.send(200,"text/plain","Location set to"+country+" "+city);
    return;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=++++++
//=================================================================
void setup()
{
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);   
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED){delay(500);Serial.print(".");}
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  server.on("/", webpage);
  server.on("/method", method);
  server.on("/xml",XML);
  server.on("/location", location);
  server.begin();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
//=================================================================
void loop()
{
  server.handleClient();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
