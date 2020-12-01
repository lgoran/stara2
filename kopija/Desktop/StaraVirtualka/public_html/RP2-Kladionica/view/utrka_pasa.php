<?php require_once __DIR__ . '/_header.php'; ?>

    <canvas width="20" height="600" id="canvas" style="border:black solid 3px;float: right;"></canvas>
    <h1><?php $title ?></h1>
    <div class="utrka_pasa_oklada" id="oklada">   
           
        <p style="text-align:center;color:gold;"><b >Odaberi psa</b>:</p><hr>
        
        <input type="radio" name="odabir" id="pas1" checked><label for="pas1">Jack</label><br>
        <input type="radio" name="odabir" id="pas2"><label for="pas2">John</label><br>    
        <input type="radio" name="odabir" id="pas3"><label for="pas3">Mack</label><br>
        <input type="radio" name="odabir" id="pas4"><label for="pas4">Phil</label><br>     
        <input type="radio" name="odabir" id="pas5"><label for="pas5">Guns</label><br>

        <input type="text" id="ulog" placeholder="Vaš ulog" maxlength="5" size="3" >
        <button id="ulozi" style="background-color:darkorange;height:30px">Igraj</button>
        <p>Stanje računa: <span id="stanje_racuna"><?php echo $iznos;?></span></p>
        <p id="pobjednik" style="font-weight: bold;"></p>
    </div>
    <hr class="utrka_pasa_hr">

    Pas 1: <b>Jack</b>
    <p id="p1" style="text-indent: 0px;"><span><img src="slike/dog1.jpeg" alt="dog1" width="50px"></span></p>
    <hr class="utrka_pasa_hr">
    
    Pas 2:<b>John</b>
    <p id="p2" style="text-indent: 0px;"><span><img src="slike/dog2.jpeg" alt="dog2" width="50px"></span></p>
    <hr class="utrka_pasa_hr">
    
    Pas 3:<b>Mack</b>
    <p id="p3" style="text-indent: 0px;"><span><img src="slike/dog3.webp" alt="dog3" width="50px"></span></p>
    <hr class="utrka_pasa_hr">
    
    Pas 4:<b>Phil</b>
    <p id="p4" style="text-indent: 0px;"><span><img src="slike/dog4.webp" alt="dog4" width="50px"></span></p>
    <hr class="utrka_pasa_hr">
    
    Pas 5:<b>Guns</b>
    <p id="p5" style="text-indent: 0px;"><span><img src="slike/dog5.webp" alt="dog5" width="50px"></span></p>
    <hr class="utrka_pasa_hr">
    
    <script type="text/javascript" src="javascript/utrka_pasa.js"></script>

<?php require_once __DIR__ . '/_footer.php'; ?>    
