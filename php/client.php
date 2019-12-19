<!DOCTYPE html>
<html>
<head>
 <title>PJSysDev V2.1.2</title>
 <link rel="stylesheet" href="index.css">
</head>
<body>

<div class="header">
<h1>Dashboard</h1>
</div>

 <form method="post">


     <div class="device">
		<h1>Bed</h1>
			<div class="content">
			<input type="button", name = "button1", class="button" value="Nightlight">
			<input type="button", name = "button2", class="button" value="Pressuresensor (Bed)">
			</div>
		</div>
		
		<div class="device">
		<h1>Chair</h1>
			<div class="content">
			<input type="button", name = "button3", class="button" value="Pressuresensor (Chair)">
			<input type="button", name = "button4", class="button" value="Vibrator">
			<input type="button", name = "button5", class="button" value="Chairlight">
			</div>
		</div>
		
		<div class="device">
		<h1>Lamp</h1>
			<div class="content">
			<input type="button", name = "button6", class="button" value="Lamp">
			<input type="button", name = "button7", class="button" value="Motionsensor (Lamp)">
			</div>
		</div>
		
		<div class="device">
		<h1>Pillar</h1>
			<div class="content">
			<input type="button", name = "button8", class="button" value="Switch (Pillar)">
			<input type="button", name = "button9", class="button" value="Smoke Detector">
			<input type="button", name = "button10", class="button" value="Zooomer">
			</div>
		</div>
		
		<div class="device">
		<h1>Wall</h1>
			<div class="content">
			<input type="button", name = "button11", class="button" value="LDR">
			<input type="button", name = "button12", class="button" value="LED-strip">
			<input type="button", name = "button13", class="button" value="Window">
			<input type="button", name = "button14", class="button" value="Dimmer">
			</div>
		</div>
		
		<div class="device">
			<h1>Fridge</h1>
			<div class="content">
			<input type="button", name = "button15", class="button" value="Door (Fridge)">
			<input type="button", name = "button16", class="button" value="Cooling (Heatsink)">
			<input type="button", name = "button17", class="button" value="Cooling (Fan)">
			<input type="button", name = "button18", class="button" value="Temperature">
			</div>
		</div>
		
		<div class="device">
		<h1>Door</h1>
			<div class="content">
			<input type="button", name = "button19", class="button" value="Inner Doorknob">
			<input type="button", name = "button20", class="button" value="Outer Doorknob">
			<input type="button", name = "button21", class="button" value="Servo (Door)">
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
   <?php
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

   ?>
   <!-- <tr>
    <td>
     <textarea rows="10" cols="30"><?php echo @$reply; ?></textarea>
    </td>
   </tr> -->


</body>
</html>