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

$sql_check = "SELECT `TankID` FROM `TankInformation` WHERE `TankID` = {$TankID}";
$sql_insert  = "INSERT INTO `TankInformation` (`TankID`,`Owner`,`Location`) VALUES ('{$TankID}','{$Owner}','{$Location}')";


$id_present_check = mysqli_query($con, $sql_check);

if ($id_present_check) {
	if (mysqli_num_rows($id_present_check) == 1) {
		echo "Data already present\n";
	} else {
		if (mysqli_query($con, $sql_insert )){
			echo "Data inserted successfully\n";
		}
		else {		
			echo "Error! Could not update\n";
		}
	}

} else {
	echo "Could not query database\n";
	exit(1);
}

?>