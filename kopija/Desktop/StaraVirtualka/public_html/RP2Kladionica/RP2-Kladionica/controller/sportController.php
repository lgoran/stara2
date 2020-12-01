<?php 
require_once __DIR__ . '/../model/kladionicaservice.class.php';

class SportController
{
	//pozivanje sport_index.php sa odgovarajucim varijablama
	public function index() 
	{
		$ks = new KladionicaService();
		$title = 'Sportska ponuda';
		$sportList=$ks->dohvatiSportove();
		$iznos=$ks->dohvatiIznos($_SESSION['user']);
		$utakmice_po_sportovima=array();
		for($i=0;$i<count($sportList);$i++)
		{
			array_push($utakmice_po_sportovima,$ks->dohvatiUtakmiceSporta($sportList[$i]));
		}
		require_once __DIR__ . '/../view/sport_index.php';
	}
	//hvatanje ajax poziva za update stanja racuna i slanje tiketa u bazu
	public function update()
	{
		$tiket=$_GET['tiket'];
		$potencijalni_dobitak=$_GET["potencijalni_dobitak"];
		$uplaceni_iznos=$_GET["uplaceni_iznos"];
		$ukupna_kvota=$_GET["ukupna_kvota"];
		$stanje_racuna=$_GET["stanje_racuna"];
		$ks = new KladionicaService();
		$user_id=$ks->getIdUserByUsername($_SESSION['user']);
		$ks->promijeniIznos($_SESSION['user'],floatval($stanje_racuna));
		$ks->staviTiket($user_id,$uplaceni_iznos,$potencijalni_dobitak,$ukupna_kvota);
		$id_tiket=$ks->dohvatiZadnjiTiket();
		for($i=0;$i<count($tiket);$i++)
		{
			$id_utakmica=$tiket[$i][0];
			$odabrani_ishod=$tiket[$i][2];
			$ks->napraviRelaciju($id_tiket,intval($id_utakmica),$odabrani_ishod);
		}
		$_SESSION['iznos']=$stanje_racuna;
	}
}; 

?>
