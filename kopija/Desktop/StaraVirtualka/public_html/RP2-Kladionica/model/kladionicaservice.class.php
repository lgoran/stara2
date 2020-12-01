<?php

require_once __DIR__ . '/../app/database/db.class.php';
require_once __DIR__ . '/user.class.php';
require_once __DIR__ . '/utakmice.class.php';
require_once __DIR__ . '/tiket.class.php';
//require_once __DIR__ . '/sveostaleklasedodatiovako.class.php';

class KladionicaService
{
	function getUserById( $id )
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM Kladionica_Users WHERE id=:id' );
			$st->execute( array( 'id' => $id ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$row = $st->fetch();
		
		if( $row === false )
			return null;
		else
			return new User( $row['id'], $row['username'], $row['password_hash'], $row['email'], $row['iznos'], $row['has_registred'], $row['registration_sequence']);
	}
	function getUserByUsername( $username )
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM Kladionica_Users WHERE username=:username' );
			$st->execute( array( 'username' => $username ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$row = $st->fetch();
		
		if( $row === false )
			return null;
		else
			return new User( $row['id'], $row['username'], $row['password_hash'], $row['email'], $row['iznos'], $row['has_registred'], $row['registration_sequence']);
	}

	function getAllUsers( )
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM Kladionica_Users ORDER BY username' );
			$st->execute();
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$arr = array();
		while( $row = $st->fetch() )
		{
			$arr[] = new User( $row['id'], $row['username'], $row['password_hash'], $row['email'], $row['iznos'], $row['has_registred'], $row['registration_sequence']);
		}

		return $arr;
	}
	function dohvatiUtakmice()
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM Kladionica_Utakmice ORDER BY sport' );
			$st->execute();
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$arr = array();
		while( $row = $st->fetch() )
		{
			$arr[] = new Utakmica( $row['id'], $row['domaci'], $row['gosti'], $row['kvota1'], 
					$row['kvotaX'], $row['kvota2'], $row['kvota1x'], $row['kvota2x'] );
		}

		return $arr;
	}
	function dohvatiSportove()
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT DISTINCT sport FROM Kladionica_Utakmice ORDER BY sport' );
			$st->execute();
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$arr = array();
		while( $row = $st->fetch() )
		{
			array_push($arr, $row['sport']);
		}
		return $arr;
	}
	function dohvatiUtakmiceSporta($sport)
	{
		
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM Kladionica_Utakmice WHERE sport="'. $sport . '"');
			$st->execute();
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }
		$arr = array();
		while( $row = $st->fetch() )
		{
			$arr[] = new Utakmica( $row['id'], $row['domaci'], $row['gosti'], $row['kvota1'], 
					$row['kvotaX'], $row['kvota2'], $row['kvota1x'], $row['kvota2x'], $row['sport'] );
		}
		return $arr;
		
	}
	function dohvatiIznos($username)
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT iznos FROM Kladionica_Users WHERE username="' . $username .'"' );
			$st->execute();
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$row = $st->fetch();
		
		if( $row === false )
			return null;
		else
			return $row['iznos'];
	}
	function promijeniIznos($username,$iznos)
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'UPDATE Kladionica_Users SET iznos=' . $iznos .'  WHERE username="' . $username .'"' );
			$st->execute();
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }
	}

	function getIdUserByUsername( $username ){

		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT id FROM Kladionica_Users WHERE username=:uname' );
			$st->execute( array( 'uname' => $username ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		if( $st->rowCount() !== 1){
			$return_state = false;
		}
		else{
			$row = $st->fetch();
			return $row['id'];
		}
	}

	function dohvatiListice($ID_User){

		try
		{
            $db = DB::getConnection();
            $st1 = $db->prepare( 'SELECT * FROM Kladionica_Tiketi WHERE user_id=:uID ORDER BY vrijeme_uplate DESC, id DESC' );
			$st1->execute( array( 'uID' => $ID_User ) );

		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }
		
		$ListaTiketa = [];

		while( $row1 = $st1->fetch() ){
			$ID_Tiket = $row1['id'];

			try
			{
				$db = DB::getConnection();
				$st2 = $db->prepare( 'SELECT * FROM Kladionica_Relacija, Kladionica_Utakmice WHERE Kladionica_Relacija.id_tiket =:tID 
																			AND Kladionica_Relacija.id_utakmica = Kladionica_Utakmice.id' );
				$st2->execute( array( 'tID' => $ID_Tiket ) );

			}
			catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

			$ListaUtakmica = [];
			$ListaOdabira = [];
			$ListaIshoda = [];
			while( $row2 = $st2->fetch() ){
				$ListaUtakmica[] = new Utakmica( $row2['id'], $row2['domaci'], $row2['gosti'], $row2['kvota1'], $row2['kvotaX'], 
													$row2['kvota2'], $row2['kvota1x'], $row2['kvota2x'], $row2['sport'] );
				$ListaOdabira[] = $row2['odabrani_ishod']; 
				$ListaIshoda[] = $row2['konacni_ishod'];
			}

			$ListaTiketa[] = new Tiket( $row1['id'], $row1['user_id'], $row1['uplaceni_iznos'], $row1['moguci_dobitak'], 
										$row1['vrijeme_uplate'], $row1['koeficijent'], $ListaUtakmica, $ListaOdabira, $ListaIshoda );
		}

		return $ListaTiketa;
	}

	function simuliraj_listic($ID_Tiket)
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM Kladionica_Relacija, Kladionica_Utakmice WHERE Kladionica_Relacija.id_tiket =:tID 
																		AND Kladionica_Relacija.id_utakmica = Kladionica_Utakmice.id
																		AND Kladionica_Relacija.konacni_ishod = \'-1\'' );
			$st->execute( array( 'tID' => $ID_Tiket ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$dobitan = 1;
		while( $row = $st->fetch() ){

			$a = (float)$row['kvota1'];
			$b = (float)$row['kvotaX'];
			$c = (float)$row['kvota2'];

			$max_broj = (int)((1/$a + 1/$b + 1/$c) * 1000);
			$rezultat = rand(0, $max_broj);
			if($rezultat < (int)(1000*(1/$a)))
			{
				$ishod_utakmice = '1';
			}
			else if($rezultat < (int)(1000*(1/$a + 1/$b)))
			{
				$ishod_utakmice = 'X';
			}
			else
			{
				$ishod_utakmice = '2';
			}


			//upisivanje rezultata u bazu
			try
			{
				$st2 = $db->prepare( 'UPDATE Kladionica_Relacija SET konacni_ishod=\'' . $ishod_utakmice .'\'  WHERE id_tiket=:tID AND id_utakmica=:utakID' );
				$st2->execute( array('tID' => $ID_Tiket, 'utakID' => $row['id_utakmica']) );
			}
			catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		}

		return $dobitan;
	}

	function dohvati_moguci_dobitak($ID_Tiket)
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM Kladionica_Tiketi WHERE Kladionica_Tiketi.id =:tID' );
			$st->execute( array( 'tID' => $ID_Tiket ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$row = $st->fetch();
		$rez = $row['moguci_dobitak'];
		
		return $rez;
	}

	function provjeri_listic($ID_Tiket)
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM Kladionica_Relacija, Kladionica_Utakmice WHERE Kladionica_Relacija.id_tiket =:tID 
																		AND Kladionica_Relacija.id_utakmica = Kladionica_Utakmice.id' );
			$st->execute( array( 'tID' => $ID_Tiket ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$dobitan = 1;
		while( $row = $st->fetch() ){

			if( strlen( $row['odabrani_ishod'] ) === 1 )
			{
				if( $row['odabrani_ishod'] === $row['konacni_ishod'] ){
					//pogodak
				}
				else{
					//promasaj
					$dobitan = 0;
					break;
				}
			}
			else
			{
				//ostaju samo 1X i 2X kao mogucnosti
				if($row['konacni_ishod'] === 'X'){
					//pogodak u oba slucaja
				}
				else{
					//krajnji rezultat je 1 ili 2
					if( substr($row['odabrani_ishod'], 0, 1) === $row['konacni_ishod'] ){
						//pogodak
					}
					else{
						//promasaj
						$dobitan = 0;
						break;
					}
				}
			}
		}

		return $dobitan;
	}

	function dohvatiZadnjiTiket()
	{
		try
		{
            $db = DB::getConnection();
            $st = $db->prepare( 'SELECT MAX(id) FROM Kladionica_Tiketi' );
			$st->execute();

		}
		catch( PDOException $e ) { exit( 'PDO error (dohvatiZadnjiTiket)' . $e->getMessage() ); }
		$row = $st->fetch();
		if( $row === false )
			return null;
		else
			return $row['MAX(id)'];

	}
	function staviTiket($user_id,$uplaceni_iznos,$potencijalni_dobitak,$ukupna_kvota)
	{
		$db = DB::getConnection();
		try
		{
			$st = $db->prepare( 'INSERT INTO Kladionica_Tiketi(user_id, uplaceni_iznos, moguci_dobitak, vrijeme_uplate, koeficijent)
								VALUES (:id_user, :uplata, :dobitak, :vrijeme, :koeficijent)' );

			$st->execute( array( 'id_user' => $user_id, 'uplata' => $uplaceni_iznos, 'dobitak' => $potencijalni_dobitak, 'vrijeme' => date("Y-m-d h:i:s"), 'koeficijent' => $ukupna_kvota ));
		}
		catch( PDOException $e ) { exit( "PDO error (staviTiket): " . $e->getMessage() ); }
	}

	function napraviRelaciju($id_tiket,$id_utakmica,$odabrani_ishod)
	{
		$db = DB::getConnection();
		try 
		{
			$st = $db->prepare("INSERT INTO Kladionica_Relacija(id_tiket, id_utakmica, odabrani_ishod, konacni_ishod) 
								VALUES (:id_tiket, :id_utakmica, :odabrani_ishod, :konacni_ishod)");

			$st->execute(array('id_tiket' => $id_tiket, 'id_utakmica' => $id_utakmica, 'odabrani_ishod' => $odabrani_ishod, 'konacni_ishod' => '-1'));
		}
		catch(PDOException $e)
		{
			exit("PDO error (napraviRelaciju): " . $e->getMessage());
		}
		}
};

?>

