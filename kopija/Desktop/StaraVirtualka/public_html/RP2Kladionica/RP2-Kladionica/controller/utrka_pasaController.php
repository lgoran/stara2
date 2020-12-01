<?php 
require_once __DIR__ . '/../model/kladionicaservice.class.php';

class Utrka_pasaController
{
	public function index() 
	{
		$ks = new KladionicaService();
		$iznos=$ks->dohvatiIznos($_SESSION['user']);
		$title = 'Utrka pasa';		
		require_once __DIR__ . '/../view/utrka_pasa.php';
	}
	//hvatanje ajax poziva za update stanja racuna
	public function update()
	{
		$stanje_racuna=$_GET["stanje_racuna"];
		$ks = new KladionicaService();
		$ks->promijeniIznos($_SESSION['user'],floatval($stanje_racuna));
		$_SESSION['iznos']=$stanje_racuna;
	}
}; 

?>
