<?php require_once __DIR__ . '/_header.php'; ?>

<?php 
    if(isset($poruka))
    {
        echo '<h3>' . $poruka . '</h3><hr><br>';
    }
?>

<form action="index.php?rt=listici/index" method="post">
  <label for="broj_listica_za_prikaz">Koliko listića želite prikazati?</label>
  <select name="broj_listica_za_prikaz" id="broj_listica_za_prikaz">
    <option selected="selected" disabled="disabled">...</option>
    <option value="3">3</option>
    <option value="5">5</option>
    <option value="10">10</option>
    <option value="15+">15+</option>
  </select>
  <br><br>
  <input type="submit" value="Prikaži listiće">
</form>

<?php

$brojac_listica = 0;
$broj_listica = $_SESSION['broj_listica'];

foreach($ListaTiketa as $tiket){

    if($broj_listica >= 0 && $brojac_listica >= $broj_listica){
        //prikazali smo sve listice koje je korisnik htio
        break;
    }
    $brojac_listica++;

    $postoji_promasaj = 0;
    $cekamo_rezultat = 0;
    echo '<hr> <br>';
    echo '<div class="vas_tiket">' . 
            '<h3> Kladionica </h3>' .
            '<div class="headerListica">'.
                'Broj listića: ' . $tiket->id . '<br>' . "\n" .
                'Vrijeme uplate: ' . $tiket->vrijeme_uplate . '<br>' . "\n" .
            '</div>'.
            '<table class="utakmice_listic"' .
                '<tr><th>Br.</th><th>Sport</th><th>Domaci-Gosti</th><th></th><th>Koef.</th><th></th><th>Rez.</th>';
            $counter = 0;
            foreach($tiket->utakmice as $utakmica){
                $ime_kvote = 'kvota' . ($tiket->odabiri_ishoda)[$counter];
                echo '<tr>' .
                     '<td>' . $utakmica->id . '</td>' .
                     '<td>' . $utakmica->sport . '</td>' .
                     '<td>' . $utakmica->domaci . '-' . $utakmica->gosti . '</td>' .
                     '<td>' . ($tiket->odabiri_ishoda)[$counter] . '</td>' .
                     '<td>' . $utakmica->$ime_kvote . '</td>' .
                     '<td>';
                     //prvo provjera je li utakmica uopce odigrana, oznaka '-1' ako nije
                     if(($tiket->konacni_ishodi)[$counter] === '-1')
                     {
                        //nasli smo neodigranu utakmicu
                        $cekamo_rezultat = 1;
                        echo '<img class="oznaka_na_listicu" src="slike/neodigrano.png" alt="?" >';
                     }
                     //tu provjeravamo je li odigrana utakmica pogodena ili ne
                     else if( strlen(($tiket->odabiri_ishoda)[$counter]) === 1 )
                     {
                        if( ($tiket->odabiri_ishoda)[$counter] === ($tiket->konacni_ishodi)[$counter] ){
                            //pogodak
                            echo '<img class="oznaka_na_listicu" src="slike/pogodeno.png" alt="+" >';
                        }
                        else{
                            //promasaj
                            $postoji_promasaj = 1;
                            echo '<img class="oznaka_na_listicu" src="slike/promasaj.png" alt="-" >';
                        }
                     }
                     else
                     {
                        //ostaju samo 1X i 2X kao mogucnosti
                        if(($tiket->konacni_ishodi)[$counter] === 'X'){
                            //pogodak u oba slucaja
                            echo '<img class="oznaka_na_listicu" src="slike/pogodeno.png" alt="+" >';
                        }
                        else{
                            //krajnji rezultat je 1 ili 2
                            if( substr(($tiket->odabiri_ishoda)[$counter], 0, 1) === ($tiket->konacni_ishodi)[$counter] ){
                                //pogodak
                                echo '<img class="oznaka_na_listicu" src="slike/pogodeno.png" alt="+" >';
                            }
                            else{
                                //promasaj
                                $postoji_promasaj = 1;
                                echo '<img class="oznaka_na_listicu" src="slike/promasaj.png" alt="-" >';
                            }
                        }
                     }/*
                     echo '</td>' .
                     '<td>' . ($tiket->konacni_ishodi)[$counter] . '</td>' .
                     
                     '</tr>';*/
                     echo '</td>' .
                        '<td>';
                        if(($tiket->konacni_ishodi)[$counter] === '-1')
                        {
                            echo '-';
                        }
                        else
                        {
                            echo ($tiket->konacni_ishodi)[$counter];
                        }
                        echo '</td>' .
                     '</tr>';
                $counter++;
            }
    echo    '</table>' .
            '<div class="footerListica">'.
                'Uplaćeni iznos: ' . $tiket->uplaceni_iznos . ' kn <br>' . "\n" . 
                'Koeficijent: ' . $tiket->koeficijent . '<br>' . "\n" . 
                'Mogući dobitak : ' . $tiket->moguci_dobitak . ' kn <br>' . "\n" ;
                if($postoji_promasaj === 1)
                {
                    //gubitni listic
                    echo '<p style="color:red; font-size:20px; margin-bottom:0;">Gubitni listić</p>';
                }
                else if($cekamo_rezultat === 1)
                {
                    //potrebno simulirati utakmice
                    echo '<p style="color:blue; font-size:20px; margin-bottom:0;">Nisu odigrane sve utakmice</p>';
                    echo '<form class="simulacija_utakmica" action="index.php?rt=listici/simuliraj" method="post">' .
                         '<input type="hidden" name="listic_ID" value="' . $tiket->id . '">' .
                         '<button type="submit">Simuliraj listić</button>' .
                         '</form>';

                }
                else
                {
                    //listic je dobitan
                    echo '<p style="color:green; font-size:20px; margin-bottom:0;">Dobitni listić</p>';
                }
            echo '</div>';
            
            
            

         echo '</div>';
}

if( count($ListaTiketa) === 0 ){
    echo '<p>Nema uplaćenih listića!</p><br>';
}
?>





<?php require_once __DIR__ . '/_footer.php'; ?>