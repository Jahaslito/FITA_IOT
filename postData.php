<!DOCTYPE html>
<html>
<head>
	<title>Data stream</title>
	<meta http-equiv="refresh" content="15">
</head>
<body>
	<h1>This is the data received.</h1>
</body>
</html>

<?php
	
	$servername = "";
    $username = "";
    $password = "";
    $dbname = "";

    $conn = new mysqli($servername, $username, $password, $dbname);
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }

    date_default_timezone_set('Africa/Nairobi');
    $d = date("Y-m-d");
    echo " Date:".$d."<BR>";
    $t = date("H:i:s");
    if (isset($_GET['temperature'])) {
    	echo $_GET['temperature'];
    }else {
    	echo "No temperature data!";
    }
    
    if(!empty($_GET['temperature']))
    {
    	$temperature = $_GET['temperature'];

    	$sql = "INSERT INTO sensor(temperature, Date, Time)
    			VALUES ('".$temperature."', '".$d."', '".$t."' )";

	    if ($conn->query($sql) === TRUE) {
			    echo "OK";
		} else {
			    echo "Error: " . $sql . "<br>" . $conn->error;
		}

	}

	$conn->close();

  ?>