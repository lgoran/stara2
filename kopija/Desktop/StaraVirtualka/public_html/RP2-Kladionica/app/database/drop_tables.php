<?php

require_once __DIR__ . '/db.class.php';

drop_table_users();
drop_table_utakmice();
drop_table_tiketi();
drop_table_relacija();

// ------------------------------------------

function drop_table_users()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare('DROP TABLE Kladionica_Users');

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (drop_table_users): " . $e->getMessage() ); }

	echo "Obrisao tablicu users.<br />";
}

function drop_table_utakmice()
{
    $db = DB::getConnection();
    
	try
	{
		$st = $db->prepare('DROP TABLE Kladionica_Utakmice');

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (drop_table_utakmice): " . $e->getMessage() ); }

	echo "Obrisao tablicu utakmice.<br />";
}


function drop_table_tiketi()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare('DROP TABLE Kladionica_Tiketi');

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (drop_table_tiketi): " . $e->getMessage() ); }

	echo "Obrisao tablicu tiketi.<br />";
}


function drop_table_relacija()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare('DROP TABLE Kladionica_Relacija');

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (drop_table_relacija): " . $e->getMessage() ); }

	echo "Obrisao tablicu relacija.<br />";
}

?>