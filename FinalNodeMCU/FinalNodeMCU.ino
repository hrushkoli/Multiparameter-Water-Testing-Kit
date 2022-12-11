/*------------------------------------------------------------------------------
  06/25/2019
  Author: Makerbro
  Platforms: ESP8266
  Language: C++/Arduino
  File: esp8266_firmware.ino
  ------------------------------------------------------------------------------
  Description: 
  Code for YouTube video demonstrating how to communicate between an Arduino UNO
  and an ESP8266.
  https://youtu.be/6-RXqFS_UtU
  
  Do you like my videos? You can support the channel:
  https://patreon.com/acrobotic
  https://paypal.me/acrobotic
  ------------------------------------------------------------------------------
  Please consider buying products from ACROBOTIC to help fund future
  Open-Source projects like this! We'll always put our best effort in every
  project, and release all our design files and code for you to use. 

  https://acrobotic.com/
  https://amazon.com/acrobotic
  ------------------------------------------------------------------------------
  License:
  Please see attached LICENSE.txt file for details.
------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#define HOST "shpwatertestingkit.000webhostapp.com"          // Enter HOST URL without "http:// "  and "/" at the end of URL


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

ESP8266WebServer server;
char* ssid = "Galaxy A73 5G9AF3";
char* password = "9820703453";
void setup()
{
  lcd.begin();
  lcd.backlight();
  WiFi.begin(ssid,password);
  Serial.begin(9600);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  lcd.print(WiFi.localIP());
  server.on("/",handleIndex);
  Serial.setTimeout(20);
  server.begin();
}

void loop()
{
  int i =0;
//  server.handleClient();
//  handleIndex();
HTTPClient http;    // http object of clas HTTPClient
  WiFiClient wclient; // wclient object of clas HTTPClient    
  while(Serial.available()){
      String serial = Serial.readString();
      Serial.println(serial);
      http.begin(wclient, "http://shpwatertestingkit.000webhostapp.com/dbwrite.php");              // Connect to host where MySQL databse is hosted
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header
      int httpCode = http.POST(serial);
      if (httpCode == 200) { 
        Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
      String webpage = http.getString();    // Get html webpage output and store it in a string
      Serial.println(webpage + "\n"); 
      }
      
      // if failed to connect then return and restart
      
      else { 
        Serial.println(httpCode); 
        Serial.println("Failed to upload values. \n"); 
        http.end();  
        }

      
//      char arr[serial.length() + 1]; 
//        int i = 0;
//        char *p = strtok (arr, "/");
//        char *array[3];
//    
//        while (p != NULL)
//        {
//            array[i++] = p;
//            p = strtok (NULL, " ");
//        }
//    
//        for (i = 0; i < 3; ++i) 
//            Serial.printf("%s\n", array[i]);
//  
//    Serial.println(serial);
  }
  
  delay(2000);
}

void handleIndex()
{
  lcd.clear();
  // Send a JSON-formatted request with key "type" and value "request"
  // then parse the JSON-formatted response with keys "gas" and "distance"
  DynamicJsonDocument doc(1024);
  float pH = 0, TDS = 0 ,Temperature = 0;
  // Sending the request
  doc["type"] = "request";
  serializeJson(doc,Serial);
  // Reading the response
  boolean messageReady = false;
  String message = "";
  while(messageReady == false) { // blocking but that's ok
    if(Serial.available()) {
      message = Serial.readString();
      messageReady = true;
    }
  }
  // Attempt to deserialize the JSON-formatted message
  DeserializationError error = deserializeJson(doc,message);
  if(error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  pH = doc["pH"];
  TDS = doc["TDS"];
  Temperature = doc["Temperature"];
  // Prepare the data for serving it over HTTP
  String output = "pH: " + String(pH) + "\n";
  output += "TDS: " + String(TDS);
  output += "Temperature : " + String(Temperature) + "\n"; 
  // Serve the data as plain text, for example
  server.send(200,"text/plain",output);
  Serial.print(String(pH)+"pH    " + String(Temperature)+"C");
//  Serial.setCursor(0,1);
  Serial.print(String(TDS)+"NTU");
}
