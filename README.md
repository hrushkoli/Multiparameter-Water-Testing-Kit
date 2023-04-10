# Multiparameter Water Testing Kit

This is a small project that I created using Arduino and NodeMCU ESP8266

## Working

This project works by using the Arduino board to process the data coming from the sensors and then sends it to the ESP8266 which uploads the data to your database.

## Installation

- Upload the php files to a hosting service

- Create a MYSQL database and a table with the following columns

<table>
<tr>
<td>id (autoincrement : int)</td>
<td>pH (varchar 10)</td>
<td>TDS (varchar 10)</td>
<td>Temperature (varchar 10)</td>
<td>Date (varchar 10)</td>
<td>Time (varchar 10)</td>
</tr>
</table>

- Modify the ESP 8266 code and chang the database details

- Upload the code to your Arduino and NodeMCU respectively
