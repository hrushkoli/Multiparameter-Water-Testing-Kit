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

$sql = "SELECT id, pH, Turbidity, Temperature , date, time FROM nodemcu_table";  // Update your tablename here

$result = $conn->query($sql);

echo "<center>";



if ($result->num_rows > 0) {


    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<strong> Id:</strong> " . $row["id"]. " &nbsp <strong>pH:</strong> " . $row["pH"]. " &nbsp <strong>val2:</strong> " ." &nbsp <strong>pH:</strong> " . $row["Turbidity"]. " &nbsp <strong>Turbidity:</strong> " . $row["Temperature"]. " &nbsp <strong>Date:</strong> " . $row["date"]." &nbsp <strong>Time:</strong>" .$row["time"]. "<p>";
    


}
} else {
    echo "0 results";
}

echo "</center>";

$conn->close();



?>
