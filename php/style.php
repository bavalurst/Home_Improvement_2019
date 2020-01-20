<?php header("Content-type: text/css"); ?>

.html{
  margin: 0;
  padding: 0;
  }
  
  body{
  margin: 0;
  padding: 0;
  font-family: 'Titillium Web', sans-serif;
  }
  
  .header{
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 50px;
  background-color: lightgrey;
  }
  
  .header h1{
  margin: 0px 0 0 15px;

  }
  
  .form{
  margin-top: 60px;
  text-align: left;
  }
  
  .footer{
  position: fixed;
  bottom: 0;
  left: 0;
  width: 100%;
  height: 50px;
  background-color: lightgrey;
  }
  
  .footer-form{
  float: right;
  }
  
  .entry{
  margin-top: 10px;
  float: left;	
  }
  
  .entry input{
  margin: 5px 15px 0 0;
  border: none;
  }
  
  .panel {
  margin-top: 50px;
  width: 100%;
  min-height: 500px;	
  }
  
.button{
    background-color: grey;
    border: none;
    color: white;
    padding: 15px 32px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    width: 200px;
	height: 50px;
    margin: 0 0 5px;
	border-radius: 50px;
}

.button:focus {
    outline: none;
	background-color: #4CAF50;
}

.led-group {
    background-color: lightgrey;
    border: none;
	width: 200px;
	height: 50px;
    
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
	border-radius: 50px;

}
  
.led {
  background-color: #4CAF50;
  border: none;
  color: white;
  text-align: center;
  display: inline-block;
  font-size: 16px;
  Width: 50px;
  Height: 50px;
  border-radius: 50px; 
  float: right;
  }
  
.led p {
  line-height: 17.5px;
}
.Led-desc {
  width: 150px;
  float: left;
  text-align: center;
  font-weight: bold;
  line-height: 50px;
  }
  
  .button-m{
  background-color: #4CAF50;
  border: #4CAF50 1.5px solid;
  color: white;
  border-radius: 50px;
  }
  
  .device{
  width: 220px;
  float: left;
  margin-top: 5px;
  background-color: #E8E8E8;
  border-radius: 25px; 
  margin-left: 5px;
  }
  
  .device h1{
   font-size: 25px;
   padding: 0 0 0 10px;
  }
  
@media only screen and (max-width: 600px) {
  .device{
	  width: 100%;
	  padding: 10px;
	  height: 275px;
	  float: left;
	  margin-top: 25px;
}
} 
  .content{
    padding: 10px;
	padding-top: 0;
  }

#door{
width: calc(100% - 10px);
height: calc(100% - 10px);
	
}
.container-80{
	position: absolute;
	display: inline-block;
	width: 75%;
	height: calc(100% - 100px);
	margin: 50px 0 0 0;
	float: left;
}

.container-20{
	position: absolute;
	right: 0;
	display: inline-block;
	width: 25%;
	height: calc(100% - 100px);
	margin: 50px 0 0 0;
	float: right;
}

.keypad{
	position: inherit;
	width: 200px;
	height: 273px;
	border-radius: 25px; 
}

.keyrow{
    background-color: darkgrey;
    border: none;
	width: 200px;
	height: 50px;
    
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
	border-radius: 50px;
}

.keyrow.value{
    background-color: white;
    border: none;
	width: 200px;
	height: 50px;
    
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 25px;
	border-radius: 50px;
	
	line-height: 50px;
	margin: 0 0 5px;
}

.key{
	display block;
	width: 50px;
	height: 50px;
	background-color: grey;
	float: left;
	line-height: 50px;
	text-align: center;
	border-radius: 50px;
	border: none;
	
	font-size: 15px;
	font-weight: bold;
	color: white;
}
.key.m1{
	margin: 0 10px 0 15px;
}
.key.m2{
	margin: 0 15px 0 10px;
}

.key.enter{
background-color: #4CAF50;
}

.key.reset{
background-color: #FF5733;
}

.key:focus {
    outline: none;
	background-color: #4CAF50;
}

.alert{
  color: white;
  border-radius: 50px;
  line-height: 20px;
  margin: -10px 0 12px 0;
  }
  
.alertButton{
  line-height: 19.5px;
  background-color: grey;
  border: grey 2px solid;
  color: white;
  border-radius: 50px;
  float: right;
  padding: 0 5px 0 5px;
  margin: -1px -5px 0 0;
  }
  
.alert.red{
   background-color: #FF5733;
   border: #FF5733 1.5px solid;
}

.alert.orange{
   background-color: Orange;
   border: Orange 1.5px solid;
}

.alert.green{
   background-color: #4CAF50;
   border: #4CAF50 1.5px solid;
}
  
	