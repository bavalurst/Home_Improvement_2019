<?php

 $host = "127.0.0.1";
 $port = "20205";
 set_time_limit(0);


 $sock = socket_create(AF_INET, SOCK_STREAM, 0) or die("Could not create socket\n");
 $result = socket_bind($sock, $host, $port) or die("Could not bind to socket\n");

 $result = socket_listen($sock, 3) or die("Could not setup socket listener\n");

 class Chat {
  function readline() {
   return rtrim(fgets(STDIN));
  }
 }

 do {
  $accept = socket_accept($sock) or die("Could not accept incoming connection\n");
  $msg = socket_read($accept, 1024) or die("Could not read input\n");

if($msg == "update") {
	echo "Update requested\n";
	$JsonData = json_decode(file_get_contents("results.json"), true);
	print_r($JsonData);
	
	//assigning value to the array  
	$arr = $JsonData;  
  
	$send = implode(" ",$arr);// Use of implode function 
	
	socket_write($accept, $send, strlen($send)) or die("Could not write output\n");
}
else{
//$file = "results.json";
$jsonString = file_get_contents('results.json');  // file openen
$data = json_decode($jsonString, true);
$msg2 = explode(',', $msg);                       // bericht ui client splitten op kommas

$ID = $msg2[0];                                   // eerste deel is ID
$Value = $msg2[1];                                // tweede deel is de aan te passen waarde

$data[$ID] = $Value;

$newJsonString = json_encode($data);
file_put_contents('results.json', $newJsonString);



  $msg = trim($msg);
  echo "Client Says:\t".$msg."\n\n";
 }

  //Dit hieronder is voor als je eerst een reply wil
//   $line = new Chat();
//   echo "Enter reply:\t";
//   $reply=$line->readline();

//   socket_write($accept, $reply, strlen($reply)) or die("Could not write output\n");
 }
 while(true);

 socket_close($accept, $sock);

?>