#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
//pH Sensor Setup
#define phPin 4
unsigned long int avgValue;
float b;
int buf[10],temp;

//TDS Setup
#define turbpin 0
float volt;
float ntu;
#define potpin 6
//Temperature Sensor Setup
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//Comm Setup
String message = "";
bool messageReady = false;

void setup() {
  Serial.setTimeout(20);
  Serial.begin(9600);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.print(" Hello Makers "); // Start Printing
  sensors.begin();
  float phValue = PhSensor();
  float tdsValue = tdsSensor();
  float temperatureValue = TemperatureSensor();
  Serial.print("phValue = ");
  Serial.print(phValue);
  Serial.print(" ");
  Serial.print("tdsValue = ");
  Serial.print(tdsValue);
  Serial.print(" ");
  Serial.print("temperatureValue = ");
  Serial.print(temperatureValue);
//  serialCommunication(phValue,tdsValue,temperatureValue);
}

void loop(){
  delay(10000);
  float phValue = PhSensor();
  float tdsValue = tdsSensor();
  float temperatureValue = TemperatureSensor();
  Serial.print("phValue=");
  Serial.print(phValue);
  Serial.print("&");
  Serial.print("tdsValue=");
  Serial.print(tdsValue);
  Serial.print("&");
  Serial.print("temperatureValue=");
  Serial.print(temperatureValue);
//  serialCommunication(phValue,tdsValue,temperatureValue);
  delay(5000);
}


void serialCommunication(String phValue, float tdsValue , float temperatureValue) {
  // Monitor serial communication
  
  while(Serial.available()) {
    message = Serial.readString();
    Serial.print(message);
  }
}


void jsonCommunication(float phValue, float tdsValue , float temperatureValue) {
  // Monitor serial communication
  
  while(Serial.available()) {
    message = Serial.readString();
    Serial.print(message);
    messageReady = true;
  }
  // Only process message if there's one
  if(messageReady) {
    // The only messages we'll parse will be formatted in JSON
    DynamicJsonDocument doc(1024); // ArduinoJson version 6+
    // Attempt to deserialize the message
     Serial.print(phValue);
    Serial.print(" ");
    Serial.print(tdsValue);
    Serial.print(" ");
    Serial.print(temperatureValue);
    DeserializationError error = deserializeJson(doc,message);
    if(error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      messageReady = false;
      return;
    }
    if(doc["type"] == "request") {
      doc["type"] = "response";
      // Get data from analog sensors
      doc["pH"] = phValue;
      doc["TDS"] = tdsValue;
      doc["Temperature"] = temperatureValue;
      serializeJson(doc,Serial);
      Serial.println("data sent");
    }
    messageReady = false;
  }
}


float PhSensor(){
   for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(phPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];

  float phValue=((float)avgValue*5.0/1024)/6;//convert the analog into millivolt
  phValue=3.5*phValue  ; //convert the millivolt into pH value
//  phValue=7;
  return phValue;
}

float tdsSensor(){
  volt = 0;
  for(int i=0; i<800; i++)
  {
      volt += ((float)analogRead(turbpin)/1023)*5;
  }
  volt = (volt/800)*0.7913;
  volt = round_to_dp(volt,2);
    double turbPot = (0.001*analogRead(potpin))-0.5002;
    double x=2.8263 + turbPot;
    ntu = (x-volt)/0.0074;
//    ntu=100;
    return ntu;
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

float TemperatureSensor()
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
//  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
//  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
//    Serial.print("Temperature for the device 1 (index 0) is: ");
//    tempC=27;
    return tempC;
  } 
  else
  {
//    Serial.println("Error: Could not read temperature data");
    return 0;
  }
}
