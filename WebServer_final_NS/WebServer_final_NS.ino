//=====================================================
//EN2560 - IoT - Group 05 (180195A / 180205H / 180241M)
//=====================================================
//==================================================
//ESP8266 Web Server (C++ + HTML + CSS + JavaScript)
//==================================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include "webpage.h";
using namespace std;

#define Valve D4


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org",0);

String utcOffsetInSeconds_s;
int utcOffsetInSeconds=0;
int H;
int M;
int S;
int Time;
bool FLAG_loop=false;

int Starting_time;
int Current_time;
int RST_count=0;

bool awake=true;


//------------------------------------------
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);
const char* ssid = "SLT-4G-3F4C";
const char* password = "5HJ39M13JDM";
//const char* ssid = "RANSIKA";
//const char* password = "RWIFI1234";

const char* mqtt_server = "test.mosquitto.org";
const char* outTopic = "ENTC/EN2560/out/180241M";
const char* inTopic = "ENTC/EN2560/in/180241M";


unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

String temperature="0";
String locset="True";
String country="None";
String city="None";
String country_nodered="None";
String city_nodered="None";
String temp="0";
String humidity="0";
String weather="None";

bool flag=true;
String mode="AUTO";



//-----------MQTT functions---------------------------                              // Feed from the NodeRed is seperated in to different variables

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

void callback(char* topic, byte* payload, unsigned int length) {                     // Take the incomming MQTT Messages and update NodeMCU global variables
  String weatherDetails = "";
  for (int i = 0; i < length; i++) {
    weatherDetails += (char)payload[i];
  }
    temp = getValue(weatherDetails, ',', 0);
    humidity = getValue(weatherDetails, ',', 1);
    weather = getValue(weatherDetails, ',', 2);
    city_nodered = getValue(weatherDetails, ',', 3);
    country_nodered=getValue(weatherDetails, ',', 4);
    utcOffsetInSeconds_s=getValue(weatherDetails, ',', 5);
    utcOffsetInSeconds=utcOffsetInSeconds_s.toInt();
  
    char msgr[30]="MQTT receievd";
    //Serial.println(msgr);
    XML();
}


