<?php

require_once __DIR__ . '/db.class.php';

create_table_users();
create_table_utakmice();
create_table_tiketi();
create_table_relacija();

// ------------------------------------------
function create_table_users()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare(
			'CREATE TABLE IF NOT EXISTS Kladionica_Users (' .
			'id int NOT NULL PRIMARY KEY AUTO_INCREMENT,' .
			'username varchar(20) NOT NULL,' .
            'password_hash varchar(255) NOT NULL,' .
            'email varchar(50) NOT NULL,'.
            'iznos float NOT NULL)'
		);

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (create_table_users): " . $e->getMessage() ); }

	echo "Napravio tablicu users.<br />";
}

function create_table_utakmice()
{
    $db = DB::getConnection();
    
	try
	{
		$st = $db->prepare(
			'CREATE TABLE IF NOT EXISTS Kladionica_Utakmice (' .
			'id int NOT NULL PRIMARY KEY AUTO_INCREMENT,' .
			'domaci varchar(50) NOT NULL,' .
			'gosti varchar(50) NOT NULL,' .
            'kvota1 float NOT NULL,' .
            'kvotaX float NOT NULL, ' .
            'kvota2 float NOT NULL,' . 
            'kvota1x float NOT NULL,' .
            'kvota2x float NOT NULL,' .
            'sport varchar(50) NOT NULL)'
		);

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (create_table_utakmice): " . $e->getMessage() ); }

	echo "Napravio tablicu utakmice.<br />";
}


function create_table_tiketi()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare(
			'CREATE TABLE IF NOT EXISTS Kladionica_Tiketi (' .
			'id int NOT NULL PRIMARY KEY AUTO_INCREMENT,' .
			'user_id int NOT NULL,' .
            'uplaceni_iznos float NOT NULL,' .
            'moguci_dobitak float NOT NULL,' .
            'vrijeme_uplate date NOT NULL,' .
            'koeficijent float NOT NULL)'
		);

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (create_table_tiketi): " . $e->getMessage() ); }

	echo "Napravio tablicu tiketi.<br />";
}


function create_table_relacija()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare(
			'CREATE TABLE IF NOT EXISTS Kladionica_Relacija (' .
			'id_tiket int NOT NULL,' .
			'id_utakmica int NOT NULL,' .
			'odabrani_ishod varchar(10) NOT NULL,' .
			'konacni_ishod varchar(10) NOT NULL,' .
			'primary key (id_tiket, id_utakmica))'
		);

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error (clear_table_relacija): " . $e->getMessage() ); }

	echo "Napravio tablicu relacija.<br />";
}

?>