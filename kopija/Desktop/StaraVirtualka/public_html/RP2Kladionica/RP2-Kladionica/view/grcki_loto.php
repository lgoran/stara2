<?php require_once __DIR__ . '/_header.php'; ?>

    <header id = "h">Stanje na računu: <span id="stanje_racuna"><?php echo $stanje;?></span></header>
    <input type="number" id="num" min="1"><button id="btn">Igraj</button> <br>
    <button id="nova">Nova igra</button>
    <button id="pravila">Vidi Pravila</button> <br>
    <br /><br />
    <canvas width="1500" height="500" style="border: none" id="canvas"></canvas>
    <p id = "p" style="font-size:1.3vw;"></p><br>
    <script type="text/javascript" src="javascript/grcki_loto.js"></script>
    
<?php require_once __DIR__ . '/_footer.php'; ?>  