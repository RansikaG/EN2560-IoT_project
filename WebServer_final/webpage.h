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
            background: rgb(34, 128, 235,0.5);
            position:relative;
            left: 18%;
            top:-15%;
            font-size: 30px;
            font-family: "Monaco", monospace;
            border-radius: 5px;
            color: rgb(228, 228, 228,0.5); 
            box-shadow: 7px 6px 28px 1px rgba(0, 0, 0, 0.24);
            cursor: pointer;
            outline: none;
            transition: 0.2s all;
        }
        #btn_M:active{
            transform: scale(0.98);
            /* Scaling button to 0.98 to its original size */
            box-shadow: 3px 2px 22px 1px rgba(0, 0, 0, 0.24);
            /* Lowering the shadow */
        }

        #location_btn{
            background: rgb(40, 116, 216,0.8);
            position:relative;
            left: 40%;
            top:-20%;
            font-size: 30px;
            font-family: "Monaco", monospace;
            border-radius: 10px;
        }
        
        body {font-family: "Calibri"; background-color: grey}
        h1   {color: rgb(62, 161, 207); text-align:center; 
        font-size: 50px;
        font-family: "Monaco", monospace;
        }
        h2   {
            color: rgb(228, 228, 228); 
            text-align:center; }
            
        h3   {color: rgb(241, 238, 241);
         text-align:center; 
         font-family: "Monaco", monospace;
        font-size: 45px;
        }
        .container {
        max-width: 400px;
        width: 85%;
        clear: both;
        margin: auto;
        position: relative;
        border-radius: 10px;
        border: 3px solid #090a07;
        padding: 10px;
        background-color: rgb(55, 141, 170);
                    }
        .container input {
        max-width: 380px;
        width: 90%;
        clear: both;
        margin: auto;
        border: 3px solid #196aa0;
        border-radius: 10px;
        padding: 10px;
        background-color: rgba(105, 185, 209, 0.849);
        font-family: "Monaco", monospace;
        font-size: 20px;
        }

        .details {
        max-width: 250px;
        width: 75%;
        clear: both;
        margin: auto;
        border: 3px solid #196aa0;
        border-radius: 10px;
        padding: 10px;
        background-color: rgba(105, 185, 209, 0.849);
                    }

        .attribute{
            font-family: "Helvetica", "Sans-serif";
            font-size: 20px;
            color: #11171ad8;
        }

        .data{
            font-family: "Helvetica", "Sans-serif";
            font-size: 20px;
            color: #11171ad8;
        }
           
        body {
        background-image: url('https://www.attractionsinsrilanka.com/wp-content/uploads/2020/02/Gampaha-Botanical-Garden-1.jpg');
        background-repeat: no-repeat;
        background-attachment: fixed;
        background-size: cover;
        background-blend-mode:color-burn;
        }

        .mode{
        border: none;
        width: 200px;
        clear: both;
        margin: auto;
        height: 100px;
        padding: 10px;
        }

        #autolabel{
            font-family: "Lucida Console", monospace;
            font-size: 45px;
            color: rgb(140, 247, 211);
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

        #clock {
        font-family: 'Orbitron', sans-serif;
        color: #d0dfd5;
        font-size: 50px;
        text-align: center;
        padding-top: 40px;
        padding-bottom: 40px;
        background-color: rgba(45, 116, 223, 0.4);
        width:250px;
        line-height: 15px;
        height: 15px;
        margin: auto;
        border: 3px solid #0b6088;
        border-radius: 5px;
        }

       .loclabel{
        font-family: "Helvetica", "Sans-serif";
        font-size: 20px;
        color: #11171ad8;
   
       }

       .locdata{
        font-family: "Helvetica", "Sans-serif";
        font-size: 20px;
        color: #c3d1d8d8;
       }


       #alert {
        padding: 20px;
        background-color: #1a9c25;
        color: white;
        opacity:0;
        display:block;
        transition: 1s ease opacity;
        }

        .closebtn {
        margin-left: 15px;
        color: white;
        font-weight: bold;
        float: right;
        font-size: 22px;
        line-height: 20px;
        cursor: pointer;
        transition: 0.3s;
        }

        .closebtn:hover {
        color: black;
        }
    

    </style>

<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<!----------------------------H T M L--------------------------------->
<body onload="startTime()">
    <h1 id="title">Garden Watering System</h1>
    
    <h2>
    Setup the location below
    </h2>
    <div class="container">
    <form id="myform">
        <label class="loclabel" for="city">City:</label><label class="locdata" id="city_name">None</label><br>
        <input type="text" id="city" ><br>
        <label class="loclabel" for="country">Country:</label><label class="locdata" id="country_name">None</label><br>
        <input type="text" id="country"><br><br>
        <button type="button" id="location_btn" name="Submit" onclick="send_form_data()">SET</button>
      </form>
    </div><br>
    <div class="details">
        <label class="attribute">Temperature:</label><label class="data" id="temp">None</label><br>
        <label class="attribute">Humidity:</label><label class="data" id="humidity">None</label><br>
        <label class="attribute">Weather:</label><label class="data" id="weather">None</label><br> 
    </div>

    <h3>Operating Mode</h3><br>
    <div id="clock"></div><br>
    <div class="mode">
    <div id="autolabel" onmouseover="Auto_details()">Auto </div>
        <label class="switch">
            <input type="checkbox" id="toggle" checked="true" onclick="JS2();">
            <span class="slider round"></span>
          </label><br>
        <button class=btn id="btn_M"  name="Manual" ONCLICK=' manual(water=true)' >MANUAL</button>
    </div><br>
    <div id="alert">
        <span class="closebtn" onclick="this.parentElement.style.opacity='0';">&times;</span> 
        <strong>AUTO MODE:</strong> Watering is done once between 9.00 AM - 10.00 AM and 4.00 PM - 5.00PM
      </div>
