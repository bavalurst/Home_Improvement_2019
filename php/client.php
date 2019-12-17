<!DOCTYPE html>
<html>
<head>
 <title></title>
</head>
<body>

 <div align="center"></div>

 <form method="post">
  <table>
   <tr>
    <td>
     <label>ID</label>
     <input type="text" name="ID">
     <label>Value</label>
     <input type="text" name="txtMessage">
     <input type="submit" name="btnSend" value="Send">
    </td>
   </tr>
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
   ?>
   <tr>
    <td>
     <textarea rows="10" cols="30"><?php echo @$reply; ?></textarea>
    </td>
   </tr>
  </table>
 </form>

</body>
</html>