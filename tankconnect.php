<?php

$servername= "localhost";
$username= "root";
$password= "";
$dbname="WTL";

$con = mysqli_connect($servername,$username,$password,$dbname);

if(!$con){
	echo "Error: " . mysqli_connect_error();
	exit();
}
else echo "Connection Success!";

$Owner=" ";
$Location=" ";
$Reading=" ";
$Time=" ";

if(isset($_GET['Owner'])){
$Temperature=$_GET['Owner'];
}

if(isset($_GET['Location'])){
$Humidity=$_GET['Location'];
}

if(isset($_GET['Reading'])){
$Temperature=$_GET['Reading'];
}

if(isset($_GET['Time'])){
$Temperature=$_GET['Time'];
}

$sql = "INSERT INTO `TankSystem` (`Owner`,`Location`,`Reading`,`Time`) 
VALUE ('{$Owner}','{$Location}','{$Reading}','{$Time}')";

if (mysqli_query($con, $sql)){
    echo "Database updated successfully";
}
else
echo "Error! Could not update";

?>
