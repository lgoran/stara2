<?php require_once __DIR__ . '/_header.php'; ?>


<?php
foreach($ListaTiketa as $tiket){
    echo '<hr> <br>';
    echo '<div class="vas_tiket">' . 
            '<h3> Kladionica </h3>' .
            '<div class="headerListica">'.
                'Broj listića: ' . $tiket->id . '<br>' . "\n" .
                'Vrijeme uplate: ' . $tiket->vrijeme_uplate . '<br>' . "\n" .
            '</div>'.
            '<table class="utakmice_listic"' .
                '<tr><th>Br.</th><th>Sport</th><th>Domaci-Gosti</th><th></th><th>Koef.</th>';
            $counter = 0;
            foreach($tiket->utakmice as $utakmica){
                $ime_kvote = 'kvota' . ($tiket->odabiri_ishoda)[$counter];
                echo '<tr>' .
                     '<td>' . $utakmica->id . '</td>' .
                     '<td>' . $utakmica->sport . '</td>' .
                     '<td>' . $utakmica->domaci . '-' . $utakmica->gosti . '</td>' .
                     '<td>' . ($tiket->odabiri_ishoda)[$counter] . '</td>' .
                     '<td>' . $utakmica->$ime_kvote . '</td>' .
                     '</tr>';
                $counter++;
            }
    echo    '</table>' .
            '<div class="footerListica">'.
                'Uplaćeni iznos: ' . $tiket->uplaceni_iznos . ' kn <br>' . "\n" . 
                'Koeficijent: ' . $tiket->koeficijent . '<br>' . "\n" . 
                'Mogući dobitak : ' . $tiket->moguci_dobitak . ' kn <br>' . "\n" . 
            '</div>'.
         '</div>';
}

if( count($ListaTiketa) === 0 ){
    echo '<p>Nema uplaćenih listića!</p><br>';
}
?>

<?php require_once __DIR__ . '/_footer.php'; ?>