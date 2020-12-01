<?php

require_once __DIR__ . '/db.class.php';

seed_table_utakmice();
seed_table_tiketi();
seed_table_relacija();

// ------------------------------------------

function seed_table_utakmice()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare( 'INSERT INTO Kladionica_Utakmice(domaci, gosti, kvota1, kvotaX, kvota2, kvota1x, kvota2x, sport)
                             VALUES (:domaci, :gosti, :kvota1, :kvotaX, :kvota2, :kvota1x, :kvota2x, :sport)' );

        $st->execute( array( 'domaci' => 'NK Varazdin', 'gosti' => 'GNK Dinamo Zagreb', 'kvota1' => 17.0, 'kvotaX' => 7.0,
                            'kvota2' =>  1.25, 'kvota1x' => 5.0, 'kvota2x' => 1.05, 'sport' => 'nogomet') );
        $st->execute( array( 'domaci' => 'NK Hajduk Split', 'gosti' => 'NK Inter Zapresic', 'kvota1' => 1.5, 'kvotaX' => 4.8,
                            'kvota2' =>  8, 'kvota1x' => 1.2, 'kvota2x'=> 4.0, 'sport' => 'nogomet') );
        $st->execute( array( 'domaci' => 'NK Istra 1961', 'gosti' => 'HNK Rijeka', 'kvota1' => 6.8, 'kvotaX' => 4.0,
                            'kvota2' =>  1.5, 'kvota1x' => 2.6, 'kvota2x'=> 1.25, 'sport' => 'nogomet') );
        $st->execute( array( 'domaci' => 'FC Chelsea', 'gosti' => 'Leicester City', 'kvota1' => 3.5, 'kvotaX' => 5.0,
                            'kvota2' =>  1.7, 'kvota1x' => 2.25, 'kvota2x'=> 1.25, 'sport' => 'nogomet') );
        $st->execute( array( 'domaci' => 'Los Angeles Lakers', 'gosti' => 'Memphis Grizzlie', 'kvota1' => 1.25, 'kvotaX' => 15.0,
                            'kvota2' =>  9.0, 'kvota1x' => 1.05, 'kvota2x'=> 7.0, 'sport' => 'kosarka') );
        $st->execute( array( 'domaci' => 'Orlando Magic', 'gosti' => 'Toronto Raptors', 'kvota1' => 7.0, 'kvotaX' => 16.5,
                            'kvota2' =>  1.25, 'kvota1x' => 5.0, 'kvota2x'=> 1.05, 'sport' => 'kosarka') );
        $st->execute( array( 'domaci' => 'Washington Wizards', 'gosti' => 'Philadelphia 76ers', 'kvota1' => 14.0, 'kvotaX' => 25.0,
                            'kvota2' =>  1.45, 'kvota1x' => 10.0, 'kvota2x'=> 1.25, 'sport' => 'kosarka') );
	}
	catch( PDOException $e ) { exit( "PDO error (seed_table_utakmice): " . $e->getMessage() ); }

	echo "Ubacio utakmice u tablicu Kladionica_utakmice.<br />";
}


function seed_table_tiketi()
{
	$db = DB::getConnection();

	try
	{
		$st = $db->prepare( 'INSERT INTO Kladionica_Tiketi(user_id, uplaceni_iznos, moguci_dobitak, vrijeme_uplate, koeficijent)
                            VALUES (:id_user, :uplata, :dobitak, :vrijeme, :koeficijent)' );

		$st->execute( array( 'id_user' => 4, 'uplata' => 10.0, 'dobitak' => 75.0, 'vrijeme' => '2020-06-01 10:15:00', 'koeficijent' => 7.5 ));
		$st->execute( array( 'id_user' => 5, 'uplata' => 25.0, 'dobitak' => 1000.0, 'vrijeme' => '2020-06-02 14:30:00', 'koeficijent' => 40.0) );
		$st->execute( array( 'id_user' => 6, 'uplata' => 10.0, 'dobitak' => 120.0, 'vrijeme' => '2020-06-03 08:15:00', 'koeficijent' => 12.0) );
		$st->execute( array( 'id_user' => 5, 'uplata' => 50.0, 'dobitak' => 1220.0, 'vrijeme' => '2020-06-03 10:20:30', 'koeficijent' => 24.5) );
	}
	catch( PDOException $e ) { exit( "PDO error (seed_table_tiketi): " . $e->getMessage() ); }

	echo "Ubacio podatke u tablicu tiketi.<br />";
}

function seed_table_relacija() 
{
    $db = DB::getConnection();

    try 
    {
        $st = $db->prepare("INSERT INTO Kladionica_Relacija(id_tiket, id_utakmica, odabrani_ishod, konacni_ishod) 
                            VALUES (:id_tiket, :id_utakmica, :odabrani_ishod, :konacni_ishod)");

        $st->execute(array('id_tiket' => 1, 'id_utakmica' => 1, 'odabrani_ishod' => '2', 'konacni_ishod' => '2'));
        $st->execute(array('id_tiket' => 1, 'id_utakmica' => 2, 'odabrani_ishod' => '1', 'konacni_ishod' => '1'));
        $st->execute(array('id_tiket' => 1, 'id_utakmica' => 3, 'odabrani_ishod' => 'X', 'konacni_ishod' => '2'));
        $st->execute(array('id_tiket' => 2, 'id_utakmica' => 5, 'odabrani_ishod' => 'X', 'konacni_ishod' => '1'));
        $st->execute(array('id_tiket' => 2, 'id_utakmica' => 7, 'odabrani_ishod' => 'X', 'konacni_ishod' => '2'));
        $st->execute(array('id_tiket' => 3, 'id_utakmica' => 2, 'odabrani_ishod' => 'X', 'konacni_ishod' => '1'));
        $st->execute(array('id_tiket' => 3, 'id_utakmica' => 4, 'odabrani_ishod' => '1X', 'konacni_ishod' => '1'));
        $st->execute(array('id_tiket' => 4, 'id_utakmica' => 4, 'odabrani_ishod' => '1', 'konacni_ishod' => '1'));
        $st->execute(array('id_tiket' => 4, 'id_utakmica' => 6, 'odabrani_ishod' => '1', 'konacni_ishod' => '2'));
    }
    catch(PDOException $e)
    {
        exit("PDO error (seed_table_relacija): " . $e->getMessage());
    }

    echo "Ubacio podatke u tablicu relacija.<br />";
}

?>