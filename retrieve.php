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
    
    if(isset($_GET['Owner'])){
    $Owner=$_GET['Owner'];
    }
    
    if(isset($_GET['Location'])){
    $Location=$_GET['Location'];
    }
    
    
    $data=array();        

	$sql_latest = mysqli_query($con,"SELECT TankInformation.TankID,TankSystem.Reading, TankInformation.Owner,TankInformation.Location FROM TankInformation,TankSystem WHERE TankInformation.TankID = TankSystem.TankID ORDER BY TankSystem.Time DESC LIMIT 1");
    
    $row=mysqli_fetch_object($sql_latest);
    while ($row)
    {         
        
        echo " 
        <table style='width:100%'>
        <tr>
            <td> {$row->TankID}</td> 
            <td> {$row->Reading}</td> 
            <td> {$row->Owner}</td> 
            <td> {$row->Location}</td> 
        </tr>
        ";
        $row=mysqli_fetch_object($q);
    }
    echo " </table>";
    }
