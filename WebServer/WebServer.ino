//============================================
//ESP8266 Web Server (HTML + CSS + JavaScript)
//============================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//------------------------------------------
ESP8266WebServer server(80);
const char* ssid = "RANSIKA";
const char* password = "RWIFI1234";

const char webpageCode[] =
R"=====(
<!DOCTYPE html>
<html>
<!------------------------------C S S--------------------------------->
<head>
    <style>
        #btn
        {
          display: inline;
          text-decoration: none;
          background: red;
          color:rgba(0, 0, 255, 0.7);
          font: 80px calibri;
          border-radius: 50%;
          box-shadow: 0px 0px 10px 15px #000000;
          border: solid 10px rgba(255, 255, 0, 0.9);
          cursor: pointer;
        }
        body {font-family: "Calibri"; background-color: grey}
        h1   {color: whitesmoke; text-align:center; font-size: 50px;}
    </style>
</head>
<!----------------------------H T M L--------------------------------->
<body>
    <h1>
        ESP8266 Webpage <br> (HTML + CSS + JavaScript) <br><br>
        <a href="#" id="btn" ONCLICK='JS1()'>JS1</a> <br><br>
        <a href="#" id="btn" ONCLICK='JS2()'>JS2</a> <br><br>
        <a href="#" id="btn" ONCLICK='JS3()'>JS3</a>
    </h1>
    <form action="/" method="GET">
        <label for="city">City:</label><br>
        <input type="text" id="city" name="country"><br>
        <label for="country">Country:</label><br>
        <input type="text" id="country" name="city"><br><br>
        <input type="submit" value="Submit">
      </form>
<!---------------------------JavaScript------------------------------->
<script>
    //function displays text message
    let m1 = 'JavaScript is an object-oriented language'
    let m2 = ' that creates interactive effects within web browsers.'
    let m3 = ' The code syntax of JavaScript is similar to C++.'
    function JS1()
    {
      alert(m1 + m2 + m3);
    }
    //function prompts for name, then displays message
    function JS2()
    {
        let yourName;
        do
        {
            yourName = prompt("Who are you?");
        } while (!yourName);
        alert('Hello ' + yourName);
    }
    //function computes factorial of integer number
    function JS3()
    {
        let f = 1;
        let n = prompt('FACTORIAL\nEnter positive integer number: ');
        for(let i=1; i<=n; i++) f = f * i;
        alert('Factorial = ' + f);
    }   
</script>
</body>
</html>
)=====";
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
