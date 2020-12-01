<?php
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
require_once __DIR__ . '/app/database/db.class.php';

$_SESSION['x'] = 1;
if( isset( $_POST['username'] ) )
{
	?><script>console.log("doslo je");</script><?php
    //prvo provjeri jesu li sva polja upisana
    if( !isset( $_POST['username'] ) || !isset( $_POST['password'] ) || !isset( $_POST['email'] )  || $_POST['username'] == "")
	{
        header('Location: index.php?i=1');
    }
    //provjeri je li upisan ispravan mail
    else if( !filter_var( $_POST['email'], FILTER_VALIDATE_EMAIL) )
	{
		header( 'Location: index.php?i=2' );	
    }
    else
	{
		// Provjeri jel već postoji taj korisnik u bazi
		$db = DB::getConnection();

		try
		{
			$st = $db->prepare( 'SELECT * FROM Kladionica_Users WHERE username=:username' );
			$st->execute( array( 'username' => $_POST['username'] ) );
		}
		catch( PDOException $e ) { exit( 'Greška u bazi: ' . $e->getMessage() ); }

		if( $st->rowCount() !== 0 )
		{
			// Taj user u bazi već postoji
			header( 'Location: index.php?i=3' );
		}

		// Dakle sad je napokon sve ok.
		// Dodaj novog korisnika u bazu. Prvo mu generiraj random string od 10 znakova za registracijski link.
		$reg_seq = '';
		for( $i = 0; $i < 10; ++$i )
			$reg_seq .= chr( rand(0, 25) + ord( 'a' ) ); // Zalijepi slučajno odabrano slovo

		try
		{
			$st = $db->prepare( 'INSERT INTO Kladionica_Users(username, password_hash, email, has_registered, iznos, registration_sequence) VALUES ' .
				                '(:username, :password, :email, :has, :iznos, :reg_seq)' );
			
			$st->execute( array( 'username' => $_POST['username'], 
				                 'password' => password_hash( $_POST['password'], PASSWORD_DEFAULT ), 
                                 'email' => $_POST['email'],
                                 'has' => floatval(0),
                                 'iznos' => floatval(100), 
				                 'reg_seq'  => $reg_seq ) );
		}
		catch( PDOException $e ) { exit( 'Greška u bazi: ------------->' . $e->getMessage() ); }

		// Sad mu još pošalji mail
		$to       = $_POST['email'];
		$subject  = 'Registracijski mail';
		$message  = 'Poštovani ' . $_POST['username'] . "!\nZa dovršetak registracije kliknite na sljedeći link: ";
        $message .= 'http://' . $_SERVER['SERVER_NAME'] . htmlentities( dirname( $_SERVER['PHP_SELF'] ) ) . '/new_user.php?niz=' . $reg_seq . "\n";
		$headers  = 'From: rp2@studenti.math.hr' . "\r\n" .
		            'Reply-To: rp2@studenti.math.hr' . "\r\n" .
		            'X-Mailer: PHP/' . phpversion();

		$isOK = mail($to, $subject, $message, $headers);

		if( !$isOK )
            exit( 'Greška: ne mogu poslati mail. (Pokrenite na rp2 serveru.)' );
        
        header( 'Location: index.php?i=4' );
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Chat</title>
	<link rel="stylesheet" href="css/style.css">
</head>
<body>
<form action="index.php" method="POST">
	<div id="unos_forma">
        Odaberite korisničko ime:
		<input type="text" name="username" />
		<br />
		Odaberite lozinku:
		<input type="password" name="password" />
		<br />
		Vaša mail-adresa:
		<input type="text" name="email" />
		<br />
        <button type="submit" value="stvori">Stvori korisnički račun!</button><br /><br>
        Za povratak nazad kliknite <a href="login.php">ovdje</a>
	</div>
</form>

</body>
</html>