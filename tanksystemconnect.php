<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "WTL";

$con = mysqli_connect($servername, $username, $password, $dbname);

if (!$con) {
	echo "Error: " . mysqli_connect_error();
	exit();
};

$TankID = " ";
$Reading = " ";

if (isset($_GET['TankID'])) {
	$TankID = $_GET['TankID'];
}

if (isset($_GET['Reading'])) {
	$Reading = $_GET['Reading'];
}

$sql = "INSERT INTO `TankSystem` (`TankID`,`Reading`) VALUE ('{$TankID}','{$Reading}')";


 if (mysqli_query($con, $sql)){
     echo "Database updated successfully";
 }
 else
 echo "Error! Could not update";

function get_latest()
{
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "WTL";

	$con = mysqli_connect($servername, $username, $password, $dbname);

	$sql_latest = "SELECT TankInformation.TankID,TankSystem.Reading, TankInformation.Owner,TankInformation.Location FROM TankInformation,TankSystem WHERE TankInformation.TankID = TankSystem.TankID ORDER BY TankSystem.Time DESC LIMIT 1";

	$result = mysqli_query($con, $sql_latest);
	$result1 = mysqli_fetch_all($result, MYSQLI_ASSOC);

	$i = 0;
	while ($i < count($result1)) {
		echo "<tr>";
		echo "<td>" . $result1[$i]['TankID'] . "</td>";
		echo "<td>" . $result1[$i]['Reading'] . "</td>";
		echo "<td>" . $result1[$i]['Owner'] . "</td>";
		echo "<td>" . $result1[$i]['Location'] . "</td>";

		echo "</tr>";
		$i++;
	};

	
};
?>