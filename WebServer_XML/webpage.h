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
        #btn
        {
          display: inline;
          text-decoration: none;
          background: red;
          color:rgba(0, 0, 255, 0.7);
          font: 30px calibri;
          box-shadow: 0px 0px 3px 5px #000000;
          border: solid 2px rgba(39, 194, 78, 0.9);
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
    <form action="/location" method="GET">
        <label for="city">City:</label><label id="city_name">None</label><br>
        <input type="text" id="city" name="City"><br>
        <label for="country">Country:</label><label id="country_name">None</label><br>
        <input type="text" id="country" name="Country"><br><br>
        <input type="submit" value="Submit">
      </form>
    </div><br>
    <div class="details">
        <label>Temperature:</label><label id="temp">None</label><br>
        <label>Humidity:</label><label id="temp">None</label><br>
        <label>Weather:</label><label id="temp">None</label><br> 
    </div>

    <h3>Operating Mode</h3><br>

    <div class="mode">
        <button method="post"id="btn" name="Auto" ONCLICK='JS1()'>AUTO</button>
        <button method="post"id="btn" ONCLICK='JS1()'>MANUAL</button>
    </div>
<!---------------------------JavaScript------------------------------->
<script>
    document.addEventListener('DOMContentLoaded', ()=>{
            //fetch the data as soon as the page has loaded
            let url = "/xml";
            fetch(url)
            .then(response=>response.text())
            .then(data=>{
                console.log("trying to get xml");
                //console.log(data);  //string
                let parser = new DOMParser();
                let xml = parser.parseFromString(data, "application/xml");
                //document.getElementById('output').textContent = data;
                console.log(xml);
                country = xml.getElementsByTagName('loc')[0].childNodes[0].innerHTML
                city=xml.getElementsByTagName('loc')[0].childNodes[1].innerHTML
                document.getElementById("country_name").innerHTML = country;
                document.getElementById("city_name").innerHTML = city;
                console.log(country)
            });
        })



    //function displays text message
    let m1 = 'JavaScript is an object-oriented language'
    let m2 = ' that creates interactive effects within web browsers.'
    let m3 = ' The code syntax of JavaScript is similar to C++.'
    function JS1()
    {
      alert(m1 + m2 + m3);
      console.log("yesyasd");
      const xhttp = new XMLHttpRequest();
      xhttp.open("POST", "/method", true);
    xhttp.send("Auto");
    console.log(xhttp);
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
							//document.getElementById("input3").innerHTML =
								//this.responseXML.getElementsByTagName('analog')[0].childNodes[0].nodeValue;
								//data_val = this.responseXML.getElementsByTagName('analog')[0].childNodes[0].nodeValue;
							// XML file received - contains analog values, switch values and LED states
							var count;
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