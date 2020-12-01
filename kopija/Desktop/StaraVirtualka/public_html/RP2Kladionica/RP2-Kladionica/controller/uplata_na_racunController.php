<?php 
require_once __DIR__ . '/../model/kladionicaservice.class.php';

class Uplata_na_racunController
{
	//Osnovna funkcija kod prikaza uplate na racun. Priprema vrijednosti iznosa racuna i imena stranice,
	//te poziva odgovarajuci view.
	public function index() 
	{
        $ks = new KladionicaService();
        $iznos=$ks->dohvatiIznos($_SESSION['user']);
        $title = 'Uplata na račun';		
        
        
		require_once __DIR__ . '/../view/uplata_na_racun.php';
	}

	//Funkcija uplati obraduje korisnikovu uplatu ("manju" uplatu), slicna je kao index funkcija,
	//samo sto jos priprema poruku o ishodu uplate.
	public function uplati()
	{
		$ks = new KladionicaService();
		$iznos=$ks->dohvatiIznos($_SESSION['user']);
		
		if( !isset( $_POST['manja_uplata'] ) ){
			header( 'Location: index.php?rt=uplata_na_racun/index' );
		}
		else{
			$uplaceni_iznos = (int)($_POST['manja_uplata']);
			$iznos = $iznos + $uplaceni_iznos;

			$ks->promijeniIznos($_SESSION['user'], $iznos);

			$title = 'Uplata na račun';	
			$poruka_o_uplati = "Uspješno ste uplatili " . $uplaceni_iznos . " kredita. Sretno u nastavku korištenja Kladionice!";

			$_SESSION['iznos']=$iznos;

			require_once __DIR__ . '/../view/uplata_na_racun.php';
		}

		
	}
}; 

?>
