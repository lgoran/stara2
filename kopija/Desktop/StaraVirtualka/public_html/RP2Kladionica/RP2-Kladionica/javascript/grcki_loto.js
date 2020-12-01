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
    //stvori button X za zatvoriti prozor   
    var x1 = $('<button>X</button>').on("click", function(){
        $("#okvir").hide();
        igra_se = 0;
    }).css("position","absolute").css("width","fit-content").css("height", "fit-content").css("font-size","28px").css("border","none").css("border","2px solid black")
        .css("background-color","red").css("top","2%").css("right","1%").css("color","white").css("border-radius", "50%");
    //mjesto za ispis teksta
    var opis = $('<p id = "opis"></p>').css("position","center").css("color","white");
    okvir.append(x1);
    okvir.append(opis);
    $("body").append(okvir);

    //služi za ispis odabira sistema
    var sistem = $('<div id ="sistem"></div>');
    sistem.css("position","absolute").css("top","20%").css("left","30%").css("height","fit-content").css("border","4px solid #00b386")
        .css("width","40%").css("text-align","center").css("background-color", "#00ffbf").hide();
    var x2 = $('<button id="X">X</button>').on("click", function(){
        $("#tekst").empty();
        $("#sistem").hide();
        igra_se = 0;
    }).css("position","absolute").css("width","fit-content").css("height", "fit-content").css("font-size","28px").css("border","none").css("border","2px solid black")
        .css("background-color","red").css("top","2%").css("right","1%").css("color","white").css("border-radius", "50%");;
    var tekst = $('<p id="tekst"></p><br>').css("padding","5%").css("font-size","1.3vw");
    sistem.append(x2);
    sistem.append(tekst);
    $("body").append(sistem);
} );


var igra_se = 0;  //oznaka da je igra u tijeku
var novac = stanje_racuna=parseFloat($("#stanje_racuna").html());  //iznos na racunu igraca
var colors = ["#0066ff", "red", "#00FF7F", "yellow", "magenta", "#FF8C00", "cyan","grey","white"]
var pressed = new Set();  //skup brojeva koje je korisnik kliknuo
var broj_pogodenih;  //broji koliko ih je korisnik pogodio

//pokazi okvir s pravilima
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
    // Dodaje ili uklanja broj iz skupa kliknutih brojeva 
    if (igra_se) return;
    var ctx = this.getContext( "2d" );
    var rect = this.getBoundingClientRect();
    var x = event.clientX - rect.left, y = event.clientY - rect.top;
    var size = rect.height / 10 - 1,i,j;
    if (x > 8*size) return;

    //odredi koji je broj kliknut
    for (i = 0; i < 10; i++){
        for (j = 0; j < 8; j++)
            if (y < ((i+1)*size + 2) && x < (j+1)*size){
                var row = i;
                var col = j;
                var flag = 1;
                break;
            }
        if (flag) break;
    }
    var num = i * 8 + j + 1;
    //num je iznos kliknutog broja
    if (pressed.has(num)){
        //izbaci ako se vec nalazi medu kliknutima
        pressed.delete(num);
        draw_canvas();
    }
    else {
        // max se može stisnuti 12 brojeva
        if (pressed.size == 12) return;
        pressed.add(num);
        draw_canvas();
    }
}

function draw_canvas(){
    //crtanje svega što je na canvasu (naravno bez brojeva)
    var ctx = $("#canvas").get(0).getContext("2d");
    var rect = $("#canvas").get(0).getBoundingClientRect();
    ctx.lineWidth = "3";
    ctx.textAlign = "center";
    var size = rect.height / 10 - 1;
    var num = 1;
    
    //nacrtaj plocu s brojevima
    for (var i = 0; i < 10; i++)
        for (var j = 0; j < 8; j++){
            if (pressed.has(num)) ctx.fillStyle = "#ff6666";
            else ctx.fillStyle = "azure";

            ctx.strokeRect(j*size,i*size + 2, size, size);
            ctx.fillRect(j*size,i*size + 2, size, size);
            ctx.fillStyle = "black";
            ctx.font = "22px Arial";
            ctx.fillText(num, j*size + size/2, i*size + 2*size/3 + 2);
            num++;
        }
    ctx.beginPath();
    ctx.moveTo(0,0);
    ctx.lineTo(0,492);
    ctx.stroke();
}

