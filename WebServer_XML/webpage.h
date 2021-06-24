//=========================================
//HTML + CSS + JavaScript codes for webpage
//=========================================
const char webpageCode[] =
R"=====(
<!DOCTYPE html>
<html>
<!------------------------------C S S--------------------------------->
<head>
    <style>
        .btn
        {
          display: inline;
          text-decoration: none;
          background: rgb(0, 255, 13);
          color:rgba(0, 0, 255, 0.7);
          font: 30px calibri;
          box-shadow: 0px 0px 3px 5px #000000;
          border: solid 2px rgba(21, 92, 134, 0.9);
          cursor: pointer;
        }
        body {font-family: "Calibri"; background-color: grey}
        h1   {color: rgb(62, 161, 207); text-align:center; font-size: 50px;}
        h2   {color: rgb(185, 97, 236); text-align:center; font-size: 30px;}
        h3   {color: rgb(185, 97, 236); text-align:center; font-size: 30px;}
        .container {
        width: 50px;
        clear: both;
        margin: auto;
        width: 25%;
        border: 3px solid #73AD21;
        padding: 10px;
        background-color: rgb(55, 141, 170);
                    }
        .container input {
        width: 100%;
        margin: auto;
        clear: both;
        
        }

        .details {
        width: 50px;
        clear: both;
        margin: auto;
        width: 25%;
        border: 3px solid #73AD21;
        padding: 10px;
        background-color: rgb(68, 175, 77);
                    }
           
        body {
        background-image: url('https://www.attractionsinsrilanka.com/wp-content/uploads/2020/02/Gampaha-Botanical-Garden-1.jpg');
        background-repeat: no-repeat;
        background-attachment: fixed;
        background-size: cover;
        }

        .mode{
        width: 50px;
        clear: both;
        margin: auto;
        width: 25%;
        padding: 10px;
        }

    </style>
</head>
<!----------------------------H T M L--------------------------------->
<body>
    <h1 id="title">Garden Watering System</h1>
    
    <h2>
    Setup the location below
    </h2>
    <div class="container">
    <form id="myform">
        <label for="city">City:</label><label id="city_name">None</label><br>
        <input type="text" id="city" ><br>
        <label for="country">Country:</label><label id="country_name">None</label><br>
        <input type="text" id="country"><br><br>
        <button type="button" name="Submit" onclick="send_form_data()">SET</button>
      </form>
    </div><br>
    <div class="details">
        <label>Temperature:</label><label id="temp">None</label><br>
        <label>Humidity:</label><label id="humidity">None</label><br>
        <label>Weather:</label><label id="weather">None</label><br> 
    </div>

    <h3>Operating Mode</h3><br>

    <div class="mode">
        <button class=btn id="btn_A" name="Auto" ONCLICK=' auto()'>AUTO</button>
        <button class=btn id="btn_M" name="Manual" ONCLICK=' manual()'>MANUAL</button>
    </div>
<!---------------------------JavaScript------------------------------->
<script>
    window.setInterval(refresh,30000)
    document.addEventListener('DOMContentLoaded',refresh);
            //fetch the data as soon as the page has loaded
            //setInterval(refresh,2000)
    function send_form_data(){
        console.log("form data bn");
        let city=document.getElementById("city").value;
        let country=document.getElementById("country").value;
        const xhttp = new XMLHttpRequest();
        xhttp.onload = function(){
        response=this.responseText;
        console.log(response);
        };
        xhttp.open("GET","/location?city="+city+"&country="+country);
        xhttp.send();
        console.log("location data sent");
    }

    
    function refresh(){
        const xhttp = new XMLHttpRequest();
        let xml; 
        xhttp.onload = function(){
        xml=this.responseXML;
        //console.log(this.responseXML);
        country = xml.getElementsByTagName('loc')[0].childNodes[0].innerHTML;
        city=xml.getElementsByTagName('loc')[0].childNodes[1].innerHTML;
        temp = xml.getElementsByTagName('sys')[0].childNodes[0].innerHTML;
        humidity = xml.getElementsByTagName('sys')[0].childNodes[1].innerHTML;
        weather = xml.getElementsByTagName('sys')[0].childNodes[2].innerHTML;

        document.getElementById("country_name").innerHTML = country;
        document.getElementById("city_name").innerHTML = city;
        document.getElementById("temp").innerHTML = temp;
        document.getElementById("humidity").innerHTML = humidity;
        document.getElementById("weather").innerHTML = weather;

        };
        xhttp.open("GET", "/xml");
        xhttp.send();
        //console.log("trying to get xml");
    }
   

    //function displays text message
    let m1 = 'JavaScript is an object-oriented language';

    function JS1()
    {
      alert(m1);
      console.log("recieved");
    }

    function auto() {
        document.getElementById("btn_A").style.borderColor = "red";
        document.getElementById("btn_M").style.borderColor = "white";
        document.getElementById("btn_A").disabled = true;
        document.getElementById("btn_M").disabled = false;
        const xhttp = new XMLHttpRequest();
        xhttp.onload = function(){
            console.log(this.responseText);
        };
        xhttp.open("GET", "/method?Auto=true&Manual=false");
        xhttp.send();
    }
    function manual() {
        document.getElementById("btn_A").style.borderColor = "white";
        document.getElementById("btn_M").style.borderColor = "red";
        document.getElementById("btn_A").disabled = false;
        document.getElementById("btn_M").disabled = true;
        const xhttp = new XMLHttpRequest();
        xhttp.onload = function(){
            console.log(this.responseText);
        };
        xhttp.open("GET", "/method?Auto=false&Manual=true");
        xhttp.send();
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
    function GetArduinoIO()
		{
			//nocache = "&nocache=" + Math.random() * 1000000;
			var request = new XMLHttpRequest();
			request.onreadystatechange = function()
			{
				if (this.readyState == 4) {
					if (this.status == 200) {
						if (this.responseXML != null) {

							// LED 2
							if (this.responseXML.getElementsByTagName('LED')[1].childNodes[0].nodeValue === "on") {
								document.getElementById("city").innerHTML = "ON";
								document.getElementById("city").style.color = "green";
								//LED2_state = 1;
							}
							else {
								document.getElementById("country").innerHTML = "OFF";
								document.getElementById("country").style.color = "red";
								//LED2_state = 0;
							}
						}
					}
				}
			}
        }

        
    
</script>
</body>
</html>
)=====";