// Import required libraries
#include "WiFi.h"
  #include "ESPAsyncWebServer.h"
  #include <Adafruit_Sensor.h>
  #include "DHT.h"
  #include <AsyncTCP.h>
  #include <Wire.h>
  #include <Adafruit_BMP085.h>
  #include <LiquidCrystal.h>

const char* ssid = "realme8";
const char* password = "12345678";

#define DHTPIN 4
#define DHTTYPE DHT11
#define seaLevelPressure_hPa 1013.25   

DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;


AsyncWebServer server(80);


# DHT11 readings
String readDHTTemperature() {
  float t = dht.readTemperature();
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}


# BMP180 readings
String readBMPTemperature() {
  float t = bmp.readTemperature();
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readBMPPressure() {
  float p = bmp.readPressure();
  if (isnan(p)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(p);
    return String(p);
  }
}

String readBMPseaLevelPressure() {
  float s = bmp.readSealevelPressure();
  if (isnan(s)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(s);
    return String(s);
  }
}

String readBMPAltitude() {
  float a = bmp.readAltitude();
  if (isnan(a)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(a);
    return String(a);
  }
}

String readBMPrealAltitude() {
  float ra = bmp.readAltitude(seaLevelPressure_hPa * 100);
  if (isnan(ra)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(ra);
    return String(ra);
  }
}




const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css"
        integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    <style>
        body {
            margin: 0;
            padding: 0;
            /* Ensure the 3D model doesn't cause scrollbars */
            font-family: Arial;
        }

        .Content {
            display: flex;
            flex-direction: column;
            gap: 50px;
        }

        .header {
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            padding: 20px;
            z-index: 1000;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
            backdrop-filter: blur(10px);
            background: rgba(255, 255, 255, 0.1);
        }

        .header h1 {
            margin: 0;
            color: rgb(255, 255, 255);
        }

        html {
            font-family: Arial;
            display: inline-block;
            margin: 0px auto;
            text-align: center;
        }

        h2 {
            font-size: 3.0rem;
        }

        h1 {
            font-size: 1.5rem;
            color: rgb(255, 255, 255);
        }

        p {
            font-size: 3.0rem;
        }

        .units {
            font-size: 1.2rem;
        }

        .dht-labels {
            font-size: 1.5rem;
            vertical-align: middle;
            padding-bottom: 15px;
        }

        .reading-container {
            background-color: white;
            padding: 20px;
            margin-bottom: 20px;
            border-radius: 10px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            display: flex;
            align-items: center;
            margin: auto;
        }

        .reading-container button {
            margin-right: 20px;
        }

        .readings-container.active {
            opacity: 1;
            max-height: 500px;

        }

        .toggleButton {
            color: #FFF;
            font-family: Arial;
            font-size: 24px;
            font-style: normal;
            font-weight: 700;
            line-height: normal;
            padding: 15px;
            margin: 80px 20px 20px;
            /* Adjusted margin to ensure visibility */
            cursor: pointer;
            width: 322.71px;
            height: 101px;
            flex-shrink: 0;
            border-radius: 54px;
            background: #151515;
            position: relative;
            /* Ensure the button is positioned correctly */
            z-index: 1001;
            /* Ensure the button is above the 3D model */
        }

        main {
            padding-top: 80px;
        }

        .header-auto-typed {
            color: #83d3ef;
        }

        .spline {
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            pointer-events: none;
            z-index: -1;
            /* Set z-index to a negative value to place it behind other elements */
        }

        #readings-container-dht {
            display: none;
            /*Edited*/

        }

        #readings-container-bmp {
            display: none;
            /*Edited*/

        }
    </style>
</head>