//brise sve kad se stisne nova igra
function nova_igra(){
    if (igra_se) return;
    pressed.clear();
    draw_canvas();
    $( "#p" ).html("");
    var c = document.getElementById("canvas");
    var ctx = c.getContext("2d");
    var rect = c.getBoundingClientRect();
    ctx.clearRect(8 * rect.height / 10 ,0, canvas.width, canvas.height);

}
//implementacija igre kad se stisne button Igraj
function pokreni_igru(){
    if (igra_se) return;
    var n = $("#num").val();
    //3 uvijeta kada igra nije valjana
    if (n <= 0){
        $( "#p" ).html("<b>Molimo unesite neki iznos veći od nule.</b>");
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
    //postavi da je igra u tijeku, da se ne mogu stiskati buttoni i brojevi
    igra_se = 1;
    $("#tekst").html('Odaberite sistem koji želite igrati<br><br>');
    var broj_oznacenih = pressed.size;
    var start;

    // start je minimalan broj u sistemu
    if (broj_oznacenih >= 9) start = 4;
    else if (broj_oznacenih >= 6) start = 3;
    else start = 2;
    
    //stvori radio za sisteme
    for (var i = start; i < broj_oznacenih; i++){
        var check = $('<input type="radio" id="' + i +'" name="sist" value="'+i+'">\
            <label for="'+i+'">' + i + '/' + broj_oznacenih +'</label><br>');
        $("#tekst").append(check);
    }
    var check = $('<input type="radio" id="' + broj_oznacenih +'" name="sist" checked>\
        <label for="'+broj_oznacenih+'">' + broj_oznacenih + '/' + broj_oznacenih +'</label><br>');
    $("#tekst").append(check);
    //stvori button koji pokrece igru
    var submit_button = $('<button id = "start_btn" style="background-color:darkorange; width:25%; font-size:1.2vw; padding:7px;" onclick="igraj();">Pokreni igru!</button>')
    $("#tekst").append(submit_button);
    $("#sistem").show();
}

//pokreće se kad se klikne button Pokreni igru!
function igraj(){

    var radios = document.getElementsByName('sist');
    var br_sistema;
    //odredi izabrani sistem
    for (var i = 0, length = radios.length; i < length; i++) 
        if (radios[i].checked)
            if (radios[i].value == "on")
                br_sistema = pressed.size;
            else br_sistema = radios[i].value;

    $("#tekst").empty();
    $("#sistem").hide();
    $("#p").html("");

    //ocisti sve prije crtanja
    var n = $("#num").val();
    var c = document.getElementById("canvas");
    var ctx = c.getContext("2d");
    var rect = c.getBoundingClientRect();
    ctx.clearRect(8 * rect.height / 10 ,0, canvas.width, canvas.height);

    //tocka predstavlja koordinate krugova s brojevima
    var tocka = {
        x: rect.left + 480, 
        y: rect.top - 160
    };
    var r = 40, arr = new Set(); //Za spremanje brojeva koji su izašli
    broj_pogodenih = 0;
    ctx.font = "30px Arial";
    ctx.textAlign = "center";
    var id = setInterval(crtaj, 300); //Svakih 0.1 sekunde izbaci broj (trebalo bi biti barem 1 sek ali ovako će oduzeti manje vremena)
    
    function crtaj(){
        //odaberi broj koji će izaći
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

        //crtaj broj na canvasu
        ctx.beginPath();
        ctx.arc(tocka.x, tocka.y, r, 0, 2 * Math.PI);
        ctx.fillStyle = colors[Math.floor((broj - 1)/10)];
        ctx.fill();
        console.log("arc");
        ctx.lineWidth = 3;
        ctx.strokeStyle = "black";
        ctx.stroke();
        ctx.strokeText(broj.toString(), tocka.x, tocka.y+10);

        if (arr.size == 10){     //nakon 10og broja pređi u novi red             
            tocka.x = rect.left + 480;
            tocka.y += 100;
            return;
        }
        else if (arr.size == 20){ //gotova igra
            clearInterval(id);
            var rez = dobitak(broj_pogodenih, n, br_sistema);
            rez = rez.toFixed(2);
            rez = parseFloat(rez);
            //rez predstavlja igracev dobitak
            if (rez == 0){
                //igrac je izgubio
                novac -= n;
                $( "#h" ).html("Stanje na računu: " + novac + " kredita.");
                $("#user_iznos").html(novac+" kredita");
                update_iznos(novac)
                izgubljeno(broj_pogodenih);
            }
            else {
                //igrac je dobio
                novac += parseFloat( rez.toFixed(2));
                $( "#h" ).html("Stanje na računu: " + novac + " kredita.");
                $("#user_iznos").html(novac+" kredita");
                update_iznos(novac)
                dobiveno(rez,broj_pogodenih);
            }
            arr.clear();
            
        }
        tocka.x+=100;
    }
    
}
//izračunava dobitak na osnovu izhoda (nije statisticki precizno, ipak nismo statističari)
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
//ispisuje gubitnicki tekst
function izgubljeno(broj_pogodenih){
    $("#opis").html("<b>Izgubili ste!</b><br>Pogodili ste " + broj_pogodenih + " od " + pressed.size + " brojeva.")
            .css("font-size","2.3vw").css("padding-top", "23%");
    $("#okvir").show();
}
//ispisuje dobitnicki tekst
function dobiveno(iznos, broj_pogodenih){
    $("#opis").html("<b>Čestitamo!</b><br>Pogodili ste " + broj_pogodenih + " od " + pressed.size + " brojeva.<br>Osvojili ste <b>" + iznos + "</b> kredita.")
            .css("font-size","2vw").css("padding-top","21%");
    $("#okvir").show();
}

//promijeni iznos u bazi
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

