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

$TankID=" ";
$Reading=" ";

if(isset($_GET['TankID'])){
$TankID=$_GET['TankID'];
}

if(isset($_GET['Reading'])){
$Reading=$_GET['Reading'];
}

$sql = "INSERT INTO `TankSystem` (`TankID`,`Reading`) VALUE ('{$TankID}','{$Reading}')";

if (mysqli_query($con, $sql)){
    echo "Database updated successfully";
}
else
echo "Error! Could not update";

?>