<body>
    <spline-viewer url="https://prod.spline.design/6qtU4WOD8pko4brU/scene.splinecode" class="spline"></spline-viewer>
    <header>
        <nav class="header">
            <div class="navbar-brand">
                <h1>Weather Station | <span class="header-auto-typed"></span></h1>
            </div>
        </nav>
    </header>
    <main>
        <div class="Content">
            <!-- Container for DHT readings -->
            <div class="reading-container">
                <div id="readings-container-dht" class="readings-container">
                    <!-- DHT readings content -->
                    <p>
                        <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
                        <span class="dht-labels">Temperature</span>
                        <span id="temperature">%TEMPERATURE%</span>
                        <sup class="units">&deg;C</sup>
                    </p>
                    <p>
                        <i class="fas fa-tint" style="color:#00add6;"></i>
                        <span class="dht-labels">Humidity</span>
                        <span id="humidity">%HUMIDITY%</span>
                        <sup class="units">%</sup>
                    </p>
                </div>
                <button class="toggleButton" onclick="toggleReadings('readings-container-dht')">DHT11 Readings</button>
                <img id="slide-image" class="slide-image" src="DHT11-Module 1.png" alt="Slide Image">
            </div>



            <!-- Container for BMP readings -->
            <div class="reading-container">
                <img id="slide-image" class="slide-image" src="bmp180 1.png" alt="Slide Image">
                <button class="toggleButton" onclick="toggleReadings('readings-container-bmp')">BMP180 Readings</button>
                <div id="readings-container-bmp" class="readings-container">
                    <!-- BMP readings content -->
                    <p>
                        <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
                        <span class="dht-labels">Temperature</span>
                        <span id="temperature_bmp">%TEMPERATURE_bmp%</span>
                        <sup class="units">&deg;C</sup>
                    </p>
                    <p>
                        <i class="fa-solid fa-wind" style="color:#cdcdcd;"></i>
                        <span class="dht-labels">Air Pressure</span>
                        <span id="pressure_bmp">%PRESSURE_bmp%</span>
                    </p>
                    <p>
                        <i class="fa-solid fa-water" style="color:#00add6;"></i>
                        <span class="dht-labels">Sea levelPressure</span>
                        <span id="sl_pressure_bmp">%SEA_LEVEL_bmp%</span>
                    </p>
                    <p>
                        <i class="fa-solid fa-mountain" style="color:#e36a0d;"></i>
                        <span class="dht-labels">Altitude</span>
                        <span id="altitude_bmp">%ALTITUDE_bmp%</span>
                    </p>
                    <p>
                        <i class="fa-solid fa-mountain" style="color:#e36a0d;"></i>
                        <span class="dht-labels">Real Altitude</span>
                        <span id="r_altitude_bmp">%REAL_ALTITUDE_bmp%</span>
                    </p>
                </div>
            </div>


            <div class="reading-container">
                <div id="readings-container-dht" class="readings-container"></div>
                <button class="toggleButton" onclick="saveData()">Save Data</button>
            </div>
        </div>
    </main>
    <script type="module" src="https://unpkg.com/@splinetool/viewer@0.9.523/build/spline-viewer.js"></script>
    <script>

        function toggleReadings(containerId) {
            var readingsContainer = document.getElementById(containerId);
            var slideImage = document.getElementById('slide-image'); // Get the image element

            readingsContainer.classList.toggle("active");

            if (readingsContainer.classList.contains("active")) {
                readingsContainer.style.maxHeight = readingsContainer.scrollHeight + "px";
                slideImage.style.transform = 'translateX(100%)'; // Slide the image to the right
            } else {
                readingsContainer.style.maxHeight = null; // Reset max-height
                slideImage.style.transform = 'translateX(0)'; // Slide the image back to its original position
            }

            // Check if the container is now active
            if (readingsContainer.classList.contains("active")) {
                readingsContainer.setAttribute('style', 'display: block');
            } else {
                // If not active, hide the container
                setTimeout(function () {
                    readingsContainer.style.display = 'none';
                }, 500); // Adjust the delay based on your animation duration
            }
        }




        function saveData() {
            // Get the current date and time
            var now = new Date();
            var formattedDateTime = now.toISOString().replace(/:/g, '-').replace(/\..+/, '');

            // Create a unique filename
            var fileName = 'esp32_' + formattedDateTime + '.txt';

            // Extract the variables you want to save
            var temperature = document.getElementById("temperature").innerText;
            var humidity = document.getElementById("humidity").innerText;
            var temperature_bmp = document.getElementById("temperature_bmp").innerText;
            var pressure_bmp = document.getElementById("pressure_bmp").innerText;
            var sl_pressure_bmp = document.getElementById("sl_pressure_bmp").innerText;
            var altitude_bmp = document.getElementById("altitude_bmp").innerText;
            var r_altitude_bmp = document.getElementById("r_altitude_bmp").innerText;

            // Create a string with the data
            var dataToSave =
                'DHT11 Readings' + '\n' +
                'Temperature: ' + temperature + '\n' +
                'Humidity: ' + humidity + '\n' +
                '\n' +
                'BMP180 Readings' + '\n' +
                'Temperature: ' + temperature_bmp + '\n' +
                'Pressure: ' + pressure_bmp + '\n' +
                'Sea Level Pressure: ' + sl_pressure_bmp + '\n' +
                'Altitude: ' + altitude_bmp + '\n' +
                'Real Altitude: ' + r_altitude_bmp;

            // Create a Blob containing the data
            var blob = new Blob([dataToSave], { type: 'text/plain' });

            // Create a link element to trigger the download
            var a = document.createElement('a');
            a.href = URL.createObjectURL(blob);
            a.download = fileName;

            // Append the link to the document and trigger the download
            document.body.appendChild(a);
            a.click();

            // Remove the link from the document
            document.body.removeChild(a);
        }



        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("temperature").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/temperature", true);
            xhttp.send();
        }, 10000);

        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("humidity").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/humidity", true);
            xhttp.send();
        }, 10000);



        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("temperature_bmp").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/temperature_bmp", true);
            xhttp.send();
        }, 10000);


        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("pressure_bmp").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/pressure_bmp", true);
            xhttp.send();
        }, 10000);


        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("sl_pressure_bmp").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/sl_pressure_bmp", true);
            xhttp.send();
        }, 10000);


        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("altitude_bmp").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/altitude_bmp", true);
            xhttp.send();
        }, 10000);


        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("r_altitude_bmp").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/r_altitude_bmp", true);
            xhttp.send();
        }, 10000);


    </script>
    <script src="https://kit.fontawesome.com/f5a624e72c.js" crossorigin="anonymous"></script>
    <script src="https://unpkg.com/typed.js@2.0.16/dist/typed.umd.js"></script>
    <script>
        var type = new Typed(".header-auto-typed", {
            strings: ["ESP32-Dev Module", "Mohamed Fawzy", "Ruba Wasfi", "Sandy Youtham", "Youssef Isaac", "Youssef Walid", "Youssef Ahmed", "Rafik Nasr"],
            typeSpeed: 40,
            backSpeed: 40,
            loop: true
        })
    </script>

