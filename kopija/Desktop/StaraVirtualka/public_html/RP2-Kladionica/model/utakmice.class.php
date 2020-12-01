<?php

class Utakmica
{
    protected $id, $domaci, $gosti, $kvota1, $kvotaX, $kvota2, $kvota1X, $kvota2X, $sport;

	function __construct( $id, $domaci, $gosti, $kvota1, $kvotaX, $kvota2, $kvota1X, $kvota2X, $sport)
	{
		$this->id = $id;
		$this->domaci = $domaci;
		$this->gosti = $gosti;
        $this->kvota1 = $kvota1;
        $this->kvotaX = $kvotaX;
        $this->kvota2 = $kvota2;
        $this->kvota1X = $kvota1X;
		$this->kvota2X = $kvota2X;
		$this->sport = $sport;
	}

	function __get( $prop ) { return $this->$prop; }
	function __set( $prop, $val ) { $this->$prop = $val; return $this; }
}

?>
