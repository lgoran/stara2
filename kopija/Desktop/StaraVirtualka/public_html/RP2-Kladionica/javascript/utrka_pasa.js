var ulog;
var radio_id;
var stanje_racuna;
$( document ).ready(function() {
        stanje_racuna=parseFloat($("#stanje_racuna").html());
        crtaj();
        $("#canvas").css("position","absolute");
        $("#canvas").css("left","1000px");
        
        function crtaj() 
        {
            var ctx = $( "#canvas" ).get(0).getContext( "2d" );   
            var promijeni=0;
            for( var x = 0; x < 2; ++x )
                for( var y = 0; y < 99; ++y )
                {
                    if(promijeni==0)
                    {
                        ctx.fillStyle = "black";
                        promijeni=1;
                    }
                    else
                    {
                        ctx.fillStyle = "white";
                        promijeni=0;
                    }
                    
                    ctx.fillRect( x*10, y*10, 10, 10 );
                }
        }
        $("#ulozi").on("click",function()
        {
            
            for(var i =1;i<=5;i++)
            { 
                $( "#p"+ i ).css("text-indent","0px");
            }
            ulog=parseFloat($("#ulog").val());
            radio_id=parseInt($("input[name='odabir']:checked").attr("id")[3]);
            if(isNaN(ulog) || ulog<=0)
            {
                alert("Niste unijeli iznos za klađenje!");
                return;
            }
            if(stanje_racuna<ulog)
            {
                alert("Nemate dovoljno kredita!");
                return;
            }
            $("#oklada").hide();
            move_dogs();
        });
        $("#ulog").on("input",function()
        {
            var str=$("#ulog").val();
            if(isNaN(str))
            {
                $("#ulog").val(str.substring(0,str.length-1));
                alert("Najmanji mogući ulog je 1!");
                return;
            }
            else
            {
                if(parseFloat(str)<1)
                {
                    str="1";
                    $("#ulog").val(1);
                }
                
                $("#potencijalni_dobitak").html((parseFloat(str)*parseFloat($("#ukupna_kvota").html())).toFixed(3));
            }
        })
        function move_dogs() 
        {
            var flag=false;
            for(var i =1;i<=5;i++)
            { 
                var pomicanje=Math.floor(Math.random() * 3) + 1;
                var pikseli=parseInt($( "#p"+ i ).css("text-indent"));
                pikseli+=pomicanje;
                $( "#p"+ i ).css("text-indent",pikseli+"px");
                if(pikseli>1000-50-10)//50 velicina slike,20 velicina canvasa
                {
                    $("#pobjednik").html("Pobjednik pas "+i);
                    flag=true;
                    $("#oklada").show();
                    reguliraj_iznos(i,radio_id);
                    break;
                }
            }
            if(flag==false)
                setTimeout( move_dogs, 10 ); 
        }
});
function reguliraj_iznos(pobjednik,odabrani)
{
    if(pobjednik===odabrani)
    {
        alert("Čestitamo! Osvojili ste "+(4.5*ulog)+" kredita.")
        stanje_racuna+=3.5*ulog;
    }
    else
    {
        stanje_racuna-=ulog;
    }
    $("#user_iznos").html(stanje_racuna+" kredita");
    $("#stanje_racuna").html(stanje_racuna);
    $.ajax(
        {
            url: "index.php?rt=utrka_pasa/update",
            data:
            {
                stanje_racuna: stanje_racuna,
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