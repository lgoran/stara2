var tiket=[];
$( document ).ready(function() {
    $("#uplaceni_iznos").on("input",function()
    {
        var str=$("#uplaceni_iznos").val();
        if(isNaN(str))
        {
            $("#uplaceni_iznos").val(str.substring(0,str.length-1));
            alert("Iznos mora biti broj");
            return;
        }
        else
        {
            if(parseFloat(str)<1)
            {
                str="1";
                $("#uplaceni_iznos").val(1);
            }
            
            $("#potencijalni_dobitak").html((parseFloat(str)*parseFloat($("#ukupna_kvota").html())).toFixed(3));
        }
        if(str==="")
            $("#potencijalni_dobitak").html(0);
    })
    $("button").on("click",function()
    {
        var botun_id=$(this).attr("id");
        if(botun_id==="uplati")
            return;
        var botun_html=$(this).html();
        var utakmica_id=0;
        var opcija="";
        for(var i=0;i<botun_id.length;i++)
        {
            if(botun_id[i]==="b")
            {
                opcija=botun_id.substring(i+1);
                break;
            }
            utakmica_id*=10;
            utakmica_id+=parseInt(botun_id[i]);
        }
        var par_array=[utakmica_id,botun_html,opcija];
        if(tiket.length===0)
        {
            tiket.push(par_array);
        }
        else if(tiket.length>0)
            for(var i=0;i<tiket.length;i++)
            {
                if(tiket[i][0]===utakmica_id)
                {
                    if(tiket[i][2]===opcija)
                    {
                        return;
                    }
                    else
                    {
                        tiket[i][1]=botun_html;
                        tiket[i][2]=opcija;
                    }
                    break;
                }
                if(i===tiket.length-1)
                {
                    tiket.push(par_array);
                    break;
                }
            }
            crtaj_listic();
    }
    )
    $("#uplati").on("click",function()
    {
        //posalji tiket;
        //skini pare;
        if(tiket.length===0)
        {
            alert("Niste odabrali niti jedan par");
            return;
        }
        var stanje_racuna=parseFloat($("#stanje_racuna").html());
        var uplaceni_iznos=parseFloat($("#uplaceni_iznos").val());
        if(isNaN(uplaceni_iznos) || uplaceni_iznos<=0)
        {
            alert("Niste unijeli iznos za klađenje!");
            return;
        }
        if(stanje_racuna<uplaceni_iznos)
        {
            alert("Nemate dovoljno kredita");
            return;
        }
        else
        {
            stanje_racuna-=uplaceni_iznos;
        }
        $("#stanje_racuna").html(stanje_racuna);
        var ukupna_kvota=$("#ukupna_kvota").html();
        var potencijalni_dobitak=$("#potencijalni_dobitak").html();
        $.ajax(
            {
                url: "index.php?rt=sport/update",
                data:
                {
                    tiket: tiket,
                    potencijalni_dobitak: potencijalni_dobitak,
                    ukupna_kvota: ukupna_kvota,
                    uplaceni_iznos: uplaceni_iznos,
                    stanje_racuna: stanje_racuna,
                },
                success: function( )
                {
                    console.log("uspijeh");
                    window.location.href="index.php?rt=sport/index";

                },
                error: function( xhr, status )
                {
                    if( status !== null )
                        console.log( "Greška prilikom Ajax poziva: " + status );
                    
                }
            } );
    })
    $("h2").on("click",function()
    {
        var id=$(this).attr("id");
        id=id.replace("sport","tabla");
        console.log(id);
        if($("#"+id).is(":hidden"))
        {
            $("#"+id).show();
        }
        else
        {
            $("#"+id).hide();
        }
    })
    
    
});
function crtaj_listic()
    {
        $("#odigrani_parovi").html("");
        var kvota=1.0;
        for(var i=0;i<tiket.length;i++)
        {
            kvota*=parseFloat(tiket[i][1]);
            $("#odigrani_parovi").html($("#odigrani_parovi").html()+
                    "<br>"+"Utakmica ID:"+tiket[i][0]+'<button disabled>'+tiket[i][2]+'</button>'+'<button disabled>'+tiket[i][1]+'</button>'+
                    '<button onclick="brisi_par('+tiket[i][0]+')" style="color:red;float:right;">X</button>');
        }
        $("#ukupna_kvota").html(kvota.toFixed(3));
        $("#potencijalni_dobitak").html((parseFloat($("#uplaceni_iznos").val())*parseFloat($("#ukupna_kvota").html())).toFixed(3));

    }
function brisi_par(id){
    var utakmica_id=parseInt(id);
    for(var i=0;i<tiket.length;i++)
    {
        if(tiket[i][0]===utakmica_id)
        {
            tiket.splice(i,1);
            break;
        }
    }
    crtaj_listic();
}