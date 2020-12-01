<?php require_once __DIR__ . '/_header.php'; ?>

<?php 
    if(isset($poruka_o_uplati))
    {
        echo '<h3>' . $poruka_o_uplati . '</h3><hr><br>';
    }
?>

<form class="uplata_na_racun" action="index.php?rt=uplata_na_racun/uplati" method="post">
    <h3>Manje uplate na račun</h3>
    <dl>
        <dt><label for="manja_uplata">Odaberite iznos uplate:</label></dt>
        <dd>
            <select name="manja_uplata" id="manja_uplata">
                <option selected="selected" disabled="disabled">Vaša uplata...</option>
                <option value="10">10 kredita</option>
                <option value="20">20 kredita</option>
                <option value="30">30 kredita</option>
                <option value="40">40 kredita</option>
                <option value="50">50 kredita</option>
                <option value="60">60 kredita</option>
            </select>
        </dd>
        <dt class="full" id="izvrsi_uplatu">
            <button type="submit">Izvršite uplatu!</button>
        </dt>
    </dl>
</form>

<br>
<hr>
<br>

<form class="uplata_na_racun" action="https://www.paypal.com/cgi-bin/webscr" method="post" target="_top">
    <h3>Za prave igrače, prave uplate</h3>
    <dl>
        <input type="hidden" name="cmd" value="_s-xclick">
        <input type="hidden" name="hosted_button_id" value="EM5PK9F6W3TVJ">
        <table>
        <tr><td><input type="hidden" name="on0" value="Koliko želite kredita?">Koliko želite kredita?</td></tr><tr><td><select name="os0">
            <option value="100 kredita">150 kredita €10.00 EUR</option>
            <option value="1500 kredita">2000 kredita €100.00 EUR</option>
            <option value="20000 kredita">25000 kredita €1,000.00 EUR</option>
        </select> </td></tr>
        </table>
        <input type="hidden" name="currency_code" value="EUR">
        <dt class="full" id="izvrsi_uplatu">
            <input type="image" src="https://www.paypalobjects.com/en_US/i/btn/btn_buynowCC_LG.gif" border="0" name="submit" alt="PayPal - The safer, easier way to pay online!">
            <img alt="" border="0" src="https://www.paypalobjects.com/en_US/i/scr/pixel.gif" width="1" height="1">
        </dt>
    </dl>
</form>

<!--
Uplati na račun:
<form action="https://www.paypal.com/cgi-bin/webscr" method="post" target="_top">
<input type="hidden" name="cmd" value="_s-xclick">
<input type="hidden" name="hosted_button_id" value="EM5PK9F6W3TVJ">
<table>
<tr><td><input type="hidden" name="on0" value="Koliko želite kredita?">Koliko želite kredita?</td></tr><tr><td><select name="os0">
	<option value="100 kredita">150 kredita €10.00 EUR</option>
	<option value="1500 kredita">2000 kredita €100.00 EUR</option>
	<option value="20000 kredita">25000 kredita €1,000.00 EUR</option>
</select> </td></tr>
</table>
<input type="hidden" name="currency_code" value="EUR">
<input type="image" src="https://www.paypalobjects.com/en_US/i/btn/btn_buynowCC_LG.gif" border="0" name="submit" alt="PayPal - The safer, easier way to pay online!">
<img alt="" border="0" src="https://www.paypalobjects.com/en_US/i/scr/pixel.gif" width="1" height="1">
</form>
!>


<?php require_once __DIR__ . '/_footer.php'; ?>