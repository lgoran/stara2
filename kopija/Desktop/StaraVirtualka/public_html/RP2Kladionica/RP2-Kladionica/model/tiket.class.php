<?php

class Tiket
{
    protected $id, $user_id,  $uplaceni_iznos, $moguci_dobitak, $vrijeme_uplate, $koeficijent;
    protected $utakmice, $odabiri_ishoda, $konacni_ishodi;

	function __construct( $id, $user_id, $uplaceni_iznos, $moguci_dobitak, $vrijeme_uplate, $koeficijent, $utakmice, $odabiri_ishoda, $konacni_ishodi )
	{
		$this->id = $id;
		$this->user_id = $user_id;
		$this->uplaceni_iznos = $uplaceni_iznos;
        $this->moguci_dobitak = $moguci_dobitak;
        $this->vrijeme_uplate = $vrijeme_uplate;
		$this->koeficijent = $koeficijent;
		//cuvamo listu objekata Utakmica
		$this->utakmice = $utakmice;
		//istim redom kao u listi utakmica, pamtimo sto smo odgirali za pojedinu utakmicu
		//na taj nacin nam ne treba Relaacija kao sto je postavljeno u bazi podataka
		$this->odabiri_ishoda = $odabiri_ishoda;
		$this->konacni_ishodi = $konacni_ishodi;
	}

	function __get( $prop ) { return $this->$prop; }
	function __set( $prop, $val ) { $this->$prop = $val; return $this; }
}

?>
