<?php

// Controllo se i dati inviati da Arduino sono vuoti
if(empty($_GET["t"]))
    $_GET["t"] = 'NoTemperature';
if(empty($_GET["h"]))
    $_GET["h"] = 'NoHumidity';

// Salvo i dati precedentemente controllati
$temperature = $_GET['t'];
$humidity = $_GET['h'];
//$pressure = $_POST["p"]; <- Implementazione con la pressione

// Info Database
$host = "your_host";
$username = "your_user";
$password = "your_pass";
$database = "db_name";

// Istanzio la connessione al database
$connection = new mysqli($host, $username, $password, $database);

// Controllo eventuali errori
if($connection->connect_error)
    die("Connection failed: " . $connection->connect_error . "with error: " . $connection->connect_errno . "\n");
echo "Connected successfully\n";

// Query da inviare al database contenente i dati registrati dal DHT22, ricevuti da Arduino
$query = "INSERT INTO arduino_weather(temperature, humidity, date_time) ". // "INSERT INTO arduino_weather(temperature, humidity, pressure, date_time) ". <- Query con l'aggiunta della pressione
         "VALUES('{$temperature}', '{$humidity}', NOW());"; // "VALUES('{$temperature}', '{$humidity}', '{$pressure}', NOW());";

// Invio della query con controllo
if($result = mysqli_query($connection, $query))
    echo "Query sent successfully to the Database\n";
else 
    echo "Something went wrong during the query send to the Database\n";

// Chiusura della connessione (non è necessario perchè avviene automaticamente)
$connection->close();

echo $query;

?>