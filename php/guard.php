<!DOCTYPE html>
<html>
<head>
 <!--Page title-->
 <title>Dashboard - Guard</title>
 <!--incorpereren van stylesheet (css)-->
 <link rel="stylesheet" type="text/css" media="screen" href="style.php">
 <!--oncorpereren van een Google webfont (werkt alleen met internet)-->
 <link href="https://fonts.googleapis.com/css?family=Titillium+Web&display=swap" rel="stylesheet">
 <!--De pagina ververst zichzelf iedere 3 seconden zonder input-->
 <meta http-equiv="refresh" content="10"/>
 <?php
	//opstart van de pagina
	$arr; 												
	$key = "Enter PIN";
	
	$host = "127.0.0.1";
    $port = "20205";
	//$sock = socket_create(AF_INET, SOCK_STREAM, 0); //socket openen.
	//socket_connect($sock, $host, $port);

	//socket_write($sock, "update", strlen("update")); //"Update" over de socket verbinding sturen.
		
	//$reply = socket_read($sock, 1924); //Wachten terugkoppeling van Server.php.
	
	//$arr = explode(" ",$reply); //de teruggekoppelde string converteren naar een Array (met explode();).
	
	//socket_close($sock); //socket verbinding beindigen.
	
	//echo "Update requested\n";
	
	$jsonString1 = file_get_contents('/home/pi/actuator.json');  // actuatoren ophalen.
	$jsonString2 = file_get_contents('/home/pi/sensor.json'); //sensoren ophalen.
	$data1 = json_decode($jsonString1, true); //actuator json data omzetten naar array.
	$data2 = json_decode($jsonString2, true); //sensor json data omzetten naar array.
	
	foreach($data1 as $key => $value) { //waarden van de ene array bij de andere voegen
		//echo "key: $key \n";
		//echo "value: $value \n";
		$data2[$key] = $value;
	}

	ksort($data2); //array op volgorde van ID (Key) sorteren.
	//print_r($data2);
	$arr = $data2;
	
    function Write($msg){ //Write functie. Met deze functie wordt Data via de socket naar de server.php verzonden om zo in een json file te kunnen worden geschreven.
        //$host = "127.0.0.1";
        //$port = "20205";
		//$sock = socket_create(AF_INET, SOCK_STREAM, 0); //socket openen.
		//socket_connect($sock, $host, $port);

		//socket_write($sock, $msg, strlen($msg)); //het versturen van de data in de vorm van ID,Value.
		//socket_close($sock); //socket verbinding beindigen.		
		
		$jsonString = file_get_contents('/home/pi/actuator.json');  // actuatoren openen
		$data = json_decode($jsonString, true);
		$msg2 = explode(',', $msg);                       // bericht ui client splitten op kommas, 		bijvoorbeeld "15,1".

		$ID = $msg2[0];                                   // eerste deel is ID, 						bijvoorbeeld "15".
		$Value = $msg2[1];                                // tweede deel is de aan te passen waarde, 	bijvoorbeeld "1".
		
		//print_r($data);
		$data[$ID] = $Value;
		

		$newJsonString = json_encode($data);
		file_put_contents('/home/pi/actuator.json', $newJsonString); //uitgesplitste waarden naar actuator.json schrijven om geinterpreteerd te kunnen worden door De raspberry Pi.

		$msg = trim($msg);
		echo "Client Wrote:\t".$msg."\n\n";
    }
    
	function refresh($cooldown){ //refresh functie. Wordt aangeroepen na het versturen van data om zo nieuwe data op te halen.
		echo("<meta http-equiv='refresh' content='0'>"); 

	}
   ?>
   
</head>
<body>

