<?php 

class IndexController
{
	public function index()
	{
		// Samo preusmjeri na sport podstranicu.
		header( 'Location: index.php?rt=sport' );
	}
}; 

?>
