<?php require_once __DIR__ . '/_header.php'; ?>
    <div id="ruletDiv">
    <h3 id="krediti">Stanje na racunu: <span id="stanje_racuna"><?php echo $iznos;?></span> kredita</h3>
    <h4 id="trenutni_ulog"></h4>
    <div id="divPravila">
        <button id="exitButtonPravila">X </button><br><br>
        Rulet je jedna od najpopularnijih svjetskih <br>
        igara na srecu. Igra se pomocu specijalnog <br>
        kola koji se sastoji od 37 brojeva (0 - 36). <br>
        Brojevi su naizmjence oznaceni crvenom i <br>
        crnom bojom, osim nule koja je zelena. <br>
        Mogucnosti odabira polja su razne, od jednog <br>
        broja, do odabira trecina ili polovina te boja. <br> 
        Prije nego što se kolo zavrti igrac <br>
        postavlja ulog tako sto oznaci jedno ili <br>
        vise mogucih polja. Oznaceno polje mozete <br>
        odznaciti desnim klikom, a ukoliko zelite <br>
        maknuti sve uloge, pritisnite Resetiraj. <br><br>
        <b style="margin-left: 30%;">SRETNO!</b><br><br>
    </div>
    <label for="ulog">Vas ulog:</label>
    <input type="number" min="1" id="ulog" value="2">
    <br>
    <button type="submit" id="start">Zavrti</button>
    <button type="button" id="pravila">Pravila i upute</button>
    <button type="reset" id="odznaci">Resetiraj</button>
    <br>
    <canvas id="roullet" width="650" height="250"></canvas>
    <canvas id="counter" width="150" height="150"></canvas>
    <br>
    <br>
    <h3 id="error"></h4>
    </div>

    <script type="text/javascript" src="javascript/rulet.js">
    </script>
    
<?php require_once __DIR__ . '/_footer.php'; ?>  