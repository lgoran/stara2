<!DOCTYPE html>
<html>
<head>
	<meta charset="utf8">
	<title>Kladionica</title>
	<link rel="stylesheet" href="css/style.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.js"></script>
</head>
<body>
	<h1>Kladionica</h1>
	<?php if(isset($_SESSION['user'])) echo 'Dobrodošli @' . $_SESSION['user'].'!'; ?>
	<span id="user_iznos" style="float:right;"><?php echo $_SESSION['iznos'];?> kredita</span>
	<hr>
	<ul>
		<a href="index.php?rt=sport/index">Sport</a>
		<a href="index.php?rt=grcki_loto/index">Grčki loto</a>
		<a href="index.php?rt=utrka_pasa/index">Utrka pasa</a>
		<a href="index.php?rt=rulet/index">Kasino</a>
		<a href="index.php?rt=listici/index">Vaši listići</a>
		<a href="index.php?rt=uplata_na_racun/index">Uplata na račun</a>
		<a href="index.php?rt=logout/logout">Odjavi se</a>
	</ul>
	<hr>
	<h1><?php echo $title; ?></h1>
