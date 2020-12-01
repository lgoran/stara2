<?php 
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}

require_once __DIR__ . '/app/database/db.class.php';

if( !isset( $_GET['niz'] ) || !preg_match( '/^[a-z]{10}$/', $_GET['niz'] ) )
    exit( 'Nešto ne valja s nizom.' );
    
// Nađi korisnika s tim nizom u bazi
$db = DB::getConnection();

try
{
	$st = $db->prepare( 'SELECT * FROM Kladionica_Users WHERE registration_sequence=:registration_sequence' );
	$st->execute( array( 'registration_sequence' => $_GET['niz'] ) );
}
catch( PDOException $e ) { exit( 'Greška u bazi: ' . $e->getMessage() ); }

$row = $st->fetch();

if( $st->rowCount() !== 1 )
	exit( 'Taj registracijski niz ima ' . $st->rowCount() . 'korisnika, a treba biti točno 1 takav.' );
else
{
	// Sad znamo da je točno jedan takav. Postavi mu has_registered na 1.
	try
	{
		$st = $db->prepare( 'UPDATE Kladionica_Users SET has_registered=1 WHERE registration_sequence=:reg_seq' );
		$st->execute( array( 'reg_seq' => $_GET['niz'] ) );
	}
	catch( PDOException $e ) { exit( 'Greška u bazi: ' . $e->getMessage() ); }

	// Sve je uspijelo -> napravi login
    $_SESSION['user']=$row['username'];
	$_SESSION['logged_in']='true';
	header( 'Location: index.php' );
}

?>