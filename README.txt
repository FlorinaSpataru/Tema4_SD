// Spataru Florina Gabriela 313CA <florina.spataru@gmail.com> Tema4 SD //

	In implementarea temei am folosit o clasa pentru memorarea proceselor (index,
timp de executie si o variabila booleana care marcheaza un proces ca fiind
executat sau nu) si o clasa pentru procesoare (index, indexul procesului ce se
executa pe acel procesor (0 daca nu se executa nimic), timpul de executie al
procesului aflat pe procesor la acel timp (0 daca nu este nici unul) si o
variabila ce marcheaza procesorul ca fiind idle sau nu).

	Aditional, am creat o functie ce verifica daca un proces poate fi executat,
adica nici un altul nu depinde de el. Practic se verifica daca, pentru procesul
p, in matricea de adiacenta coloana p contine numai zerouri.

	In main, dupa citirea datelor din fisierul .in si cel .txt, se construieste
matricea de adiacenta a grafului. De asemenea, se contruiesc vectorii de procese
si procesoare (task[], respectiv proc[]).

	Atata timp cat nodul curent este diferit de ultimul nod din graf:
* se numara cate procese pot fi executate;
* se numara cate procesoare sunt disponibile (idle);
* incepand cu procesul 1 si procesorul 1 se face cautarea;
* cand se gaseste o pereche <proces procesor> ce poate fi executata, procesorul
va fi marcat ca !idle si procesul ca fiind executat; de asemenea se atribuie
procesorului un timp de executie;
* dupa ce au fost epuizate procesele si procesoarele disponibile ne vom ocupa
de timpii de executie si trecerea la urmatorul moment de timp;
* pentru fiecare proces !idle se decrementeaza timpul de executie; daca acesta
ajunge la 0, procesul va fi marcat la idle;
* se incrementeaza timpul total

	In final, se elibeareaza memoria.

	