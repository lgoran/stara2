U polazno stablo prikazano ovdje

![max-hrpa](img/graph-enum.txt.png)

odnosno


![lin-hrpa](img/graph-line.txt.png)

ubacujemo element `q`.
**Prvi korak**. Novi element dolazi na zadnje mjesto:

![max-hrpa](img/graph-push-enum-1.txt.png)

![lin-hrpa](img/graph-push-line-1.txt.png)

**Drugi korak**.  Kako je `q` veći od `m` zamijenjujemo `q`i `m`.


![max-hrpa](img/graph-push-enum-2.txt.png)

![lin-hrpa](img/graph-push-line-2.txt.png)


**Treći korak**.  Kako je `q` veći i od `p` zamijenjujemo `q`i `p`.


![max-hrpa](img/graph-push-enum-3.txt.png)

![lin-hrpa](img/graph-push-line-3.txt.png)


**Završno stablo**. Sada je `q` manji od svojeg roditelja i time smo završili. 

![max-hrpa](img/graph-push-enum-4.txt.png)

![lin-hrpa](img/graph-push-line-4.txt.png)

Operacija se nastavlja sve dok ubačeni element nije dobro pozicioniran.
