<?php

//get the unique id of the run requested and access run data from database.
$runid = $_POST["runid"];
$con = pg_connect("host=localhost dbname=turbiduino user=joemellor password=lamarama");
$query = "SELECT * FROM readings WHERE run_id IN ('$runid')";
$result = pg_query($con, $query);
//store the resulting data in the array $rows.
$rows = pg_fetch_all($result);

//lay out the 'recent readings' table.
echo "number of readings: ";
$size = count($rows);
echo $size;
echo '</br></br> recently: (most recent at top) </br> <table border = "1">';
echo "<tr><td> baseline reading </td> <td> current reading </td> <td> hours elapsed </td> <td> temperature(C) </td> <td> doublings </td> </tr>";

//fill in the 'recent readings' table.
for($counter = $size-1; $counter > $size - 6; $counter -= 1) {
        $value = $rows[$counter];
        //convert seconds to hours and format to 3dp.
        $hours = $value[time]/3600;
        $hours = number_format((float)$hours, 3, '.', ',');
        echo "<tr> <td>".$value[baseline_read]."</td> <td>".$value[current_read]."</td> <td>".$hours."</td> <td>".$value[temperature]."</td> <td>".$value[doublings]."</td> </tr>";
}
echo "</table>";


//initialize the 'all readings' table.
echo "</br></br> all readings: (most recent at bottom)";
echo '</br><table border = "1">';
echo "<tr><td> baseline reading </td> <td> current reading </td> <td> hours elapsed </td> <td> temperature(C) </td> <td> doublings </td> </tr>";

//fill in the 'all readings' table.
foreach($rows as $value) {
        $hours = $value[time]/3600;
        $hours = number_format((float)$hours, 3, '.', ',');

echo "<tr> <td>".$value[baseline_read]."</td> <td>".$value[current_read]."</td> <td>".$hours."</td> <td>".$value[temperature]."</td> <td>".$value[doublings]."</td> </tr>"; }
echo "</table>";

?>
