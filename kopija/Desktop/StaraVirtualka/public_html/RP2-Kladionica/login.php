<?php
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
require_once __DIR__ . '/app/database/db.class.php';

$db = DB::getConnection();
if(isset($_POST['user']) && $_POST['user']!="" && isset($_POST['pw']) && $_POST['pw']!="")
{
	$pw=$_POST['pw'];
	$user=$_POST['user'];
	$hash=password_hash($pw,PASSWORD_DEFAULT);
	if($_POST['submit']=="Login")
	{
		try{
			$st = $db->prepare( 'SELECT password_hash, has_registered, registration_sequence, iznos FROM Kladionica_Users WHERE username=:username' );
			$st->execute( array( 'username' => $user ) );
		}catch(PDOException $e){
			echo $e;
		}
		if($st->rowCount()==0)
		{
			echo "Krivi Username";
		}
		foreach( $st->fetchAll() as $row )
		{
		
			if( password_verify( $pw, $row['password_hash'] ) )
			{
				echo "Uspijesno logiranje";
				$_SESSION['user']=$user;
				$_SESSION['iznos']=$row['iznos'];
				$_SESSION['logged_in']='true';
				header( 'Location: index.php' );
			}
			else
				echo "Krivi Password";
		}
	}
}
$_SESSION['x'] = 0;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Kladionica</title>
	<link rel="stylesheet" href="css/style.css">
</head>
<body>
<form action="index.php" method="POST">
	<div id="unos_forma">
		Username:<input type="text" name="user"><br><br>
		Password:<input type="password" name="pw"><br>
		<input type="submit" name="submit" value="Login"><br><br>
		Ukoliko nemate korisnički račun, otvorite ga <a href="register.php">ovdje</a><br>
	</div>
</form>

</body>
</html>
