<?php

//connect to the SQL database and store a list of runIDs in array $rows.
$con = pg_connect("host=localhost dbname=turbiduino user=joemellor password=lamarama");
$query = "SELECT DISTINCT run_id FROM READINGS ORDER BY run_id DESC";
$result = pg_query($con, $query);
$rows = pg_fetch_all($result);

//pass on the connection handle and rows array to create a menu.
echo  generateSelect('runid', $rows, $con);


//generates a drop-down menu by formatting runIDs and passes on a connection to the database to the next php script.
function generateSelect($name = '', $options = array(),$con) {
    //call the script 'display.php' on submit.
    $html = '<form method = "post" action = "display.php">';
    $html .= '<select name="'.$name.'">';

    //iterate through $rows, allowing you to get data for each reading.
    foreach ($options as $key => $value) {
        $runid = $value[run_id];
	   //parse the string runID into a readable form.
        $str = substr($runid,6,2)."/". substr($runid,4,2)."/".substr($runid,0,4)." on ".substr($runid,8,2).":".substr($runid,10);
        $html .= '<option value='.$runid.'>'.$str.'</option>';
        }

    $html .= '</select>';
    $html .= '<INPUT TYPE = "submit" name = "submit" /> </form>';
    return $html;
}

?>
