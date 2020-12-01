$( document ).ready( function()
{   
    draw_canvas();
    $( "#h" ).html("Stanje na računu: " + novac + " kredita.");
    $( "#btn" ).on( "click", pokreni_igru );
    $( "#pravila" ).on( "click", vidi_pravila );
    $( "#nova" ).on( "click", nova_igra);
    $( "#canvas" ).on( "click", oznaci );

    //okvir služi za ispis pravila kao i ispis poruka na kraju igre
    var okvir = $('<div id ="okvir"></div>');
    okvir.css("position","absolute").css("top","20%").css("left","30%").css("height","60%").css("border","4px solid #00ff00")
        .css("width","40%").css("text-align","center").css("background-color", "#006622").hide();
    var x1 = $('<button>X</button>').on("click", function(){
        $("#okvir").hide();
        igra_se = 0;
    }).css("position","absolute").css("width","6%").css("height", "6%").css("font-size","100%").css("border","none").css("border","2px solid black")
        .css("background-color","red").css("top","2%").css("right","1%").css("color","white").css("border-radius", "40%");
    var opis = $('<p id = "opis"></p>').css("position","center").css("color","white");
    okvir.append(x1);
    okvir.append(opis);
    $("body").append(okvir);

    //služi za ispis odabira sistema
    var sistem = $('<div id ="sistem"></div>');
    sistem.css("position","absolute").css("top","20%").css("left","30%").css("height","55%").css("border","4px solid #00b386")
        .css("width","40%").css("text-align","center").css("background-color", "#00ffbf").hide();
    var x2 = $('<button id="X">X</button>').on("click", function(){
        $("#tekst").empty();
        $("#sistem").hide();
        igra_se = 0;
    }).css("position","absolute").css("width","5%").css("height", "5%").css("font-size","100%").css("border","none").css("border","2px solid black")
        .css("background-color","red").css("top","2%").css("right","1%").css("color","white").css("border-radius", "50%");;
    var tekst = $('<p id="tekst"></p><br>').css("padding","5%").css("font-size","1.3vw");
    sistem.append(x2);
    sistem.append(tekst);
    $("body").append(sistem);
} );


var igra_se = 0;
// Novac se mora prominit
var novac = stanje_racuna=parseFloat($("#stanje_racuna").html());
var colors = ["#0066ff", "red", "#00FF7F", "yellow", "magenta", "#FF8C00", "cyan","grey","white"]
var pressed = new Set();
var broj_pogodenih;

function vidi_pravila(){
    if (igra_se) return;
    igra_se = 1;
    $("#opis").html("Grčki loto sastoji se od izvlačenja 20 brojeva iz skupa od 80 brojeva. Igrač može izabrati između \
<b>jednog i dvanaest</b> brojeva na koje se želi kladiti. Nakon što odabere svoje brojeve te unese neki ulog, treba stisnuti na \
gumb <i>Igraj</i>. Igrač zatim ima priliku birati sistem svoje igre. Sistem omogučava igraču da, ako i ne pogodi sve brojeve,\
 može osvojiti neki iznos. Primjerice, ako je birao 10 brojeva te sistem 5/10, ako među 20 brojeva koji izađu bude barem \
5 onih koje je igrač izabrao, igrač će osvojiti dobitak. Nakon odabira sistema, igra se započinje klikom na gumb <i>Pokreni igru!</i>. \
Gumb <i>Nova igra</i> briše odabrane brojeve.").css("font-size","1.3vw").css("padding","7%");
    $("#okvir").show();
}

function oznaci() {
    if (igra_se) return;
    var ctx = this.getContext( "2d" );
    var rect = this.getBoundingClientRect();
    var x = event.clientX - rect.left, y = event.clientY - rect.top;
    var size = rect.width / 40,i,j;
    if (y > 2*size) return;
    for (i = 0; i < 2; i++){
        for (j = 0; j < 40; j++)
            if (y < ((i+1)*size + 2) && x < (j+1)*size){
                var row = i;
                var col = j;
                var flag = 1;
                break;
            }
        if (flag) break;
    }
    var num = (i == 0) ? (j+1) : (j+1 + 40);
    if (pressed.has(num)){
        pressed.delete(num);
        draw_canvas();
    }
    else {
        if (pressed.size == 12) return;
        pressed.add(num);
        draw_canvas();
    }
}

function draw_canvas(){
    var ctx = $("#canvas").get(0).getContext("2d");
    var rect = $("#canvas").get(0).getBoundingClientRect();
    ctx.lineWidth = "3";
    ctx.textAlign = "center";
    var size = rect.width / 40;
    var num = 1;
    for (var i = 0; i < 2; i++)
        for (var j = 0; j < 40; j++){
            if (pressed.has(num)) ctx.fillStyle = "#ff6666";
            else ctx.fillStyle = "azure";

            ctx.strokeRect(j*size,i*size + 2, size, size);
            ctx.fillRect(j*size,i*size + 2, size, size);
            ctx.fillStyle = "black";
            ctx.font = "15px Arial";
            ctx.fillText(num, j*size + size/2, i*size + 2*size/3 + 2);
            num++;
        }
}
function nova_igra(){
    if (igra_se) return;
    pressed.clear();
    draw_canvas();
    $( "#p" ).html("");
    var c = document.getElementById("canvas");
    var ctx = c.getContext("2d");
    var rect = c.getBoundingClientRect();
    ctx.clearRect(0, 3*rect.width/40, canvas.width, canvas.height);
}

