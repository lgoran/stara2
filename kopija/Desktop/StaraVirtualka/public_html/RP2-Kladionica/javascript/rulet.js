$(document).ready(function () {
    Initialize();
    createTable();
    $("#roullet").click(markCell);
    $("#start").click(function() {
        if (uvjetiZaIgru() === false) 
        {
            $("#error").text("Morate postaviti zetone na plocu!");
            return;
        }
        var ID = setInterval(startCounter, 25);
        setTimeout(igraj, 3000, ID);
    });
    $("#pravila").click(vidiPravila);
    $("#ulog").on("keypress", onlyNumbersInput);
    $("#odznaci").click(resetiraj);
    $("#exitButtonPravila").click(zatvoriPravila);
    $("#roullet").on("contextmenu", removeCoin);
});

var stanjeNaRacunu; // trebat ce nesto iz sessiona
var table;
var canvas = $("#roullet").get(0);
var ctx = canvas.getContext("2d");
var c = document.getElementById("counter").getContext("2d");
var trenutniUlog = 0;
var counterVar = 0;

function Initialize()
{
    $("#divPravila").hide();
    counterVar = 0;
    trenutniUlog = 0;
    stanjeNaRacunu = parseFloat($("#stanje_racuna").html());
    $("#error").text("");
    //$("#krediti").text("Stanje na racunu: " + stanjeNaRacunu + " kredita");
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

function drawNumber(i, j) {
    ctx.beginPath();
    if (j % 2 === 0) ctx.fillStyle = "black";
    else ctx.fillStyle = "red";
    ctx.fillRect(j * 50, i * 50, 49, 49);

    ctx.font = "bold 25px Comic Sans MS";
    ctx.textAlign = "center";
    ctx.fillStyle = "white";
    ctx.fillText((i * 12 + j).toString(), j * 50 + 25, i * 50 + 35);
}

function drawNumbers() {
    for (var i = 0; i < 3; i++)
        for (var j = 1; j <= 12; j++)
            drawNumber(i, j);
}

function drawThird(i) {
    ctx.beginPath();
    ctx.fillStyle = "green";
    ctx.fillRect(50 + i * 200, 150, 199, 49);

    ctx.font = "bold 25px Comic Sans MS";
    ctx.textAlign = "center";
    ctx.fillStyle = "white";
    ctx.fillText((i * 12 + 1).toString() + " - " + (i * 12 + 12).toString(), 150 + i * 200, 185);
}

function drawThirds() {
    for (var i = 0; i < 3; i++) {
        drawThird(i);
    }
}

function drawHalf(i, fillColor, value) 
{
    ctx.beginPath();
    ctx.fillStyle = fillColor;
    ctx.fillRect(50 + i * 150, 200, 149, 49);

    ctx.font = "bold 25px Comic Sans MS";
    ctx.textAlign = "center";
    ctx.fillStyle = "white";
    ctx.fillText(value, 125 + i * 150, 235);
    
}

function drawHalfs() {
    drawHalf(0, "green", "1 - 18");
    drawHalf(1, "red", "RED");
    drawHalf(2, "black", "BLACK");
    drawHalf(3, "green", "19 - 36");
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

function removeCoin(event) 
{
    var mousePosition = getMousePosition(event);
    var indexes = getRowAndCol(mousePosition.x, mousePosition.y);
    var mark = markTable(indexes.i, indexes.j);
    if (table[mark.index] === 0) return;
    trenutniUlog -= table[mark.index];
    $("#trenutni_ulog").text("Trenutno stanje na ploci: " + trenutniUlog + " kredita");
    table[mark.index] = 0;
    if (mark.index === 0) 
        drawZero();
    else if (mark.index >= 1 && mark.index <= 36)
        drawNumber(mark.j, mark.i);
    else if (mark.index >= 37 && mark.index <= 39)
        drawThird(mark.index % 37);
    else if (mark.index === 40)
        drawHalf(0, "green", "1 - 18");
    else if (mark.index === 41)
        drawHalf(1, "red", "RED");
    else if (mark.index === 42)
        drawHalf(2, "black", "BLACK");
    else if (mark.index === 43)
        drawHalf(3, "green", "19 - 36");

    return false;
}

function drawCounter()
{
    var grd = c.createRadialGradient(75, 75, 65, 75, 75, 75);
    grd.addColorStop(0, "white");
    grd.addColorStop(1, "black");
    c.beginPath();
    c.arc(75, 75, 75, 0, 2 * Math.PI);
    c.fillStyle = grd;
    c.fill();
    
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
    //drawCoin(mark.i, mark.j, pom);
    /* if (table[mark.index] !== 0)
    {
        trenutniUlog -= table[mark.index];
    } */
    table[mark.index] += pom;
    drawCoin(mark.i, mark.j, table[mark.index]); 
    trenutniUlog += pom;
    
    $("#trenutni_ulog").text("Trenutno stanje na ploci: " + trenutniUlog + " kredita");
       
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

function igraj(ID)
{
    stopCounter(ID);

    var izvuceniBroj = getRandomNumber();
    drawCounter();
    fillCounter(izvuceniBroj, "red");
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

    $("#user_iznos").html(stanjeNaRacunu + " kredita");
    $("#stanje_racuna").html(stanjeNaRacunu);

    updateIznos();
    resetiraj();
}

function vidiPravila()
{
    $("#divPravila").show();
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

function fillCounter(counterVar, color) 
{
    c.font = "bold 90px Comic Sans MS";
    c.textAlign = "center";
    c.fillStyle = color;
    c.fillText(counterVar.toString(), 75, 110);
}

function startCounter() 
{
    counterVar = (counterVar + 1) % 37;
    drawCounter();
    fillCounter(counterVar, "blue");
}

function stopCounter(ID)
{
    clearInterval(ID);
}

function zatvoriPravila()
{
    $("#divPravila").hide();
}

function updateIznos()
{
    $.ajax(
        {
            url: "index.php?rt=rulet/update",
            data:
            {
                stanje_racuna: stanjeNaRacunu,
            },
            success: function( )
            {
                console.log("Uspiješan Ajax");
            },
            error: function( xhr, status )
            {
                if( status !== null )
                    console.log( "Greška prilikom Ajax poziva: " + status );                
            }
        } );
}