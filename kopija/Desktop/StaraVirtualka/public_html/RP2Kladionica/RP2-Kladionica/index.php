<?php 
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
if(isset($_SESSION['logged_in']))
{
	// Provjeri je li postavljena varijabla rt; kopiraj ju u $route
	if( isset( $_GET['rt'] ) )
		$route = $_GET['rt'];
	else
		$route = 'index';

	// Ako je $route == 'con/act', onda rastavi na $controllerName='con', $action='act'
	$parts = explode( '/', $route );

	$controllerName = $parts[0] . 'Controller';
	if( isset( $parts[1] ) )
		$action = $parts[1];
	else
		$action = 'index';

	// Controller $controllerName se nalazi poddirektoriju controller
	$controllerFileName = 'controller/' . $controllerName . '.php';

	// Includeaj tu datoteku
	require_once $controllerFileName;

	// Stvori pripadni kontroler
	$con = new $controllerName; 

	// Pozovi odgovarajuću akciju
	$con->$action();
}
//SESSION['x'] = 1 kad je otvoren prozor za registraciju, 0 kad je za login
else if (isset($_SESSION['x']) && $_SESSION['x'] == 1){
	//preko GET saljemo vrijednost koja određuje sto se tocno dogodilo i sto ispisati
	if (isset($_GET['i']) && $_GET['i'] == '1')
		echo 'Trebate unijeti korisničko ime, lozinku i e-mail adresu.';
	else if (isset($_GET['i']) && $_GET['i'] == '2')
		echo 'Niste unijeli ispravan email.';
	else if (isset($_GET['i']) && $_GET['i'] == '3')
		echo 'Taj user već postoji u bazi.';
	else if (isset($_GET['i']) && $_GET['i'] == '4'){
		echo 'Uspješna registracija!';
		require_once __DIR__ . '/login/login.php';
		exit();
	}
	else if (isset($_GET['i']) && $_GET['i'] == '5'){
		require_once __DIR__ . '/login/login.php';
		exit();
	}


	require_once __DIR__ . '/login/register.php';
}
else {
	//ako je k=1 znaci da smo kliknuli za prelazak na prozor za registraciju
	if (isset($_GET['k']) && $_GET['k'] == '1'){ 
		require_once __DIR__ . '/login/register.php';
	}
	else
		require_once __DIR__ . '/login/login.php';
}


?>
