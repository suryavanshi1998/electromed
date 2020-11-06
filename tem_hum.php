<?php
$Temp=$_POST["temperature"];
// create variable for receaving temperature data
$Humidity=$_POST["humidity"];
//create variable for receaving humidity data
$Write="<p>temperature : " . $Temp . "Celcius </p>". "<p>"Humidity : " . $Humidity . " % </p>;
// Create HTML for display data
file_put_contents('sensor.html',$Write);

?>