function pokreni_igru(){
    if (igra_se) return;
    var n = $("#num").val();
    if (!n){
        $( "#p" ).html("<b>Molimo unesite neki iznos.</b>");
        return;
    }
    if (pressed.size < 1){
        $( "#p" ).html("<b>Morate izabrat barem jedan broj!</b>");
        return;
    }
    if (n > novac) {
        $( "#p" ).html("<b>Nemate toliko kredita.</b>");
        return;
    }
    igra_se = 1;
    $("#tekst").html('Odaberite sistem koji želite igrati<br><br>');
    var broj_oznacenih = pressed.size;
    var start;
    if (broj_oznacenih >= 9) start = 4;
    else if (broj_oznacenih >= 6) start = 3;
    else start = 2;
    for (var i = start; i < broj_oznacenih; i++){
        var check = $('<input type="radio" id="' + i +'" name="sist" value="'+i+'">\
            <label for="'+i+'">' + i + '/' + broj_oznacenih +'</label><br>');
        $("#tekst").append(check);
    }
    var check = $('<input type="radio" id="' + broj_oznacenih +'" name="sist" checked>\
        <label for="'+broj_oznacenih+'">' + broj_oznacenih + '/' + broj_oznacenih +'</label><br>');
    $("#tekst").append(check);
    var submit_button = $('<button id = "start_btn" onclick="igraj();">Pokreni igru!</button>')
    $("#tekst").append(submit_button);
    $("#sistem").show();
}

function igraj(){

    var radios = document.getElementsByName('sist');
    var br_sistema;
    for (var i = 0, length = radios.length; i < length; i++) 
        if (radios[i].checked)
            if (radios[i].value == "on")
                br_sistema = pressed.size;
            else br_sistema = radios[i].value;

    $("#tekst").empty();
    $("#sistem").hide();
    $("#p").html("");

    var n = $("#num").val();
    var c = document.getElementById("canvas");
    var ctx = c.getContext("2d");
    var rect = c.getBoundingClientRect();
    ctx.clearRect(0, 3*rect.width/40, canvas.width, canvas.height);

   // $( "#h" ).html("Stanje na računu: " + novac + " kredita.");
    var tocka = {
        x: rect.left + 50, 
        y: rect.top - 200
    };
    var r = 40, arr = new Set();
    broj_pogodenih = 0;
    //var x = rect.left + 50, y = rect.top, r = 40;
    ctx.font = "30px Arial";
    ctx.textAlign = "center";
    var id = setInterval(crtaj, 100);
    
    function crtaj(){
        while(1){
            var broj = Math.floor(Math.random() * 80) + 1;
            if (arr.has(broj))
                continue;
            else{
                arr.add(broj);
                break;
            }
        }
        if (pressed.has(broj)) broj_pogodenih++;
        ctx.beginPath();
        ctx.arc(tocka.x, tocka.y, r, 0, 2 * Math.PI);
        ctx.fillStyle = colors[Math.floor((broj - 1)/10)];
        ctx.fill();
        ctx.lineWidth = 3;
        ctx.strokeStyle = "black";
        ctx.stroke();
        ctx.strokeText(broj.toString(), tocka.x, tocka.y+10);
        if (arr.size == 10){
            tocka.x = rect.left + 50;
            tocka.y += 100;
            return;
        }
        else if (arr.size == 20){
            clearInterval(id);
            //$("#p").html('<p>Pogodili ste ' + broj_pogodenih + ' od ' + pressed.size + ' brojeva.</p>');
            var rez = dobitak(broj_pogodenih, n, br_sistema);
            if (rez == 0){
                novac -= n;
                $( "#h" ).html("Stanje na računu: " + novac + " kredita.");
                update_iznos(novac)
                izgubljeno(broj_pogodenih);
            }
            else {
                novac += rez;
                $( "#h" ).html("Stanje na računu: " + novac + " kredita.");
                update_iznos(novac)
                dobiveno(rez,broj_pogodenih);
            }
            return;
        }
        tocka.x+=100;
    }
    
}
function dobitak(broj, ulog, br_sistema){
    if (broj < br_sistema) 
        return 0;
    var rez = ulog * 4.11;
    for (var i = 1; i < broj; i++) rez *= 4.11;
    if (br_sistema == pressed.size)
        return parseFloat( rez.toFixed(2));
    else{
        for (var i = 0; i < pressed.size - broj; i++){
            rez *= (0.75 - i*0.05);
        }
    }
    return parseFloat( rez.toFixed(2));
}
function izgubljeno(broj_pogodenih){
    $("#opis").html("<b>Izgubili ste!</b><br>Pogodili ste " + broj_pogodenih + " od " + pressed.size + " brojeva.")
            .css("font-size","2.3vw").css("padding-top", "23%");
    $("#okvir").show();
}
function dobiveno(iznos, broj_pogodenih){
    $("#opis").html("<b>Čestitamo!</b><br>Pogodili ste " + broj_pogodenih + " od " + pressed.size + " brojeva.<br>Osvojili ste <b>" + iznos + "</b> kredita.")
            .css("font-size","2vw").css("padding-top","21%");
    $("#okvir").show();
}

function update_iznos(iznos){
    $.ajax(
        {
            url: "index.php?rt=grcki_loto/update",
            data:
            {
                stanje_racuna: iznos,
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

