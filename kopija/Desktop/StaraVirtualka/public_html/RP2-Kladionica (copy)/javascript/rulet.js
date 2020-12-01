$(document).ready(function () {
    Initialize();
    createTable();
    $("#roullet").click(markCell);
    $("#start").click(igraj)
    $("#pravila").click(vidiPravila);
    $("#ulog").on("keypress", onlyNumbersInput);
    $("#odznaci").click(resetiraj)
});

var stanjeNaRacunu = 100; // trebat ce nesto iz sessiona
var table;
var canvas = $("#roullet").get(0);
var ctx = canvas.getContext("2d");
var trenutniUlog = 0;

function Initialize()
{
    trenutniUlog = 0;
    $("#error").text("");
    $("#krediti").text("Stanje na racunu: " + stanjeNaRacunu + " kredita");
    $("#trenutni_ulog").text("Trenutno stanje na ploci: " + trenutniUlog + " kredita");
    $("#ulog").prop("max", stanjeNaRacunu.toString());
    table = new Array(44);
    for (var i = 0; i < 44; i++)
        table[i] = 0;
}

function createTable() {
    drawZero();
    drawNumbers();
    drawThirds();
    drawHalfs();
}

function drawZero() {
    ctx.beginPath();
    ctx.fillStyle = "lightgreen";
    ctx.fillRect(0, 0, 49, 5 * 50);
    ctx.font = "bold 25px Comic Sans MS";
    ctx.textAlign = "center";
    ctx.fillStyle = "white";
    ctx.fillText("0", 25, 135);
}

function drawNumbers() {
    for (var i = 0; i < 3; i++) {
        for (var j = 1; j <= 12; j++) {
            ctx.beginPath();
            if (j % 2 === 0) ctx.fillStyle = "black";
            else ctx.fillStyle = "red";
            ctx.fillRect(j * 50, i * 50, 49, 49);

            ctx.font = "bold 25px Comic Sans MS";
            ctx.textAlign = "center";
            ctx.fillStyle = "white";
            ctx.fillText((i * 12 + j).toString(), j * 50 + 25, i * 50 + 35);
        }
    }
}

function drawThirds() {
    for (var i = 0; i < 3; i++) {
        ctx.beginPath();
        ctx.fillStyle = "green";
        ctx.fillRect(50 + i * 200, 150, 199, 49);

        ctx.font = "bold 25px Comic Sans MS";
        ctx.textAlign = "center";
        ctx.fillStyle = "white";
        ctx.fillText((i * 12 + 1).toString() + " - " + (i * 12 + 12).toString(), 150 + i * 200, 185);
    }
}

function drawHalfs() {
    for (var i = 0; i < 4; i++) {
        ctx.beginPath();
        if (i == 1)
            ctx.fillStyle = "red";
        else if (i == 2)
            ctx.fillStyle = "black";
        else
            ctx.fillStyle = "green";
        ctx.fillRect(50 + i * 150, 200, 149, 49);

        ctx.font = "bold 25px Comic Sans MS";
        ctx.textAlign = "center";
        ctx.fillStyle = "white";
        if (i == 0 || i == 3)
            ctx.fillText(((i % 2) * 18 + 1).toString() + " - " + ((i % 2) * 18 + 18).toString(), 125 + i * 150, 235);
        else if (i == 1)
            ctx.fillText("RED", 125 + i * 150, 235);
        else
            ctx.fillText("BLACK", 125 + i * 150, 235);
    }
}

function drawCoin(x, y, value) 
{
    ctx.beginPath();
    ctx.arc(x * 50 + 25, y * 50 + 25, 18, 0, 2 * Math.PI);
    ctx.fillStyle = "gold";
    ctx.fill();
    ctx.font = "bold 25px Comic Sans MS";
    ctx.textAlign = "center";
    ctx.fillStyle = "purple";
    ctx.fillText(value, x * 50 + 25, y * 50 + 35);
}

function getRowAndCol(x, y) {
    return {
        i: Math.floor(y / 50),
        j: Math.floor(x / 50)
    };
}

function getMousePosition(event) 
{
    var rect = canvas.getBoundingClientRect();
    return {
        x: event.clientX - rect.left,
        y: event.clientY - rect.top
    };
}

