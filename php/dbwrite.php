<?php



    $host = "";		         // host = localhost because database hosted on the same server where PHP files are hosted
    $dbname = "";              // Database name
    $username = "";		// Database username
    $password = "";	        // Database password


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

else { echo "Connected to mysql database. "; }

   
// Get date and time variables
    date_default_timezone_set('Asia/Kolkata');  // for other timezones, refer:- https://www.php.net/manual/en/timezones.asia.php
    $d = date("Y-m-d");
    $t = date("H:i:s");
    
// If values send by NodeMCU are not empty then insert into MySQL database table

  if(!empty($_POST['sendval1']) && !empty($_POST['sendval2']) && !empty($_POST['sendval3']) )
    {
		$pH = $_POST['sendval1'];
                $Turbidity = $_POST['sendval2'];
                        $Temperature = $_POST['sendval3'];


// Update your tablename here
	        $sql = "INSERT INTO nodemcu_table (pH, Turbidity, Temperature, Date, Time) VALUES ('".$pH."','".$Turbidity."','".$Temperature."', '".$d."', '".$t."')"; 
 


		if ($conn->query($sql) === TRUE) {
		    echo "Values inserted in MySQL database table.";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


// Close MySQL connection
$conn->close();



?>
