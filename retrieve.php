<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "WTL";

$con = mysqli_connect($servername, $username, $password, $dbname);

$TankID = " ";
$Reading = " ";

if (isset($_GET['TankID'])) {
    $TankID = $_GET['TankID'];
}

if (isset($_GET['Reading'])) {
    $Reading = $_GET['Reading'];
}

if (isset($_GET['Owner'])) {
    $Owner = $_GET['Owner'];
}

if (isset($_GET['Location'])) {
    $Location = $_GET['Location'];
}


$sql = "SELECT TankInformation.TankID,TankSystem.Reading, TankInformation.Owner,TankInformation.Location FROM TankInformation,TankSystem WHERE TankInformation.TankID = TankSystem.TankID ORDER BY TankSystem.Time DESC LIMIT 1";
$result = mysqli_query($con, $sql);



$row = mysqli_fetch_object($result);

echo" <table style='width:100%'>
   
 <tr>
<th> TankID</th> 
<th> Reading</th> 
<th> Owner</th> 
<th> Location</th> 
</tr>";

while ($row) {
    echo " 
        
        <tr>
            <td> {$row->TankID}</td> 
            <td> {$row->Reading}</td> 
            <td> {$row->Owner}</td> 
            <td> {$row->Location}</td> 
        </tr>
        ";
    $row = mysqli_fetch_object($result);
}
echo " </table>";
