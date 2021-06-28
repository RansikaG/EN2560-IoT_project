

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
// Update these with values suitable for your network.

#define Valve D4

const char* ssid = "SLT-4G-3F4C";
const char* password = "5HJ39M13JDM";

const long utcOffsetInSeconds = 19800;
const char* mqtt_server = "test.mosquitto.org";
const char* outTopic = "ENTC/EN2560/out/180241M";
const char* inTopic = "ENTC/EN2560/in/180241M";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;


// **************** Yasod's Part ******************************************************************************//

void Auto(float temp,float hum, String Stat, int H){            //Automatically watering for 5 minutes in between 9-10am and 4-5pm

  if (weather=="rain" ||weather=="shower rain"|| weather=="thunderstorm"||weather=="snow"||weather=="mist"){
    //we don't have to water
    delay(100);
  }

  else{
    unsigned long On_time=temp/10*6e4 + (100-hum)/10*6e4;
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
  

  
}

void Manual(bool Button){                   // We pess the button on the mobile application. This Global variable should update atleast at 0.1Hz frequency
  if(Button){
    digitalWrite(Valve,HIGH);
    delay(300e3);
  }
  digitalWrite(Valve,LOW);
  ESP.deepSleep(3600e6);
}


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


//***************************####################################************************************************************



void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

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

float tempc;
float humidity;
String weather;
String detail;
String location;
String Time;
void callback(char* topic, byte* payload, unsigned int length) {
  String weatherDetails = "";
  for (int i = 0; i < length; i++) {
    weatherDetails += (char)payload[i];
  }
//    Serial.print(weatherDetails);
//    Serial.println();

    String tem = getValue(weatherDetails, ',', 0);
    tempc = tem.toFloat();
    String hum = getValue(weatherDetails, ',', 1);
    humidity = hum.toFloat();
    weather = getValue(weatherDetails, ',', 2);
    detail = getValue(weatherDetails, ',', 3);
    location = getValue(weatherDetails, ',', 4);

    
    //Time=H_.totring()+":"++":"+;
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

void setup() {
  // Initialize the BUILTIN_LED pin as an output
  pinMode(BUILTIN_LED, OUTPUT);     
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  timeClient.update();                            // This function gets the local time of the NodeMCU. This should run frequently
    int H=timeClient.getHours();
    int M=timeClient.getMinutes();
    int S=timeClient.getSeconds();
    //Serial.print(H);
    //Serial.print(M);
    //Serial.print(S);
    //Serial.println();
  
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    if (Serial.available()){
      char msg[30];
      String text = Serial.readString();
      Serial.print("Publish message: ");
      Serial.println(text);
      int i=0;
      for (i = 0; i < text.length()-1; i++){
        msg[i] = text[i];
      }
      client.publish(outTopic, msg);
    }
  }
}
