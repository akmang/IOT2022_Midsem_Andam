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
$TankID=" ";

if(isset($_GET['TankID'])){
$TankID=$_GET['TankID'];
}

if(isset($_GET['Owner'])){
$Owner=$_GET['Owner'];
}

if(isset($_GET['Location'])){
$Location=$_GET['Location'];
}

$sql = "INSERT INTO `TankInformation` (`TankID`,`Owner`,`Location`) VALUE ('{$TankID}','{$Reading}','{$Location}')";

if (mysqli_query($con, $sql)){
    echo "Database updated successfully";
}
else
echo "Error! Could not update";

?>
