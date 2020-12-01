<?php 
require_once __DIR__ . '/../model/kladionicaservice.class.php';

class ListiciController
{
	public function index() 
	{
        $ks = new KladionicaService();
        $iznos=$ks->dohvatiIznos($_SESSION['user']);
        $title = 'Vaši listići';		
        
        $ID_User = $ks->getIdUserByUsername( $_SESSION['user'] );
        $ListaTiketa = $ks->dohvatiListice($ID_User);
        
		require_once __DIR__ . '/../view/vasi_listici.php';
	}
}; 

?>