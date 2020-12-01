<?php 

require_once __DIR__ . '/../model/kladionicaservice.class.php';

class LogoutController
{
	public function logout() 
	{
		session_unset(); 
		session_destroy();
		require_once __DIR__ . '/../login.php';
	}
}; 

?>
