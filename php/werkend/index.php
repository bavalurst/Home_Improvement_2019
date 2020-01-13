<!DOCTYPE html>

<html>

<head>

        <title>PJSysDev V1.1.0 </title>

        <meta charset="UTF-8">

        <meta name="viewport" content="width=device-width, initial-scale=1.0">

	<link rel="stylesheet" href="index.css">

</head>

<body>
	<div class="header">
	<h1>Dashboard</h1>
	
	</div>
	
    <div class="panel">
		<div class="device">
		<h1>Bed</h1>
		<input type="button" class="button" value="Nightlight">
		<input type="button" class="button" value="Pressuresensor (Bed)">
		</div>
		
		<div class="device">
		<h1>Chair</h1>
		<input type="button" class="button" value="Pressuresensor (Chair)">
		<input type="button" class="button" value="Vibrator">
		<input type="button" class="button" value="Chairlight">
		</div>
		
		<div class="device">
		<h1>Lamp</h1>
		<input type="button" class="button" value="Lamp">
		<input type="button" class="button" value="Motionsensor (Lamp)">
		</div>
		
		<div class="device">
		<h1>Pillar</h1>
		<input type="button" class="button" value="Switch (Pillar)">
		<input type="button" class="button" value="Smoke Detector">
		<input type="button" class="button" value="Zooomer">
		</div>
		
		<div class="device">
		<h1>Wall</h1>
		<input type="button" class="button" value="LDR">
		<input type="button" class="button" value="LED-strip">
		<input type="button" class="button" value="Window">
		<input type="button" class="button" value="Dimmer">
		</div>
		
		<div class="device">
		<h1>Fridge</h1>
		<input type="button" class="button" value="Door (Fridge)">
		<input type="button" class="button" value="Cooling (Heatsink)">
		<input type="button" class="button" value="Cooling (Fan)">
		<input type="button" class="button" value="Temperature">
		</div>
		
		<div class="device">
		<h1>Door</h1>
		<input type="button" class="button" value="Inner Doorknob">
		<input type="button" class="button" value="Outer Doorknob">
		<input type="button" class="button" value="Servo (Door)">
		</div>	
	</div>
	
	
    
	
	<div class="footer">

	<form method="post">
		<div class=" footer-form">
			<div class="entry">
				<input type="text" placeholder="Enter ID" name="id" required><br><br>
			</div>
			<div class="entry">
				<input type="text" placeholder="Enter Value" name="value" required><br><br>
			</div>
			<div class="entry">
				<input type="submit" name="update" value="Update Manually">
			</div>
			</form>
		</div>
	</div>
</body>
</html>

<?php
// php code tot Update data from mysql database Table

if(isset($_POST['update']))
{

   $hostname = "localhost";
   $username = "pi";
   $password = "root";
   $databaseName = "database";

   $connect = mysqli_connect($hostname, $username, $password, $databaseName);

   // get values form input text and number

   $id = $_POST['id'];
   $value = $_POST['value'];

   // mysql query to Update data
   $query = "UPDATE `domotica` SET `value`='".$value."' WHERE `id` = $id";

   $result = mysqli_query($connect, $query);

   if($result)
   {
       echo 'Data Updated';
   }else{
       echo 'Data Not Updated';
   }
   mysqli_close($connect);
}

?>
<!--<html>
 <head>
  <title>Dejavu</title>
 </head>
 <body>
<?php
$servername = "localhost";
$username = "pi";
$password = "root";
$dbname = "database";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "UPDATE domotica SET value='20' where ID=1";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();

?>

<?php
function write(){

}
?>

 </body>
</html>
