Polazno stablo je sljedeće:

![max-hrpa](img/graph-enum.txt.png)

odnosno


![lin-hrpa](img/graph-line.txt.png)

**Prvi korak**. Zamijenjujemo `z` i `l`.

![max-hrpa](img/graph-pop-enum-1.txt.png)

![lin-hrpa](img/graph-pop-line-1.txt.png)

**Drugi korak**.  Zamijenjujemo `l`i `r`.


![max-hrpa](img/graph-pop-enum-2.txt.png)

![lin-hrpa](img/graph-pop-line-2.txt.png)


**Treći korak**.  Zamijenjujemo `l`i `m`.


![max-hrpa](img/graph-pop-enum-3.txt.png)

![lin-hrpa](img/graph-pop-line-3.txt.png)


**Završno stablo**.

![max-hrpa](img/graph-pop-enum-4.txt.png)

![lin-hrpa](img/graph-pop-line-4.txt.png)

Operacija se nastavlja sve dok ne naiđemo na element koji je u dobrom
položaju (veći ili jednak od svoje djece) ili dok ne dođemo do elemeta
lista.
