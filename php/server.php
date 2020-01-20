<?php

 $host = "127.0.0.1"; //host en port defineren.
 $port = "20205";
 set_time_limit(0);


 $sock = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n"); //socket openen.
 $result = socket_bind($sock, $host, $port) or die("Could not bind to socket\n");

 $result = socket_listen($sock, 3) or die("Could not setup socket listener\n"); //luisteren naar de socket voor inkomende berichten van client.php
 class Chat {
  function readline() {
   return rtrim(fgets(STDIN));
  }
 }

do { //binnengekomen bericht opvangen en interpreteren.
  $accept = socket_accept($sock) or die("Could not accept incoming connection\n");
  $msg = socket_read($accept, 1024) or die("Could not read input\n");

if($msg == "update") { //Na het verversen van de pagina stuurt client.php een "update" request om de laatste waarde uit van de actuatoren en sensoren op te vragen.
	//echo "Update requested\n";
	
	$jsonString1 = file_get_contents('data/actuator.json');  // actuatoren ophalen.
	$jsonString2 = file_get_contents('data/sensor.json'); //sensoren ophalen.
	$data2 = json_decode($jsonString2, true); //json data omzetten naar array.
	
	foreach($data1 as $key => $value) { //waarden van de ene array bij de andere voegen
		//echo "key: $key \n";
		//echo "value: $value \n";
		$data2[$key] = $value;
	}

	ksort($data2); //array op volgorde van ID (Key) sorteren.
	print_r($data2);
		
	$send = implode(" ",$data2);// er wordt gebruik gemaakt van implode() om de array om te zetten naar een string.
	
	socket_write($accept, $send, strlen($send)) or die("Could not write output\n"); //de string wordt verzonden naar client.php om gebruikt te worden in het dashboard.
}

else{ //de server.php mag alleen naar actuatoren schrijven, sensoren kan hij enkel ophalen en versturen naar de client.php om gebruikt te worden in het dashboard.
	$jsonString = file_get_contents('data/actuator.json');  // actuatoren openen
	$data = json_decode($jsonString, true);
	$msg2 = explode(',', $msg);                       // bericht ui client splitten op kommas, 		bijvoorbeeld "15,1".

	$ID = $msg2[0];                                   // eerste deel is ID, 						bijvoorbeeld "15".
	$Value = $msg2[1];                                // tweede deel is de aan te passen waarde, 	bijvoorbeeld "1".

	$data[$ID] = $Value;

	$newJsonString = json_encode($data);
	file_put_contents('data/actuator.json', $newJsonString); //uitgesplitste waarden naar actuator.json schrijven om geinterpreteerd te kunnen worden door De raspberry Pi.

	$msg = trim($msg);
	echo "Client Says:\t".$msg."\n\n";
 }

  socket_write($accept, $reply, strlen($reply)) or die("Could not write output\n");
 }
 while(true);

 socket_close($accept, $sock); //socket sluiten.

?>