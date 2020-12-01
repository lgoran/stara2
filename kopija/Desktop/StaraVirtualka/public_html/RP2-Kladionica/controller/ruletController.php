<?php

require_once __DIR__ . '/../model/kladionicaservice.class.php';

class RuletController
{
	public function index() 
	{
        $ks = new KladionicaService();
		$iznos=$ks->dohvatiIznos($_SESSION['user']);
		$title = 'Rulet';		
		require_once __DIR__ . '/../view/rulet_view.php';
	}
	public function update()
	{
		$stanje_racuna=$_GET["stanje_racuna"];
		$ks = new KladionicaService();
		$ks->promijeniIznos($_SESSION['user'],floatval($stanje_racuna));
		$_SESSION['iznos'] = $stanje_racuna;
	}
}; 

?>