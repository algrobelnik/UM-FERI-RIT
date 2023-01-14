S pomočjo programskega vmesnika MPI in uporabe niti paralelizirajte izvajanje algoritma za ustvarjanje (rudarjenje) blokov, ki ste ga že implementirali v okviru predmeta MUR. Program naj omogoča rudarjenje blokov na več vozliščih in na vsakem vozlišču naj se izvaja v več nitih. Program na vsakem vozlišču zažene toliko niti kot je optimalna za arhitekturo vozlišča.

Oddajte kratko predstavitev o implementirani rešitvi. Ta naj vsebuje kratko predstavitev rešitve in grafe pohitritev računanja glede na število vozlišč (procesov) in število niti.

**Podrobnejša navodila**

Izdelajte storitev v poljubnem programskem jeziku, ki bo omogočala delo z verigo blokov. Ta storitev naj omogoča:
* Validacijo blokov in verige
* Ustvarjanje novih blokov.

Vsak blok naj vsebuje naslednje elemente:
* indeks
* podatek
* časovna značka
* zgoščena vrednost prejšnjega bloka
* težavnost
* žeton
* zgoščena vrednost bloka
Ustvarjanje novih blokov implementirajte z algoritmom konsenza "proof-of-work", ki vključuje spremenljivo težavnost ustvarjanja novih blokov oz. validacijo časovnih značk in kumulativno težavnost. Prvi blok v verigi mora imeti zgoščene vrednosti prejšnjega bloka nastavljeno na vrednost 0. Ko se novi bloki dodajajo v verigo,  je potrebno preveriti njihovo integriteto. Izpolnjeni morajo biti naslednji pogoji:

Indeks trenutnega bloka je za 1 večji od prejšnjega bloka
Zgoščene vrednosti morajo biti ustrezne
Zgoščena vrednost prejšnjega bloka se ujema z njeno vrednostjo v trenutnem bloku
Shranjena zgoščena vrednost trenutnega bloka ustreza izračunom zgoščene vrednosti 
zgoščena vrednost = sha256( indeks + podatki + časovna značka + zgoščena vrednost prejšnjega bloka +težavnost + žeton)
Integriteto celotne verige preverimo tako, da preverimo integriteto vseh blokov v verigi. 

Če blok lahko validiramo, ga lahko dodamo v verigo blokov, saj mora izpolnjevati pogoje za integriteto. Te pogoje dosežemo s pomočjo rudarjenja, ki je časovno potraten in zato ga je potrebno paralelizirati v okviru te naloge. V tem postopku uporabimo vrednost težavnosti, ki določa število ničel, ki jih mora imeti zgoščena vrednost bloka na začetku, da bo blok veljaven. Da to dosežemo, moramo poiskati določeno vrednost žetona (angl. nonce), ki ga uporabljamo pri izračunu zgoščene vrednosti.

Algoritem za rudarjenje, ki ga je potrebno paralelizirati
žeton = 0
while(true){
    zgoščena vrednost = sha256( indeks + podatki + časovna značka + zgoščena vrednost prejšnjega bloka + težavnost + žeton
    if( zgoščena vrednost ima število začetnih ničel enako težavnosti ) 
        return new Block(indeks + podatki + časovna značka + zgoščena vrednost prejšnjega bloka + težavnost + žeton)
    else žeton++
}
Za določanje trenutne težavnosti določite časovni intervala ustvarjanja blokov in intervala popravka težavnosti. Časovni interval ustvarjanja
blokov pove v kakšnem času, se lahko najde nov blok. Za to vrednost uporabite npr. 10 sekund. Interval popravka težavnosti pove kako pogosto se bo težavnost prilagajala. Za vrednost uporabite število blokov (npr. 10 blokov). Težavnost povečamo za 1, če ustvarjanje traja vsaj 2-krat manj časa kot je pričakovano in pomanjšamo za 1, če ustvarjanje traja vsaj 2-krat dalj časa kot je pričakovano.

prilagoditvani blok = Veriga blokov[dolžina verige - interval popravka]
pričakovani čas = čas ustvarjanja bloka * interval popravka
dejanski čas = časovna značka zadnjega bloka - časovna značka prilagoditbenega bloka

if ( dejanski čas < (pričakovani čas / 2) ) return težavnost prilagoditvenega bloka + 1 
else if ( dejanski čas > (pričakovani čas * 2) ) return težavnost prilagoditvenega bloka - 1
else return težavnost prilagoditvenega bloka

Ker je čas ustvarjanja blokov pomembna informacija, je potrebno bloke validirati glede na časovne značke s pomočjo naslednjih pravil:
* blok je ustrezen, če je njegova časovna značka največ 1 minuto večja od našega trenutnega časa
* blok v verigi je ustrezen če je njegova časovna značka največ 1 minuto manjša od časovne značke prejšnjega bloka

Ob konfliktih zaradi sočasnosti izberemo verigo z največjo kumulativno težavnostjo. To je veriga, kjer je bilo potrebno porabiti največ sistemskih sredstev oz. časa. Izračun kumulativne težavnosti verige je vsota težavnosti za vsak blok. Težavnost bloka pa predstavlja 2^(težavnost).

Ocenjevanje:
+ Struktura bloka, povezovanje blokov v verigo (1 t)
+ Validacija zgoščenih vrednosti, blokov in verige (1 t)
+ Ustvarjanje novih blokov (rudarjenje) s pomočjo paralelizacije na enem računalniku (4 t)
+ Ustvarjanje novih blokov (rudarjenje) s pomočjo paralelizacije v porazdeljenem okolju in na nivoju lokalnega računalnika (4 t)
+ Določanje trenutne težavnosti (2 t)
+ Validacija časovnih značk (2 t)
+ Validacija verige s kumulativno težavnostjo (2 t)
+ Izdelava spletne storitve (2 t)
+ Izdelava predstavitve (2 t)

**Dopis naloge**
+ paraleliziraj samo del, kjer se računa rudarjenje blokov
* uporabljamo MPI in vse zaženemo na enem računalniku, ki nam omogoča "fake" več rač.
* poljuben programski jezik
* uporabi /home/aleks/Desktop/UM-FERI-RIT/3rd_semester/MUR/vaja05
* razdeli na podintervale, kjer podobno kot pri prejšnih nalogah, kjer si razdelil polje na več delov in si pošiljal noter indekse 
* 4 naj bo najmanjša vrednost težavnosti
* 