<!---------------------------JavaScript------------------------------->
<script>
    window.setInterval(refresh,20000);
    document.addEventListener('DOMContentLoaded',refresh);
    //document.addEventListener('DOMContentLoaded',auto);
    document.addEventListener('DOMContentLoaded',JS2);//set to auto
            //fetch the data as soon as the page has loaded
            //setInterval(refresh,2000)
    function send_form_data(){
        if(awake || mode=="MANUAL"){
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
        console.log("location data sent");}
        else{
            var diff=(6-minutes%6);
            var wait=diff.toString();
            alert("Server is Sleeping. Try again in " +wait+ "minutes.");
        }
    }

    
    function refresh(){
        if(awake){
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
        var timeoffset=xml.getElementsByTagName('loc')[0].childNodes[2].innerHTML;
        timezone=parseInt(timeoffset);

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
        else{
            return;
        }
    }
    function Auto_details(){
    document.getElementById("alert").style.setProperty('opacity', '1');
    
    }
   
    function auto() {
        document.getElementById("btn_M").style.borderColor = "white";
        const xhttp = new XMLHttpRequest();
        xhttp.onload = function(){
            console.log(this.responseText);
            if(this.responseText==" Set to Auto"){
                mode="AUTO"
            }
           
        };
        xhttp.open("GET", "/method?Auto=true&Manual=false");
        xhttp.send();
    }
    function manual(water) {
        console.log("manual sent");
        const xhttp = new XMLHttpRequest();
        xhttp.onload = function(){
            console.log(this.responseText);
            if (this.responseText=="Manual watering enabled"){
                mode="MANUAL"
            }
        };
        if(water){
            xhttp.open("GET", "/method?Auto=false&Manual=true&mwatering=true");
        }
        else{
            xhttp.open("GET", "/method?Auto=false&Manual=true&mwatering=false");
        }
        xhttp.send();
    }
    //function prompts for name, then displays message
    function JS2()
    {
        if(awake || mode=="MANUAL"){
        if(document.getElementById("toggle").checked){
            document.getElementById("btn_M").disabled = true;//In auto
            document.getElementById("btn_M").style.setProperty('background', 'rgb(34, 128, 235,0.5)');
            document.getElementById("btn_M").style.setProperty('color', 'rgb(228, 228, 228,0.5)');
            auto();
            console.log("Auto enabled");
        }
        else{
            document.getElementById("btn_M").disabled = false;
            document.getElementById("btn_M").style.setProperty('background', 'rgb(34, 128, 235,0.8)');
            document.getElementById("btn_M").style.setProperty('color', 'rgb(228, 228, 228,1)');
            console.log("Manual enabled");
            manual(water=false);
        }}
        else{
            document.getElementById("toggle").checked=true;
            var diff=(6-minutes%6);
            var wait=diff.toString();
            alert("Server is Sleeping. Try again in " +wait+ "minutes.");

        }
    }
    var timezone=19800;
    var awake=false;
    var hours;
    var minutes;
    var seconds;
    var mode="AUTO"
    //need to be set by the XML 
    function startTime() {
        var d = new Date();
        var diff = d.getTimezoneOffset();
        let unix_timestamp = Date.now();
        //console.log(unix_timestamp);
        //console.log(diff*60);
        unix_timestamp=unix_timestamp+diff*60*1000+timezone*1000;
        //console.log(unix_timestamp);
        // Create a new JavaScript Date object based on the timestamp
        // multiplied by 1000 so that the argument is in milliseconds, not seconds.
        var date = new Date(unix_timestamp);
        // Hours part from the timestamp
        hours = date.getHours();
        // Minutes part from the timestamp
        minutes = "0" + date.getMinutes();
        // Seconds part from the timestamp
        seconds = "0" + date.getSeconds();
        if(mode=="AUTO"){
        deepsleep(minutes.substr(-2),seconds.substr(-2));}
        // Will display time in 10:30:23 format
        var formattedTime = hours + ':' + minutes.substr(-2) + ':' + seconds.substr(-2);
        //console.log(formattedTime);
        document.getElementById('clock').innerHTML =  formattedTime;
        setTimeout(startTime, 1000);
        }
    var startflag=true;//need to change to false in the implementation
    function deepsleep(minutes,seconds){
        if(minutes=="00" && seconds=="00"){//Initial syncing(done by startflag) and the hourly syncing
         check_awake();
         startflag=true;
         console.log("Case1");
        }
        else if(((parseInt(minutes)%6==0)||(parseInt(minutes)%6==1)||(parseInt(minutes)%6==2))&&(seconds=="00")&&startflag){//After schedule started
        check_awake();
        console.log("Case2");
        }
        else if(((parseInt(minutes)%6==3)||(parseInt(minutes)%6==4)||(parseInt(minutes)%6==5))&&(seconds=="00")&&startflag){
        console.log("Case3");
        awake=false;
        console.log(minutes);
        }
        }

    function check_awake(){
        const xhttp = new XMLHttpRequest();
            xhttp.onload = function(){
            if(this.responseText=="true"){
                awake=true;
            };

            };
            xhttp.open("GET", "/wake");
            xhttp.send();
    }
        
    
</script>
</body>
</html>
)=====";
