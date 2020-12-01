<?php

// skripta koja brise podatke iz svih tablica
require_once __DIR__ . '/db.class.php';

//clear_table_users();
clear_table_utakmice();
clear_table_tiketi();
clear_table_relacija();

// ------------------------------------------

function clear_table_users()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare('DELETE FROM Kladionica_Users');

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (clear_table_users): " . $e->getMessage() ); }

	echo "Ocistio tablicu users.<br />";
}

function clear_table_utakmice()
{
    $db = DB::getConnection();
    
	try
	{
		$st = $db->prepare('DELETE FROM Kladionica_Utakmice');

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (clear_table_utakmice): " . $e->getMessage() ); }

	echo "Ocistio tablicu utakmice.<br />";
}


function clear_table_tiketi()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare('DELETE FROM Kladionica_Tiketi');

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (clear_table_tiketi): " . $e->getMessage() ); }

	echo "Ocistio tablicu tiketi.<br />";
}


function clear_table_relacija()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare('DELETE FROM Kladionica_Relacija');

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (clear_table_relacija): " . $e->getMessage() ); }

	echo "Ocistio tablicu relacija.<br />";
}

?>