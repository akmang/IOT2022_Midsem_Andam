<table class="table" style='width:100%'>
<thead>
        <tr>
            <th scope="col">TankID</th>
            <th scope="col">Water Level</th>
            <th scope="col">Owner</th>
            <th scope="col">Location</th>
        </tr>
    </thead>
    <tbody>
        <?php

        include("tanksystemconnect.php");
        get_latest();
        ?>
    <tbody>


</table>