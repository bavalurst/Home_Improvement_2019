<!DOCTYPE html>
<html>
<head>
 <title>PJSysDev V2.1.2</title>
 <link rel="stylesheet" href="index.css">
 
 <?php
	header('Refresh: 3; url=client.php');
	$arr = '1';
	
	$host = "127.0.0.1";
    $port = "20205";
	$sock = socket_create(AF_INET, SOCK_STREAM, 0);
	socket_connect($sock, $host, $port);

	socket_write($sock, "update", strlen("update"));
		
	$reply = socket_read($sock, 1924);
	
	$arr = explode(" ",$reply);
	//print_r($arr);
	$GLOBALS['status'] = $arr[0];

	 

    $host = "127.0.0.1";
    $port = "20205";

    if (isset($_POST['btnSend'])) {
     $msg2 = $_REQUEST['txtMessage'];
     $msg = $_REQUEST['ID'];
     $sock = socket_create(AF_INET, SOCK_STREAM, 0);
     socket_connect($sock, $host, $port);

     socket_write($sock, $msg, strlen($msg));           // schrijf bericht gesplitst door komma
     socket_write($sock, ",", strlen($msg));
     socket_write($sock, $msg2, strlen($msg2));

     $reply = socket_read($sock, 1924);
     $reply = trim($reply);

     $reply = "Server says:\t".$reply;
    }

    function Write($msg){
        $host = "127.0.0.1";
        $port = "20205";
		$sock = socket_create(AF_INET, SOCK_STREAM, 0);
		socket_connect($sock, $host, $port);

		socket_write($sock, $msg, strlen($msg));           // stuur het bericht

		$reply = socket_read($sock, 1924);
		$reply = trim($reply);

		$reply = "Server says:\t".$reply;				// zichtbaar in terminal
		
    }
    
    if (isset($_POST['toggle1'])){						// testknop
        Write("0,5");	
    }
	
	//als timer voorbij is: doe Read()
	
	function Read() {
		

		
		
		//lees json file
		//doe lampjes
	}
	
	function Toggle(){
	 if ($status == 0){
		$status = 1;
	 }
	 else {
		$status = 0;
	 }
	}
   ?>
</head>
<body>

<div class="header">
<h1>Dashboard</h1>
</div>

 <form method="post">
	<div class="device">
		<h1>Bed</h1>
			<div class="content">
				<input type="submit" name = "button1" class="button" value="Nightlight">
					<?php
					if (isset($_POST['button1'])){
						
						if ($status == 0){
						$status = 1;
						}
						else {
						$status = 0;
						}
						
						Write("1,$status");
					
						}
					echo $status;
					?>
				<input type="submit" name = "button2" class="button" value="Pressuresensor (Bed)">
					<?php
					if (isset($_POST['button2'])){
					Write("2,0");
					}
					?>
			</div>
		</div>
		
		<div class="device">
		<h1>Chair</h1>
			<div class="content">
				<input type="submit" name = "button3" class="button" value="Pressuresensor (Chair)">
					<?php
					if (isset($_POST['button3'])){
					Write("3,0");
					}
					?>
			<input type="submit" name = "button4" class="button" value="Vibrator">
					<?php
					if (isset($_POST['button4'])){
					Write("4,0");
					}
					?>
			<input type="submit" name = "button5" class="button" value="Chairlight">
					<?php
					if (isset($_POST['button5'])){
					Write("5,0");
					}
					?>
			</div>
		</div>
		
		<div class="device">
		<h1>Lamp</h1>
			<div class="content">
			<input type="submit" name = "button6" class="button" value="Lamp">
					<?php
					if (isset($_POST['button6'])){
					Write("6,0");
					}
					?>
			<input type="submit" name = "button7" class="button" value="Motionsensor (Lamp)">
					<?php
					if (isset($_POST['button7'])){
					Write("7,0");
					}
					?>
			</div>
		</div>
		
		<div class="device">
		<h1>Column</h1>
			<div class="content">
			<input type="submit" name = "button8" class="button" value="Switch (Pillar)">
					<?php
					if (isset($_POST['button8'])){
					Write("8,0");
					}
					?>
			<input type="submit" name = "button9" class="button" value="Smoke Detector">
										<?php
					if (isset($_POST['button9'])){
					Write("9,0");
					}
					?>
			<input type="submit" name = "button10" class="button" value="Zooomer">
					<?php
					if (isset($_POST['button10'])){
					Write("10,0");
					}
					?>
			</div>
		</div>
		
		<div class="device">
		<h1>Wall</h1>
			<div class="content">
			<input type="submit" name = "button11" class="button" value="LDR">
					<?php
					if (isset($_POST['button11'])){
					Write("11,0");
					}
					?>
			<input type="submit" name = "button12" class="button" value="LED-strip">
					<?php
					if (isset($_POST['button12'])){
					Write("12,0");
					}
					?>
			<input type="submit" name = "button13" class="button" value="Window">
					<?php
					if (isset($_POST['button13'])){
					Write("13,0");
					}
					?>
			<input type="submit" name = "button14" class="button" value="Dimmer">
					<?php
					if (isset($_POST['button14'])){
					Write("14,0");
					}
					?>
			</div>
		</div>
		
		<div class="device">
			<h1>Fridge</h1>
			<div class="content">
			<input type="submit" name = "button15" class="button" value="Door (Fridge)">
					<?php
					if (isset($_POST['button15'])){
					Write("15,0");
					}
					?>
			<input type="submit" name = "button16" class="button" value="Cooling (Heatsink)">
					<?php
					if (isset($_POST['button16'])){
					Write("16,0");
					}
					?>
			<input type="submit" name = "button17" class="button" value="Cooling (Fan)">
					<?php
					if (isset($_POST['button17'])){
					Write("17,0");
					}
					?>
			<input type="submit" name = "button18" class="button" value="Temperature">
					<?php
					if (isset($_POST['button18'])){
					Write("18,0");
					}
					?>
			</div>
		</div>
		
		<div class="device">
		<h1>Door</h1>
			<div class="content">
			<input type="submit" name = "button19" class="button" value="Inner Doorknob">
					<?php
					if (isset($_POST['button19'])){
					Write("19,0");
					}
					?>
			<input type="submit" name = "button20" class="button" value="Outer Doorknob">
					<?php
					if (isset($_POST['button20'])){
					Write("20,0");
					}
					?>
			<input type="submit" name = "button21" class="button" value="Servo (Door)">
					<?php
					if (isset($_POST['button21'])){
					Write("21,0");
					}
					?>
			</div>	
		</div>

        <div class="footer">
		
<form method="post">
    <div class=" footer-form">
    <label>ID</label>

    <input type="text" name="ID">
    <label>Value</label>
    <input type="text" name="txtMessage">
    <input type="submit" name="btnSend" value="Send">
    <input type="submit" name="toggle1" value="Turn On"/>
        
        <?php
             if(isset($_POST['update'])){
                 Write($_POST['ID'],$_POST['VALUE']);	 
             }
        ?>
    </div>
</form>

</div>
  
   <tr>
    <td>
     <textarea rows="10" cols="30"><?php echo @$reply; ?></textarea>
    </td>
   </tr>


</body>
</html>