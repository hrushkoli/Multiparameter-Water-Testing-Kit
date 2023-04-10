# Multiparameter Water Testing Kit

This is a small project that I created using Arduino and NodeMCU ESP8266

## Working

This project works by using the Arduino board to process the data coming from the sensors and then sends it to the ESP8266 which uploads the data to your database.

## Installation

- Upload the php files to a hosting service

- Create a MYSQL database and a table and change the php files to match the database information

- Go to website/dbcreate.php to create the required tables

- Modify the ESP 8266 code and change the database details and also change the wifi ssid network details

- Upload the code to your Arduino and NodeMCU respectively

- Go to website/dbread.php to read the data from your database 
