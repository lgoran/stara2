<?php

class User
{
	protected $id, $username, $password, $email, $iznos, $has_registered, $registration_sequence;

	function __construct( $id, $username, $password, $email, $iznos, $has_registered, $registration_sequence)
	{
		$this->id = $id;
		$this->username = $username;
		$this->email = $email;
		$this->password = $password;
		$this->iznos = $iznos;
		$this->has_registered = $has_registered;
		$this->registration_sequence = $registration_sequence;
	}

	function __get( $prop ) { return $this->$prop; }
	function __set( $prop, $val ) { $this->$prop = $val; return $this; }
}

?>

