**Konstrukcija hrpe iz ulaznog niza**.  Neka je dan sljedeći ulazni niz:


![lin-hrpa](img/constr-line-1.txt.png)

odnosno, zapisano kao potpuno binarno stablo:


![max-hrpa](img/constr-enum-1.txt.png)


Ukupan broj elemenata je `n=10`. Zadnji element ima roditelja na mjesto
`(9-1)/2 = 4`. Procedura će sada ići po `l=4,3,2,1,0`. Za `l=4` imamo:  


![max-hrpa](img/constr-enum-2.txt.png)

![lin-hrpa](img/constr-line-2.txt.png)

Za `l=3`:


![max-hrpa](img/constr-enum-3.txt.png)

![lin-hrpa](img/constr-line-3.txt.png)

Za `l=2`:

![max-hrpa](img/constr-enum-4.txt.png)

![lin-hrpa](img/constr-line-4.txt.png)



Za `l=1`:

![max-hrpa](img/constr-enum-5.txt.png)

![lin-hrpa](img/constr-line-5.txt.png)




Za `l=0`:

![max-hrpa](img/constr-enum-6.txt.png)

![lin-hrpa](img/constr-line-6.txt.png)
