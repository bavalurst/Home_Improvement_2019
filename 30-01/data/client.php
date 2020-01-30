<!DOCTYPE html>
<html>
<head>
 <!--Page title-->
 <title>PJSysDev V2.1.2</title>
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
	$sock = socket_create(AF_INET, SOCK_STREAM, 0); //socket openen.
	socket_connect($sock, $host, $port);

	socket_write($sock, "update", strlen("update")); //"Update" over de socket verbinding sturen.
		
	$reply = socket_read($sock, 1924); //Wachten terugkoppeling van Server.php.
	
	$arr = explode(" ",$reply); //de teruggekoppelde string converteren naar een Array (met explode();).
	
	socket_close($sock); //socket verbinding beindigen.
	
    function Write($msg){ //Write functie. Met deze functie wordt Data via de socket naar de server.php verzonden om zo in een json file te kunnen worden geschreven.
        $host = "127.0.0.1";
        $port = "20205";
		$sock = socket_create(AF_INET, SOCK_STREAM, 0); //socket openen.
		socket_connect($sock, $host, $port);

		socket_write($sock, $msg, strlen($msg)); //het versturen van de data in de vorm van ID,Value.

		socket_close($sock); //socket verbinding beindigen.		

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
				<input type="submit" name = "button1" class="button" value="Nightlight <?php global $arr; echo $arr[1]; //toont de huidige waarde van de corresponderende ID.?>"> <!--Led, Bed-->
					<?php
					if (isset($_POST['button1'])){global $arr; if ($arr[1] == 0){$arr[1] = 1;}else {$arr[1] = 0;}Write("1,$arr[1]"); refresh(0);}
					//Wanneer de knop wordt ingedrukt detecteerd bovenstaande functie dit, vervolgens wordt het ID geflipt, wordt deze weggeschreven naar server.php, en wordt de pagina ververst.
					//Dit principe wordt toegepast bij iedere grijze knop.
					?>
				<div class="led-group">
					<div class="Led-desc"> NightLight</div>
					<div class="led" id="Led1" value="Switch (Bed)"><p><?php global $arr; if($arr[2] == 1){echo "ON";}else{echo "OFF";} //$arr wordt aangeroepen en afhankelijk van de status (1 of 0) weergeeft het lampje "ON" of "OFF". Dit principe wordt toegepast bij iedere groene indicator.?></p></div> <!-- Switch, Bed-->
					
				</div>	
				<div class="led-group">
					<div class="led" value="Pressuresensor (Bed)"><p><?php global $arr; if($arr[3] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Pressure Sensor, Bed-->
					<div class="Led-desc"> Pressuresensor</div>
				</div>
			</div>
		</div>
		
		<div class="device">
		<h1>Chair</h1>
			<div class="content">
				
			<input type="submit" name = "button4" class="button" value="Vibrator <?php global $arr; echo $arr[4]; ?>"> <!-- Vibrator, Chair -->
					<?php
					if (isset($_POST['button4'])){global $arr; if ($arr[4] == 0){$arr[4] = 1;}else {$arr[4] = 0;}Write("4,$arr[4]"); refresh(0);}
					?>
			<input type="submit" name = "button5" class="button" value="Led (Chair) <?php global $arr; echo $arr[5]; ?>"> <!-- Led, Chair -->
					<?php
					if (isset($_POST['button5'])){global $arr; if ($arr[5] == 0){$arr[5] = 1;}else {$arr[5] = 0;}Write("5,$arr[5]"); refresh(0);}
					?>
				<div class="led-group">
					<div class="led" value="Pressuresensor (Chair)"><p><?php global $arr; if($arr[6] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Led, Lamp -->
					<div class="Led-desc"> Pressuresensor </div>
				</div>	
				<div class="led-group">
					<div class="led" value="Switch (Chair)"><p><?php global $arr; if($arr[7] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Switch, Chair -->
					<div class="Led-desc"> Chairlight </div>
				</div>	
			</div>
		</div>
		
		<div class="device">
		<h1>Lamp</h1>
			<div class="content">
			
			<input type="submit" name = "button8" class="button" value="Lamp <?php global $arr; echo $arr[8]; ?>"> <!-- Led, Lamp-->
					<?php
					if (isset($_POST['button8'])){global $arr; if ($arr[8] == 0){$arr[8] = 1;}else {$arr[8] = 0;}Write("8,$arr[8]"); refresh(0);}
					?>
				
				<div class="led-group">
					<div class="led" value="Motionsensor"><p><?php global $arr; if($arr[9] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Motion, Lamp -->
					<div class="Led-desc"> Motionsensor </div>
				</div>
			</div>
		</div>
		
		<div class="device">
		<h1>Column</h1>
			<div class="content">
			

			<input type="submit" name = "button10" class="button" value="Buzzer <?php global $arr; echo $arr[10]; ?>"> <!-- Buzzer, Column -->
					<?php
					if (isset($_POST['button10'])){global $arr; if ($arr[10] == 0){$arr[10] = 1;}else {$arr[10] = 0;}Write("10,$arr[10]");  refresh(0);}
					?>
			<input type="submit" name = "button11" class="button" value="Led (Column) <?php global $arr; echo $arr[11]; ?>"> <!-- Led, Column -->
					<?php
					if (isset($_POST['button11'])){global $arr; if ($arr[11] == 0){$arr[11] = 1;}else {$arr[11] = 0;}Write("11,$arr[11]");  refresh(0);}
					?>
				<div class="led-group">
					<div class="led" value="Switch (Column)"><p><?php global $arr; if($arr[12] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Switch, Column -->
					<div class="Led-desc"> Columnlight </div>
				</div>
				<div class="led-group">
					<div class="led" value="Smoke"><p><?php global $arr; if($arr[13] == 1){echo "ON";}else{echo "OFF";}?></p></div><!-- Smoke, Column -->
					<div class="Led-desc"> Smokedetector </div>
				</div>	
			</div>
		</div>
		
		<div class="device">
		<h1>Wall</h1>
			<div class="content">
			<input type="submit" name = "button14" class="button" value="LedStrip <?php global $arr; echo $arr[14]; ?>"> <!-- Ledstrip, Wall -->
					<?php
					if (isset($_POST['button14'])){global $arr; if ($arr[14] == 0){$arr[14] = 1;}else {$arr[14] = 0;}Write("14,$arr[14]");  refresh(0);}
					?>
			<input type="submit" name = "button15" class="button" value="Window <?php global $arr; echo $arr[15]; ?>"> <!-- Window, Wall -->
					<?php
					if (isset($_POST['button15'])){global $arr; if ($arr[15] == 0){$arr[15] = 1;}else {$arr[15] = 0;}Write("15,$arr[15]");  refresh(0);}
					?>
				<div class="led-group">
					<div class="led" value="Dimmer"><p><?php global $arr; if($arr[16] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Dimmer, Wall -->
					<div class="Led-desc"> Dimmer </div>
				</div>
				<div class="led-group">
					<div class="led" value="LDR"><p><?php global $arr; if($arr[17] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- LDR, Wall -->
					<div class="Led-desc"> LDR </div>
				</div>	
			</div>
		</div>
		
		<div class="device">
			<h1>Fridge</h1>
			<div class="content">
			<input type="submit" name = "button18" class="button" value="Cooler + Fan <?php global $arr; echo $arr[18]; ?>"> <!-- Cooler + Fan, Fridge -->
					<?php
					if (isset($_POST['button18'])){global $arr; if ($arr[18] == 0){$arr[18] = 1;}else {$arr[18] = 0;}Write("18,$arr[18]");  refresh(0);}
					?>
				<div class="led-group">
					<div class="led" value="Inner Temp"><p><?php global $arr; if($arr[19] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Temp binnen, Fridge -->
					<div class="Led-desc">Inner Temp.</div>
				</div>
				<div class="led-group">			
					<div class="led" value="Outer Temp"><p><?php global $arr; if($arr[20] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Temp buiten, Fridge -->
					<div class="Led-desc">Outer Temp.</div>
				</div>
				<div class="led-group">
					<div class="led" value="Door (Fridge)"><p><?php global $arr; if($arr[21] == 1){echo "ON";}else{echo "OFF";}?> </p></div> <!-- Doorsensor, Fridge -->
					<div class="Led-desc">Fridge Door</div>
				</div>
			</div>
		</div>
	</div>
	<div class="container-20">
		<div class="device" id="door">
		<h1>Door</h1>
			<div class="content">
				<!-- Uitgecommente code is voor de bewaker, maar maakt plaats voor de onderstaande keypad om de deur te openen.
					<input type="submit" name = "button22" class="button" value="Inner LED (Door) <?php global $arr; echo $arr[22]; ?>"> <!-- Inner Doorled, Door
					<?php
					if (isset($_POST['button22'])){global $arr; if ($arr[22] == 0){$arr[22] = 1;}else {$arr[22] = 0;}Write("22,$arr[22]");  refresh(0);}
					?>
					<input type="submit" name = "button23" class="button" value="Outer LED (Door) <?php global $arr; echo $arr[23]; ?>"> <!-- Outer Doorled, Door
					<?php
					if (isset($_POST['button23'])){global $arr; if ($arr[23] == 0){$arr[23] = 1;}else {$arr[23] = 0;}Write("23,$arr[23]");  refresh(0);}
					?>
					<input type="submit" name = "button24" class="button" value="Servo (Door) <?php global $arr; echo $arr[24]; ?>"> <!-- Servo, Door
					<?php
					if (isset($_POST['button24'])){global $arr; if ($arr[24] == 0){$arr[24] = 1;}else {$arr[24] = 0;}Write("24,$arr[24]");  refresh(0);}
					?>
						<div class="led-group">
							<div class="led" value="Inner Doorknob"><p><?php global $arr; if($arr[25] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Inner Doorknob, Door
							<div class="Led-desc">Inner Door</div>
						</div>
						<div class="led-group">
							<div class="led" value="Outer Doorknob"><p><?php global $arr; if($arr[26] == 1){echo "ON";}else{echo "OFF";}?></p></div> <!-- Outer Doorknob, Door
							<div class="Led-desc">Outer Door</div>
						</div>-->
			
				<div class="keypad"> <!-- Keypad dat gebruikt kan worden voor het van binnenuit openen van de deur. -->
				<div class="keyrow value">
					<?php
					function keypad($pad){ //keypad() krijgt de ingetoetste toets mee bij het aanroepen van de functie.
						global $arr;
						$key = $arr[27]; //in arr[27] wordt de pincode opgeslagen van vorige iteraties.
						if($pad == "Enter"){ //Wanneer de toets "Enter" is ingedrukt wordt de huidige code door deur.cpp uitgelezen en gecontroleerd op validiteit. de Raspberry pi zal bij een correcte code de deur openen.
							write("28,1");
						}
						else if($pad == "Reset"){ //Wanneer de toets "Reset" wordt ingedrukt wordt de $key leeg gemaakt voor een nieuwe poging.
							$key = "";
							write("27,$key");
						}
						else if(strlen($key) == 4){ //Wanneer $key een grote van 4 characters bereikt worden er geen nieuwe cijfers geaccepteerd. Een reset is nodig voor een nieuwe poging. of enter kan gebruikt worden om de code te valideren.
							//Don't add key.
							}
						else{
							$key = $key . $pad; //Wanneer tpets 0 tot 9 wordt gebruikt wordt deze toegevoegd aan de string. 
							write("27,$key");
							}
						
						refresh(0); //pagina verversen om huidige in beeld te brengen.
					}

						if ($arr[27] == ""){ //wanneer de array leeg is wordt "Enter PIN" in het veld getoont, wanneer het eerste character wordt ingevoerd wordt deze getoont.
							echo "Enter PIN";
							}
						else{
							echo $arr[27];
							}
					?>
					</div>
				<div class="keyrow">
						<input type="submit" name="key1" value="1" class="key m1"> <!-- "1" key, De daadwerkelijke keys. Werkt met het zelfde principe als de eerdere grijze knoppen maar gebruikt keypad() om de gewenste waarde weg te schrijven.-->
						<?php if (isset($_POST['key1'])){keypad(1);}?>
						<input type="submit" name="key2" value="2" class="key"><!-- "2" key -->
						<?php if (isset($_POST['key2'])){keypad(2);}?>
						<input type="submit" name="key3" value="3" class="key m2"><!-- "3" key -->
						<?php if (isset($_POST['key3'])){keypad(3);}?>
					</div>
				<div class="keyrow">
						<input type="submit" name="key4" value="4" class="key m1"><!-- "4" key -->
						<?php if (isset($_POST['key4'])){keypad(4);}?>
						<input type="submit" name="key5" value="5" class="key m"><!-- "5" key -->
						<?php if (isset($_POST['key5'])){keypad(5);}?>
						<input type="submit" name="key6" value="6" class="key m2"><!-- "6" key -->
						<?php if (isset($_POST['key6'])){keypad(6);}?>
					</div>
				<div class="keyrow">
						<input type="submit" name="key7" value="7"class="key m1"><!-- "7" key -->
						<?php if (isset($_POST['key7'])){keypad(7);}?>
						<input type="submit" name="key8" value="8" class="key m"><!-- "8" key -->
						<?php if (isset($_POST['key8'])){keypad(8);}?>
						<input type="submit" name="key9" value="9" class="key m2"><!-- "9" key -->
						<?php if (isset($_POST['key9'])){keypad(9);}?>
					</div>
				<div class="keyrow">
						<input type="submit" name="keyEnter" value="Enter" class="key m1 enter"><!-- "Enter" key --> 
						<?php if (isset($_POST['keyEnter'])){keypad('Enter');}?>
						<input type="submit" name="keyReset" value="Reset" class="key m reset"><!-- "Reset" key -->
						<?php if (isset($_POST['keyReset'])){keypad('Reset');}?>
						<input type="submit" name="key0" value="0" class="key m2"><!-- "0" key -->
						<?php if (isset($_POST['key0'])){keypad(0);}?>
					</div>
					<?php
						if ($arr[29] == 1){ //wanneer de ingevoerde waarde niet juist is schrijft deur.cpp een waarde van "1" weg naar ID 29, waardoor de tekst "Incorrect PIN" zichtbaar wordt.
							echo "Incorrect PIN";
							write("29,0"); //ID 29 resetten.
							}
						
					?>
				</div>
			
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
					<?php if (isset($_POST['alert3'])){global $arr; write("32,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[37] == 1){echo '<div class="alert red">Resident has requested aid (!)'; echo '<input type="submit" name = "alert8" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert8'])){global $arr; write("37,0"); refresh(0);}?>		
					
					<?php global $arr; if($arr[35] == 1){echo '<div class="alert orange">Resident must take his medicine (!)'; echo '<input type="submit" name = "alert6" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert6'])){global $arr; write("35,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[36] == 1){echo '<div class="alert orange" >Resident has not taken his medicine yet (!)'; echo '<input type="submit" name = "alert7" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert7'])){global $arr; write("36,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[34] == 1){echo '<div class="alert orange">Fridge has been open for too long (!)'; echo '<input type="submit" name = "alert5" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert5'])){global $arr; write("34,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[39] == 1){echo '<div class="alert green">A request was made to open the door (!)'; echo '<input type="submit" name = "alert10" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert10'])){global $arr; write("39,0"); refresh(0);}?>

					<?php global $arr; if($arr[33] == 1){echo '<div class="alert green">Massage requested during cooldown (!)'; echo '<input type="submit" name = "alert4" class="alertButton" value="Clear"> </div>';} ?>
					<?php if (isset($_POST['alert4'])){global $arr; write("33,0"); refresh(0);}?>
					
					<?php global $arr; if($arr[30] == 1){echo '<div class="alert green">Alarmclock currently active (!)'; echo '<input type="submit" name = "alert1" class="alertButton" value="Clear"> </div>';} ?>
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