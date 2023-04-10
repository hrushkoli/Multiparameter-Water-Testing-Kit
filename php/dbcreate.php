<?php



    $host = "localhost";		         // host = localhost because database hosted on the same server where PHP files are hosted
    $dbname = "";              // Database name
    $username = "";		// Database username
    $password = "";	        // Database password


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

else { echo "Connected to mysql database. <br>"; }


// Select values from MySQL database table

$sql = "CREATE TABLE nodemcu_table ( id INT(10) NOT NULL AUTO_INCREMENT , pH FLOAT(10) , Turbidity FLOAT(10) , Temperature FLOAT(10) , date DATE , time TIME , PRIMARY KEY (id)) ";  // Update your tablename here

$result = $conn->query($sql);

if ($result){
    echo "Created";
}

$sql2 = "INSERT INTO nodemcu_table (pH, Turbidity,Temperature) VALUES (7,0,35)";
$result2 = $conn->query($sql2);

echo "<center>";


$conn->close();



?>
