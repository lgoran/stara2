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

        //koliko na pocetku prikazujemo listica
        $broj_listica = 2;

        if(isset($_POST['broj_listica_za_prikaz']))
        {
            $br_t = $_POST['broj_listica_za_prikaz'];
            if($br_t === '15+'){
                //oznaka da nemamo ogranicenja, sve listice prikazujemo
                $broj_listica = -1;
            }     
            else{
                $broj_listica = (int)$br_t;
            }
        }
        $_SESSION['broj_listica'] = $broj_listica;
        
		require_once __DIR__ . '/../view/vasi_listici.php';
    }
    
    public function simuliraj()
    {
        $ks = new KladionicaService();
        $ID_Listic = $_POST['listic_ID'];

        $ks->simuliraj_listic($ID_Listic);
        //povratna vrijednost je 1 ako su sve simulirane utakmice pogodene, 0 inace
        $rezultat_simulacije = $ks->provjeri_listic($ID_Listic);

        $iznos = $ks->dohvatiIznos($_SESSION['user']);

        if($rezultat_simulacije === 1){            
            $iznos = $iznos + (float)($ks->dohvati_moguci_dobitak($ID_Listic));

            $ks->promijeniIznos($_SESSION['user'], $iznos);
            $_SESSION['iznos']=$iznos;

            $poruka = 'Čestitamo, Vaš listić br. ' . $ID_Listic . ' je dobitni!'; 
        }
        else{
            $poruka = 'Nažalost, Vaš listić br. ' . $ID_Listic . ' nije prošao.';
        }

        $title = 'Vaši listići';
        $ID_User = $ks->getIdUserByUsername( $_SESSION['user'] );
        $ListaTiketa = $ks->dohvatiListice($ID_User);
        
		require_once __DIR__ . '/../view/vasi_listici.php';
    }
}; 

?>