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
			$st = $db->prepare( 'SELECT password_hash FROM Kladionica_Users WHERE username=:username' );
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
				$_SESSION['logged_in']='true';
				header( 'Location: index.php' );
			}
			else
				echo "Krivi Password";
		}
	}
	else
	{
		$flag=0;
		try{
			$st = $db->prepare( 'SELECT password_hash FROM Kladionica_Users WHERE username=:username' );
			$st->execute( array( 'username' => $user ) );
		}catch(PDOException $e){
			echo $e;
		}
		if($st->rowCount()>0)
		{
			echo "Postoji Username";
		}
		else
		{
			try{
				$st = $db->prepare( 'INSERT INTO Kladionica_Users (username, password_hash, email, iznos) VALUES (:username, :hash, :email, :iznos)' );
				$st->execute( array( 'username' => $user, 'hash' => $hash, 'email' => $_POST['email'], 'iznos' => floatval(100) ) );
			}catch(PDOException $e){
				echo $e;
			}
			echo "Dodani ste!";
		}
		
	}
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Chat</title>
</head>
<body>
<hr>
<form action="index.php" method="POST">
	Username:<input type="text" name="user"><br><br>
	Password:<input type="password" name="pw"><br>
	<input type="submit" name="submit" value="Login"><br><br>
	Email: <input type="email" name="email"><br>	
	<input type="submit" name="submit" value="Create">
</form>
<hr>
</body>
</html>
