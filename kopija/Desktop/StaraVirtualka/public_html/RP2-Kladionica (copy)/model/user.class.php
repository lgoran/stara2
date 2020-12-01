<?php

class User
{
	protected $id, $username, $password, $email;

	function __construct( $id, $username, $password, $email)
	{
		$this->id = $id;
		$this->username = $username;
		$this->email = $email;
		$this->password = $password;
	}

	function __get( $prop ) { return $this->$prop; }
	function __set( $prop, $val ) { $this->$prop = $val; return $this; }
}

?>

