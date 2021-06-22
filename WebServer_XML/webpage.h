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
          font: 80px calibri;
          border-radius: 50%;
          box-shadow: 0px 0px 10px 15px #000000;
          border: solid 10px rgba(39, 194, 78, 0.9);
          cursor: pointer;
        }
        body {font-family: "Calibri"; background-color: grey}
        h1   {color: whitesmoke; text-align:center; font-size: 50px;}
    </style>
</head>
<!----------------------------H T M L--------------------------------->
<body onload="GetArduinoIO()">
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