</body>

</html>
)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  else if(var == "TEMPERATURE_bmp"){
    return readBMPTemperature();
  }
  else if(var == "PRESSURE_bmp"){
    return readBMPPressure();
  }
  else if(var == "SEA_LEVEL_bmp"){
    return readBMPseaLevelPressure();
  }
  else if(var == "ALTITUDE_bmp"){
    return readBMPAltitude();
  }
  else if(var == "REAL_ALTITUDE_bmp"){
    return readBMPrealAltitude();
  }
  return String();
}

void setup(){
  Serial.begin(115200);

  dht.begin();
  bmp.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }


  Serial.println(WiFi.localIP());

  // get server request
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  
  // get DHT11 requests
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  // get DHT11 requests
  server.on("/temperature_bmp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMPTemperature().c_str());
  });
  server.on("/pressure_bmp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMPPressure().c_str());
  });
  server.on("/sl_pressure_bmp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMPseaLevelPressure().c_str());
  });
  server.on("/altitude_bmp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMPAltitude().c_str());
  });
  server.on("/r_altitude_bmp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBMPrealAltitude().c_str());
  });
  


  server.begin();
}
 
void loop(){

  float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);
 
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
 
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.print(F(" °C "));
    Serial.print("/ ");
    Serial.print(f);
    Serial.print(F(" °F "));
    Serial.println();
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F(" %"));
    Serial.println();
    Serial.println();
    Serial.println("End of DHT11 readings!");
    Serial.println("=============================");



    if (!bmp.begin()) {
    Serial.println("BMP180 Not Found. CHECK CIRCUIT!");
    }
 
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
 
    Serial.print("Pressure at sealevel = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");
 
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");
    Serial.println();
    Serial.println("End of BMP180 readings!");
    Serial.println("=============================");
  
}