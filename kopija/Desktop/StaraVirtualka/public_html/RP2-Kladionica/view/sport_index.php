<?php require_once __DIR__ . '/_header.php'; ?>
<div class="sport_tiket" id="sport_tiket">
	<p style="text-align:center;font-weight:bold;color:gold">Vaš tiket</p><hr>
	<p id="odigrani_parovi"></p>
	Stanje računa:<span id="stanje_racuna"><?php echo $iznos; ?></span><br>
	<input type="text" name="uplaceni_iznos" id="uplaceni_iznos" placeholder="Vaš ulog" size="5">
	<button id="uplati" style="background-color:darkorange;height:30px">Odigraj tiket</button><br><br>
	ISPLATA:<span id="potencijalni_dobitak"></span><br>
	Tečaj:<span id="ukupna_kvota">1</span><br>
	
</div>
<?php
for($j=0;$j<count($utakmice_po_sportovima);$j++)
{
	$utakmiceList=$utakmice_po_sportovima[$j];
	echo '<h2 id="sport' . $j . '">'. $sportList[$j] . '(' . count($utakmiceList) .')</h2>';
	echo '<table class="tablica_utakmica" id="tabla' . $j . '">';
		if(count($utakmiceList)!=0)
		{
			echo '<tr><th>Domaći</th><th>Gosti</th><th>1</th><th>X</th><th>2</th><th>1X</th><th>2X</th></tr>';
		}
		else 
		{
			echo 'Nema utakmica';
		}
		for( $i=0;$i<count($utakmiceList);$i++ )
		{
			$utakmica=$utakmiceList[$i];
			echo '<tr>' .
				 '<td>'. $utakmica->domaci . '</td>' . '<td>'. $utakmica->gosti . '</td>' . 
				 '<td><button id="' . $utakmica->id .'b1">'. $utakmica->kvota1 . '</button></td>' . 
				 '<td><button id="' . $utakmica->id .'bX">'. $utakmica->kvotaX . '</button></td>' . 
				 '<td><button id="' . $utakmica->id .'b2">'. $utakmica->kvota2 . '</button></td>' . 
				 '<td><button id="' . $utakmica->id .'b1X">'. $utakmica->kvota1X . '</button></td>' .
				 '<td><button id="' . $utakmica->id .'b2X">'. $utakmica->kvota2X . '</button></td>' .  
			     '</tr>';
		}
	echo '</table>';
}

?>
<script type="text/javascript" src="javascript/sport.js"></script>
<?php require_once __DIR__ . '/_footer.php'; ?>