void reconnect() {                                                                  // Reconnect to the MQTT server when the connection is lost
  // Loop until we're reconnected
  
  while ((!client.connected()) && awake) {
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
void XML()                                                                        // Send data to the web page in XML format
{
  String xml="<?xml version = \"1.0\" ?><inputs><locset>"+locset+"</locset><loc><country>"+country_nodered+"</country><city>"+city_nodered+"</city><utcoffset>"+utcOffsetInSeconds_s+"</utcoffset></loc><sys><temp>"+temp+"</temp><humidity>"+humidity+"</humidity><weather>"+weather+"</weather></sys><mode>"+mode+"</mode></inputs>";
  server.send(200,"text/XML",xml);
  Serial.println("xml sent");
}
void webpage()                                                                   // Refresh the web page
{
  server.send(200,"text/html", webpageCode);

}
void method(){                                                                   // Change the watering Mode (Auto/Manula). Desided by the button on the web page
    Serial.println("method invoked");
    if (server.arg("Auto")=="true"&&server.arg("Manual")=="false"){
            mode="AUTO";
            server.send(200,"text/plain","Set to Auto");
            return;
      }
    else if (server.arg("Auto")=="false"&&server.arg("Manual")=="true"){ 
            mode="MANUAL";
            if(server.arg("mwatering")=="true"){
            Manual();
            }
            else if (server.arg("mwatering")=="false")
            {
            Serial.println("Manual enabled");
            server.send(200,"text/plain","Manual watering enabled");
            }
            
            return;
      }
    else{
      return;
    }

}

void awake_confirm(){                                                         // Check whether the NodeMCU is awake
  server.send(200,"text/plain","true");
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void Auto(String temp,String humidity, String weather, int H){                                 // Automatical watering for a calculated time depend of Temperature and the Humidity
//Serial.println("Auto");
String mode="AUTO";

if (weather=="rain" ||weather=="shower rain"|| weather=="thunderstorm"){
    //we don't have to water
    delay(100);
  }
  else{
    
    unsigned long On_time=temp.toFloat()/10*6e4 + (100-humidity.toFloat())/50*6e4;
    //int h=H.toInt();
    //Serial.println(H);
    if ((9<=H && H<10) || (16<=H && H<17)){
      if (flag){
        
        Serial.println(On_time);
        digitalWrite(Valve,HIGH);
        Serial.println("Auto Watering Happening");
        delay(On_time/4);
        digitalWrite(Valve,LOW);
        Serial.println("Auto Watering stopped****************************************");
        delay(1000);
        flag=false;
      }
      
    }
    else{
        flag=true;

    }
    
  }
}

void Manual(){                                                                                    // Manual wetering
  digitalWrite(Valve,HIGH);
  Serial.println("Manual Watering Happening");
  delay(30e3);
  Serial.println("Manual Watering stopped****************************************");
  digitalWrite(Valve,LOW);
  server.send(200,"text/plain","Manual watering happened");
  //ESP.deepSleep(3600e6);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void light_sleep(){                                                                             // NodeMCU sleep for 3 minutes. (3 min awake/ 3 min sleep)
  awake=false;
   wifi_station_disconnect();
   wifi_set_opmode_current(NULL_MODE);
   wifi_fpm_set_sleep_type(LIGHT_SLEEP_T); // set sleep type, the above    posters wifi_set_sleep_type() didnt seem to work for me although it did let me compile and upload with no errors 
   wifi_fpm_open(); // Enables force sleep
   delay(100);
   gpio_pin_wakeup_enable(GPIO_ID_PIN(0), GPIO_PIN_INTR_LOLEVEL);
   wifi_fpm_do_sleep(180e3); // Sleep for longest possible time
   Serial.println("going to wifi sleep");
 }

 void initWifi() {                                                                            // Reinitializing WiFi connectivity after awaking
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED){delay(500);Serial.print(".");}
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  server.on("/", webpage);
  server.on("/method", method);
  server.on("/xml",XML);
  server.on("/location", location);
  server.on("/wake",awake_confirm);
  server.begin();
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 }


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void location() { //Handler for the body path                                                // Send the collected location details from the web page, to the NodeRed. This fuction act as a middle man.
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


//=================================================================
void setup()
{
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(D0,HIGH);
  pinMode(Valve, OUTPUT);  
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED){delay(500);Serial.print(".");}
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  server.on("/", webpage);
  server.on("/method", method);
  server.on("/xml",XML);
  server.on("/location", location);
  server.on("/wake",awake_confirm);
  server.begin();

  //Starting_time=millis();
  
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
  
  
  timeClient.update();// This function gets the local time of the NodeMCU using the NTP server.
    H=timeClient.getHours();
    M=timeClient.getMinutes();
    S=timeClient.getSeconds();
    Time=H*3600+M*60+S;
    Time=Time+utcOffsetInSeconds;
    
    H= floor(Time/3600);
    Time=Time%3600;
    M=floor(Time/60);
    S=Time%60;

    /*Serial.print(H);
    Serial.print(" : ");
    Serial.print(M);
    Serial.print(" : ");
    Serial.println(S);*/
    
  if (mode=="AUTO"){                                     // Automatical Process
    
    //Current_time=millis();
    if (M==3 && S==0){
      FLAG_loop=true;
      light_sleep();
      delay(100);
      RST_count=0;
        
    }
    else if (FLAG_loop && (M-3)%6==0 && S==0){         // Auto function deepsleep
      light_sleep();
      delay(100);
      RST_count=0;
    }
    else if(FLAG_loop && M%6==0 && RST_count==0){
        initWifi();
        awake=true;
        Serial.println("AWAKE and Making connections");
        RST_count=RST_count+1;
      
    }
    
    Auto(temp,humidity,weather,H);
    
  }


}
