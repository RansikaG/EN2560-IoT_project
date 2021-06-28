//============================================
//ESP8266 Web Server (HTML + CSS + JavaScript)
//============================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "webpage.h";


#define Valve D4

const long utcOffsetInSeconds = 19800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//------------------------------------------
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);
const char* ssid = "SLT-4G-3F4C";
const char* password = "5HJ39M13JDM";

const char* mqtt_server = "test.mosquitto.org";
const char* outTopic = "ENTC/EN2560/out/180241M";
const char* inTopic = "ENTC/EN2560/in/180241M";

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int H=0;

int n=0;
String temperature="90";
String locset="True";
String country="Sri Lanka";
String city="Colombo";
String country_nodered="None";
String city_nodered="None";
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
            Auto(temp,humidity,weather,H);
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

void Auto(String temp,String humidity, String weather, int H){
Serial.println("Auto");
String mode="AUTO";
if (weather=="rain" ||weather=="shower rain"|| weather=="thunderstorm"){
    //we don't have to water
    delay(100);
  }

  else{
    unsigned long On_time=temp.toFloat()/10*6e4 + (100-humidity.toFloat())/10*6e4;
    //int h=H.toInt();
    if (9<H<10 || 16<H<17){
      unsigned long C_time = millis();
      unsigned long N_time = C_time;
      while (N_time>C_time+On_time){
        digitalWrite(Valve,HIGH);
        N_time = millis();
      }
      digitalWrite(Valve,LOW);
      delay(1000);
      ESP.deepSleep(3600e6);
    }
  }
server.send(200,"text/plain","Set to Auto");

}

void Manual(){
Serial.println("Manual");
digitalWrite(Valve,HIGH);
delay(300e3);
digitalWrite(Valve,LOW);
server.send(200,"text/plain","Set to Manual");
String mode="MANUAL";
ESP.deepSleep(3600e6);
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Reg_sleep(int H,int M){             // This function check the local time if it is not close to the watering time, ESP will goto a 5 Mins deep sleep.
  
  //int h=H.toInt();
  //int m=M.toInt();

  if (not(9<H<10 || 16<H<17)){
    ESP.deepSleep(300e6);
  }
  else if (not(50<M<60)){
    ESP.deepSleep(300e6);
  }
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

  timeClient.update();                            // This function gets the local time of the NodeMCU. This should run frequently
    int H=timeClient.getHours();
    int M=timeClient.getMinutes();
    int S=timeClient.getSeconds();
}
