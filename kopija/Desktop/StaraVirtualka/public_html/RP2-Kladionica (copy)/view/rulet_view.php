<?php require_once __DIR__ . '/_header.php'; ?>
    <div id="ruletDiv">
    <h3 id="krediti"></h3>
    <h4 id="trenutni_ulog"></h4>
    <label for="ulog">Vas ulog:</label>
    <input type="number" min="1" id="ulog" value="2">
    <br>
    <button type="submit" id="start">Zavrti</button>
    <button type="button" id="pravila">Pravila i upute</button>
    <button type="reset" id="odznaci">Resetiraj</button>
    <br>
    <canvas id="roullet" width="650" height="250"></canvas>
    <br>
    <br>
    <h3 id="error"></h4>
    </div>

    <script type="text/javascript" src="javascript/rulet.js">
    </script>
    
<?php require_once __DIR__ . '/_footer.php'; ?>  