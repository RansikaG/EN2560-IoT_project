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
          position: relative;
          display: inline;
          text-decoration: none;
          background: rgb(0, 255, 13);
          color:rgba(0, 0, 255, 0.7);
          font: 30px calibri;
          box-shadow: 0px 0px 3px 5px #000000;
          border: solid 2px rgba(21, 92, 134, 0.9);
          cursor: pointer;}
        
        #btn_M{
            background: rgb(0, 255, 13);
            position:relative;
            left: 18%;
            top:-20%
        }

        #location_btn{
            background: rgb(144, 150, 155);
            position:relative;
            left: 40%;
            top:-20%;
        }
        
        body {font-family: "Calibri"; background-color: grey}
        h1   {color: rgb(62, 161, 207); text-align:center; font-size: 50px;}
        h2   {color: rgb(185, 97, 236); text-align:center; font-size: 30px;}
        h3   {color: rgb(185, 97, 236); text-align:center; font-size: 30px;}
        .container {
        width: 50px;
        clear: both;
        margin: auto;
        position: relative;
        width: 25%;
        border: 3px solid #090a07;
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
        border: solid 2px rgba(18, 28, 34, 0.9);
        width: 200px;
        clear: both;
        margin: auto;
        height: 100px;
        padding: 10px;
        }

        #autolabel{
            font-family: "Lucida Console", monospace;
            font-size: 45px;
        }

        .switch {
        position:relative;
        left:70%;
        top: -40%;
        display: inline-block;
        width: 60px;
        height: 34px;
        }

        .switch input { 
        opacity: 0;
        width: 0;
        height: 0;
        }

        .slider {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: #ccc;
        -webkit-transition: .4s;
        transition: .4s;
        }

        .slider:before {
        position: absolute;
        content: "";
        height: 26px;
        width: 26px;
        left: 4px;
        bottom: 4px;
        background-color: white;
        -webkit-transition: .4s;
        transition: .4s;
        }

        input:checked + .slider {
        background-color: #2196F3;
        }

        input:focus + .slider {
        box-shadow: 0 0 1px #2196F3;
        }

        input:checked + .slider:before {
        -webkit-transform: translateX(26px);
        -ms-transform: translateX(26px);
        transform: translateX(26px);
        }

        /* Rounded sliders */
        .slider.round {
        border-radius: 34px;
        }

        .slider.round:before {
        border-radius: 50%;
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
        <button type="button" id="location_btn" name="Submit" onclick="send_form_data()">SET</button>
      </form>
    </div><br>
    <div class="details">
        <label>Temperature:</label><label id="temp">None</label><br>
        <label>Humidity:</label><label id="humidity">None</label><br>
        <label>Weather:</label><label id="weather">None</label><br> 
    </div>

    <h3>Operating Mode</h3><br>

    <div class="mode">
    <div id="autolabel">Auto </div>
        <label class="switch">
            <input type="checkbox" id="toggle" aria-checked="false" onclick="JS2();">
            <span class="slider round"></span>
          </label><br>
        <button class=btn id="btn_M"  name="Manual" ONCLICK=' manual()' >MANUAL</button>
    </div>
<!---------------------------JavaScript------------------------------->
<script>
    window.setInterval(refresh,30000)
    document.addEventListener('DOMContentLoaded',refresh);
    //document.addEventListener('DOMContentLoaded',auto);
    document.addEventListener('DOMContentLoaded',JS2);//set to auto
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
        document.getElementById("btn_M").style.borderColor = "white";
        const xhttp = new XMLHttpRequest();
        xhttp.onload = function(){
            console.log(this.responseText);
        };
        xhttp.open("GET", "/method?Auto=true&Manual=false");
        xhttp.send();
    }
    function manual() {
        console.log("manual watering");
        const xhttp = new XMLHttpRequest();
        xhttp.onload = function(){
            console.log(this.responseText);
        };
        xhttp.open("GET", "/method?Auto=false&Manual=true");
        xhttp.send();
    }
    //function prompts for name, then displays message
    function JS2(checkbox)
    {
        if(document.getElementById("toggle").checked){
            document.getElementById("btn_M").disabled = true;//In auto
            auto();
            console.log("Auto enabled");
        }
        else{
            document.getElementById("btn_M").disabled = false;
            document.getElementById("btn_M").style.borderColor = "red";
            manual();
            console.log("Manual enabled");
        }
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