<div class="header"> <!-- Header balk bovenaan de php pagina -->
<h1>Dashboard</h1>
</div>

 <form method="post">
 <div class="container-80"> <!-- Container van 80% breedte, bevadt de meeste knoppen -->
	<div class="device"> <!-- Container voor ieder invidiueel device -->
		<h1>Bed</h1>
			<div class="content">
				<input type="submit" name = "button1" class="button" value="Nightlight <?php //global $arr; echo $arr[1]; //toont de huidige waarde van de corresponderende ID.?>"> <!--Led, Bed-->
					<?php
					if (isset($_POST['button1'])){global $arr; if ($arr[1] == 0){$arr[1] = 1;}else {$arr[1] = 0;}Write("1,$arr[1]"); refresh(0);}
					//Wanneer de knop wordt ingedrukt detecteerd bovenstaande functie dit, vervolgens wordt het ID geflipt, wordt deze weggeschreven naar server.php, en wordt de pagina ververst.
					//Dit principe wordt toegepast bij iedere grijze knop.
					?>
				<div class="led-group">
					<div class="Led-desc"> Nightlight</div>
					<div class="led <?php global $arr; if($arr[2] == 1){echo "green";}else{echo "grey";}?>" id="Led1" value="Switch (Bed)"><p><?php global $arr; if($arr[2] == 1){echo "ON";}else{echo "OFF";} //$arr wordt aangeroepen en afhankelijk van de status (1 of 0) weergeeft het lampje "ON" of "OFF". Dit principe wordt toegepast bij iedere groene indicator.?></p></div> <!-- Switch, Bed-->
					
				</div>	
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[3] >= 0){echo "orange";}else{echo "grey";}?>" value="Pressuresensor (Bed)"><p><?php global $arr; echo $arr[3];?></p></div> <!-- Pressure Sensor, Bed-->
					<div class="Led-desc"> Pressuresensor</div>
				</div>
			</div>
		</div>
		
		<div class="device">
		<h1>Chair</h1>
			<div class="content">
				
			<input type="submit" name = "button4" class="button" value="Massage <?php //global $arr; echo $arr[4]; ?>"> <!-- Vibrator, Chair -->
					<?php
					if (isset($_POST['button4'])){global $arr; if ($arr[40] == 0){$arr[40] = 1;}else {$arr[40] = 0;}Write("40,$arr[40]"); refresh(0);}
					?>
			<input type="submit" name = "button5" class="button" value="All Lights"> <!-- Led, Chair -->
					<?php
					if (isset($_POST['button5'])){global $arr; if ($arr[5] == 0){$arr[5] = 1;}else {$arr[5] = 0; $arr[8] = 0;}Write("5,$arr[5]"); Write("8,$arr[8]"); refresh(0);}
					?>
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[6] >= 0){echo "orange";}else{echo "grey";}?>" value="Pressuresensor (Chair)"><p><?php global $arr; echo $arr[6];?></p></div> <!-- Led, Lamp -->
					<div class="Led-desc"> Pressuresensor </div>
				</div>	
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[5] == 1){echo "green";}else{echo "grey";}?>" value="Switch (Chair)"><p><?php global $arr; if($arr[5] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Switch, Chair -->
					<div class="Led-desc"> Chairlight </div>
				</div>	
			</div>
		</div>
		
		<div class="device">
		<h1>Lamp</h1>
			<div class="content">
			
			<input type="submit" name = "button8" class="button" value="Toggle Lamp <?php //global $arr; echo $arr[8]; ?>"> <!-- Led, Lamp-->
					<?php
					if (isset($_POST['button8'])){global $arr; if ($arr[8] == 0){$arr[8] = 1;}else {$arr[8] = 0;}Write("8,$arr[8]"); refresh(0);}
					?>
			
			<input type="submit" name = "button40" class="button" value="Toggle Lights <?php //global $arr; echo $arr[15]; ?>"> <!-- Window, Wall -->
					<?php
					if (isset($_POST['button40'])){global $arr; if ($arr[5] == 0){$arr[5] = 1;}else {$arr[5] = 0;} Write("5,$arr[5]"); refresh(0);}
					?>	
					
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[9] == 1){echo "green";}else{echo "grey";}?>" value="Motionsensor"><p><?php global $arr; if($arr[9] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Motion, Lamp -->
					<div class="Led-desc"> Motionsensor </div>
				</div>
			</div>
		</div>
		
		
		
		<div class="device">
		<h1>Wall</h1>
			<div class="content">
			<input type="submit" name = "button14" class="button" value="Toggle Ledstrip <?php //global $arr; echo $arr[14]; ?>"> <!-- Ledstrip, Wall -->
					<?php
					if (isset($_POST['button14'])){global $arr; if ($arr[41] == 0){$arr[41] = 1;}else {$arr[41] = 0;}Write("41,$arr[41]");  refresh(0);}
					?>
			<input type="submit" name = "button15" class="button" value="Window <?php //global $arr; echo $arr[15]; ?>"> <!-- Window, Wall -->
					<?php
					if (isset($_POST['button15'])){global $arr; if ($arr[15] == 0){$arr[15] = 3;}else {$arr[15] = 0;}Write("15,$arr[15]");  refresh(0);}
					?>
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[16] >= 1){echo "green";}else{echo "grey";}?>" value="Dimmer"><p><?php global $arr; if($arr[16] >= 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Dimmer, Wall -->
					<div class="Led-desc"> Dimmer </div>
				</div>
			<!--<div class="led-group">
					<div class="led <?php global $arr; if($arr[17] == 1){echo "green";}else{echo "grey";}?>" value="LDR"><p><?php global $arr; if($arr[17] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- LDR, Wall -->
					<!--<div class="Led-desc"> LDR </div>
				</div>-->	
			</div>
		</div>
		
		<div class="device">
			<h1>Fridge</h1>
			<div class="content">
			<!--<input type="submit" name = "button18" class="button" value="Cooler + Fan <?php global $arr; echo $arr[18]; ?>"> <!-- Cooler + Fan, Fridge -->
					<?php
					if (isset($_POST['button18'])){global $arr; if ($arr[18] == 0){$arr[18] = 1;}else {$arr[18] = 0;}Write("18,$arr[18]");  refresh(0);}
					?>
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[19] >= 0){echo "orange";}else{echo "grey";}?>" value="Inner Temp"><p><?php global $arr; echo $arr[19];?></p></div> <!-- Temp binnen, Fridge -->
					<div class="Led-desc">Inner Temp.</div>
				</div>
				<div class="led-group">			
					<div class="led <?php global $arr; if($arr[20] >= 0){echo "orange";}else{echo "grey";}?>" value="Outer Temp"><p><?php global $arr; echo $arr[20];?></p></div> <!-- Temp buiten, Fridge -->
					<div class="Led-desc">Outer Temp.</div>
				</div>
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[21] == 0){echo "blue";}else{echo "grey";}?>" value="Door (Fridge)"><p><?php global $arr; if($arr[21] == 0){echo "OPEN";}else{echo "CLOSED";}?> </p></div> <!-- Doorsensor, Fridge -->
					<div class="Led-desc">Fridge Door</div>
				</div>
			</div>
		</div>
	
		
		<div class="device">
		<h1>Column</h1>
			<div class="content">
			<input type="submit" name = "button10" class="button" value="Buzzer <?php //global $arr; echo $arr[10]; ?>"> <!-- Buzzer, Column -->
					<?php
					if (isset($_POST['button10'])){global $arr; if ($arr[10] == 0){$arr[10] = 1;}else {$arr[10] = 0;}Write("10,$arr[10]");  refresh(0);}
					?>
			<input type="submit" name = "button11" class="button" value="Led (Column) <?php //global $arr; echo $arr[11]; ?>"> <!-- Led, Column -->
					<?php
					if (isset($_POST['button11'])){global $arr; if ($arr[11] == 0){$arr[11] = 2;}else {$arr[11] = 0;}Write("11,$arr[11]");  refresh(0);}
					?>
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[12] == 1){echo "green";}else{echo "grey";}?>" value="Switch (Column)"><p><?php global $arr; if($arr[12] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Switch, Column -->
					<div class="Led-desc"> Columnlight </div>
				</div>
				<div class="led-group">
					<div class="led <?php global $arr; if($arr[13] <= 400){echo "red";}else{echo "grey";}?>" value="Smoke"><p><?php global $arr; if($arr[13] <= 500){echo "ON";}else{echo "OFF";}?></p></div><!-- Smoke, Column -->
					<div class="Led-desc"> Smokedetector </div>
				</div>	
			</div>
		</div>
		
		<div class="device">
		<h1>Door</h1>
			<div class="content">
				<!-- Onderstaande code is voor de bewaker, maar maakt plaats voor de onderstaande keypad om de deur te openen. -->
					<!--<input type="submit" name = "button22" class="button" value="Inner LED (Door) <?php global $arr; echo $arr[22]; ?>"> <!-- Inner Doorled, Door -->
					<?php
					if (isset($_POST['button22'])){global $arr; if ($arr[22] == 0){$arr[22] = 1;}else {$arr[22] = 0;}Write("22,$arr[22]");  refresh(0);}
					?>
					<!--<input type="submit" name = "button23" class="button" value="Outer LED (Door) <?php global $arr; echo $arr[23]; ?>"> <!-- Outer Doorled, Door -->
					<?php
					if (isset($_POST['button23'])){global $arr; if ($arr[23] == 0){$arr[23] = 1;}else {$arr[23] = 0;}Write("23,$arr[23]");  refresh(0);}
					?>
					<input type="submit" name = "button24" class="button" value="Open Door <?php //global $arr; echo $arr[24]; ?>"> <!-- Servo, Door -->
					<?php
					if (isset($_POST['button24'])){global $arr; if ($arr[24] == 0){$arr[24] = 1;}else {$arr[24] = 0;}Write("24,$arr[24]");  refresh(0);}
					?>
						<div class="led-group">
							<div class="led <?php global $arr; if($arr[22] == 1){echo "green";}else{echo "grey";}?>" value="Inner Doorknob"><p><?php global $arr; if($arr[22] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Inner Doorknob, Door -->
							<div class="Led-desc">Light (inside)</div>
						</div>
						<div class="led-group">
							<div class="led <?php global $arr; if($arr[23] == 3){echo "green";}else{echo "grey";}?>" value="Outer Doorknob"><p><?php global $arr; if($arr[23] == 3){echo "ON";}else{echo "OFF";}?></p></div> <!-- Outer Doorknob, Door -->
							<div class="Led-desc">Light (outside)</div>
						</div>
					</div>
			</div>
	</div>
	<div class="container-20">
		<div class="device" id="door">
				<h1>Alerts</h1> <!-- alerts van de verschillende devices.-->
				<div class="content">
					<?php global $arr; if($arr[31] == 1){echo '<div class="alert red">A seizure has been detected (!)'; echo '<input type="submit" name = "alert2" class="alertButton" value="Clear"> </div>';} ?>
					<!-- Wanneer Alert 31 actief (1) is zal dit zichtbaar worden gemaakt in het venster, daarnaast wordt er een knop gegenereerd die de betreffende alert uit zet.-->
					<?php if (isset($_POST['alert2'])){global $arr; write("31,0"); refresh(0);}?>
					<!-- Wanneer de knop in de regel hierboven wordt ingedrukt wordt de alert uitgezet en de pagina ververst zodat de alert verdwijnt.
						 Onderstaande alerts gebruiken hetzelfde principe. -->
					<?php global $arr; if($arr[38] != 0){echo '<div class="alert red">PIN entered incorrectly '; if($arr[38] == 1){echo '(!)';}else{echo $arr[38]; echo' times (!)';};  echo '<input type="submit" name = "alert9" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert9'])){global $arr; write("38,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[32] == 1){echo '<div class="alert red">The firealarm has been triggered (!)'; echo '<input type="submit" name = "alert3" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert3'])){global $arr; write("32,0"); write("10,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[37] == 1){echo '<div class="alert red">Resident has requested aid (!)'; echo '<input type="submit" name = "alert8" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert8'])){global $arr; write("37,0"); refresh(0);}?>		
					
					<?php //global $arr; if($arr[35] == 1){echo '<div class="alert orange">Resident must take his medicine'; echo '<input type="submit" name = "alert6" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert6'])){global $arr; write("35,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[36] == 1){echo '<div class="alert orange" >Resident has not taken his medicine yet'; echo '<input type="submit" name = "alert7" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert7'])){global $arr; write("36,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[34] == 1){echo '<div class="alert orange">Fridge has been open for too long'; echo '<input type="submit" name = "alert5" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert5'])){global $arr; write("34,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[39] == 1){echo '<div class="alert green">A request was made to open the door'; echo '<input type="submit" name = "alert10" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert10'])){global $arr; write("39,0"); refresh(0);}?>

					<?php global $arr; if($arr[33] == 1){echo '<div class="alert green">Massage requested during cooldown'; echo '<input type="submit" name = "alert4" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert4'])){global $arr; write("33,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[30] == 1){echo '<div class="alert green">Alarmclock currently active'; echo '<input type="submit" name = "alert1" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert1'])){global $arr; write("30,0"); refresh(0);}?>
				</div>
			</div>	
		</div>
	</div>
    <div class="footer"> <!-- footer, de onderste grijze balk-->		
		<form method="post">
			<div class=" footer-form"> <!--onderstaande functie werkt het zelfde als write(), maar gebruikt 2 velden om de ID en waarde te bepalen. Wordt enkel gebruikt om te testen.
			<div class="entry">
				<input type="text" placeholder="Enter ID" name="ID"><br><br>
			</div>
			<div class="entry">
				<input type="text" placeholder="Enter Value" name="txtMessage"><br><br>
			</div>
			<div class="entry">
				<input type="submit" class="button-m" name="btnSend" value="Update Manually">
				 <?php
				 if(isset($_POST['update'])){
					 Write($_POST['ID'],$_POST['VALUE']);	 
				 }
				 
				if (isset($_POST['btnSend'])) {
				 $msg2 = $_REQUEST['txtMessage'];
				 $msg = $_REQUEST['ID'];
				 $sock = socket_create(AF_INET, SOCK_STREAM, 0);
				 socket_connect($sock, $host, $port);

				 socket_write($sock, $msg, strlen($msg));           // schrijf bericht gesplitst door komma
				 socket_write($sock, ",", strlen($msg));
				 socket_write($sock, $msg2, strlen($msg2));

				 $reply = socket_read($sock, 1924);
				 //$reply = trim($reply);

				 //$reply = "Server says:\t".$reply;
				 socket_close($sock);
				 //socket_shutdown($sock,2);
				}
				?>
			</div>
		</form>

</div>
  
   <!--<tr> reply functie voor bovenstaande code.
    <td>
     <textarea rows="10" cols="30"><?php echo @$reply; ?></textarea>
    </td>
   </tr>-->


</body>
</html>