function markCell(event)
{
    var pom = Number ($("#ulog").val() );
    if (pom < 0 || pom > stanjeNaRacunu || trenutniUlog > stanjeNaRacunu || trenutniUlog + pom > stanjeNaRacunu)
    {
        $("#error").text("Nemate dovoljno kredita na racunu!");
        return;
    }
    var mousePosition = getMousePosition(event);
    var indexes = getRowAndCol(mousePosition.x, mousePosition.y);
    var mark = markTable(indexes.i, indexes.j);
    console.log(mark);
    drawCoin(mark.i, mark.j, pom);
    if (table[mark.index] !== 0)
    {
        trenutniUlog -= table[mark.index];
    }
    table[mark.index] = pom; 
    trenutniUlog += pom;
    
    $("#trenutni_ulog").text("Trenutno stanje na ploci: " + trenutniUlog + " kredita")
       
}

function markTable(i, j) 
{
    if (j === 0) return {index: 0, i: 0, j: 2 };
    if (i === 3 && j >= 1 && j <= 4) return {index: 37, i: 2.5, j: 3 };
    if (i === 3 && j >= 5 && j <= 8) return {index: 38, i: 6.5, j: 3 };
    if (i === 3 && j >= 9 && j <= 12) return {index: 39, i: 10.5, j: 3 };
    if (i === 4 && j >= 1 && j <= 3) return {index: 40, i: 2, j: 4 };
    if (i === 4 && j >= 4 && j <= 6) return {index:41, i: 5, j:4 };
    if (i === 4 && j >= 7 && j <= 9) return {index: 42, i: 8, j: 4 };
    if (i === 4 && j >= 10 && j <= 12) return {index: 43, i: 11, j: 4 };
    return {index: j + i * 12, i: j, j: i };
}

function uvjetiZaIgru()
{
    for (var i = 0; i < 44; i++)
        if (table[i] !== 0) return true;

    return false;
}

function getRandomNumber()
{
    // generira cijeli broj izmedu 0 i 36
    return Math.floor(Math.random() * Math.floor(36));
}

function vratiDobitak(izvuceniBroj)
{
    if (table[izvuceniBroj] !== 0) return 36 * table[izvuceniBroj];
    if (izvuceniBroj >= 1 && izvuceniBroj <=12 && table[37] !== 0) return table[37] * 3;
    if (izvuceniBroj >= 13 && izvuceniBroj <=24 && table[38] !== 0) return table[38] * 3;
    if (izvuceniBroj >= 25 && izvuceniBroj <=36 && table[39] !== 0) return table[39] * 3;
    if (izvuceniBroj >= 1 && izvuceniBroj <=18 && table[40] !== 0) return table[40] * 2;
    if (izvuceniBroj % 2 == 1 && table[41] !== 0) return table[41] * 2;
    if (izvuceniBroj % 2 == 0 && table[42] !== 0) return table[42] * 2;
    if (izvuceniBroj >= 19 && izvuceniBroj <=36 && table[43] !== 0) return table[43] * 2;

    return 0;
}

function igraj()
{
    if (uvjetiZaIgru() === false) 
    {
        $("#error").text("Morate postaviti zetone na plocu!");
        return;
    }

    var izvuceniBroj = getRandomNumber();
    var dobitak = vratiDobitak(izvuceniBroj);
    if (dobitak === 0) 
    {
        stanjeNaRacunu -= trenutniUlog;
        alert("Izvuceni broj je " + izvuceniBroj.toString() + ". Izgubili ste.");
    }
    else
    {
        stanjeNaRacunu = stanjeNaRacunu + dobitak - trenutniUlog;
        alert("Izvuceni broj je " + izvuceniBroj.toString() + ". Dobili ste " + (dobitak - trenutniUlog).toString() + " kredita.");
    }

    resetiraj();
}

function vidiPravila()
{
    alert("Rulet je jedna od najpopularnijih svjetskih igara na srecu. Igra se pomocu \
            specijalnog kola koji se sastoji od 37 brojeva (0 - 36). Brojevi su naizmjence \
            oznaceni crvenom i crnom bojom, osim nule koja je zelena. Prije nego što se kolo zavrti \
            igrac postavlja ulog tako sto oznaci jedno ili vise mogucih polja. Ako zelite odznaciti polje, \
            postavite njegov ulog na 0, a ukoliko zelite maknuti sve uloge, pritisnite Reset. Sretno!");
}

function onlyNumbersInput(evt) 
{
    var charCode = (evt.which) ? evt.which : event.keyCode;
    if (charCode > 31 && (charCode < 48 || charCode > 57))
        return false;

    return true;
}

function resetiraj() 
{
    Initialize();
    createTable();
}