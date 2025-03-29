punctaj: 120/120

makefile:
- eticheta build (cea default) compileaza codul si creaza executabilul tema1
- eticheta run ruleaza executabilul tema1
- eticheta clean sterge executabilul tema1

functii.h:
- declar structura pentru tren care are un camp de informatie tip char si doua de tip pointer al structurii care indica spre celulele vecine ale celulei curente
- in structura pentru coada sunt trei parametrii de tip char: unul retine numele comenzii, altul parametrul de tip sir de caractere aferent comenzii (default " "), iar variabila simpla retine parametrul tip caracter al comenzii (default '\0'); structura mai are un parametru tip int care este egal cu 1 daca celula respectiva reprezinta varful cozii si 0 in caz contrar; de asemenea exista doi pointeri spre celulele vecine ale fiecarui element din coada
- restul liniilor reprezinta antetele functiilor implementate in functii.c

main.c:
- modific standard input si output astfel incat citirea, respectiv afisarea sa se faca in fisierele cerute
- declar pointer-ul pentru tren si unul care va tine minte adresa la celula din tren care contine mecanicul si le initializez; mai declar si pointerii pentru inceputul si sfarsitul cozii
- am declarat un vector care retine comanda curenta citia, un sir de caractere si o variabila tip char care retin (atunci cand este cazul) parametrii comenzilor curente
- citesc cele n comenzi, iar pe cele de tip update si search le introduc in coada impreuna cu parametrii acestora (acolo unde exista); ceelalte comenzi sunt executate direct la citire
- dupa ce se citesc toate comenziile eliberez memoria ramasa in tren, impreuna cu vectorii utilizati la citirea comenzilor

functii.c:
- AllocCellT: aloca o noua celula a trenului
    aloca o celula a trenului, creaza legaturile defult spre celula nou creata, initializeaza informatia cu "#" si returneaza celula
- AllocCellC: aloca o noua celula a cozii
    aloc o celula a cozii si creez legaturile spre NULL; aloc spatiul pt comanda din cadrul celulei si copiez "valoaera" comenzii in acel spatiu (analog pt parametrul de tip sir de caractere); copiez caracterul parametru si setez ca default varful cozii ca fiind 0; in final returnez celula nou creata
- InitT: initializeaza trenul
    aloc o celula tip tren careia ii pun ca informatie caracterul '\0' (santinela); aloc inca o celula care va reprezenta vagonul default al trenului in care se va afla mecanicul initial si stabilesc legaturile intre cele doua celule
- INSERT_RIGHT: insereaza o celula la dreapta curentei
    aloc o celula tip tren in care pun ca informatie caracterul dat ca parametru, "inserez" vagonul nou la dreapta celui curent si stabilesc legaturile cu celulele vecine dupa care modific adresa mecanicului ca fiind adresa celulei nou crate
- INSERT_LEFT: insereaza un vagon la stanga celui curent
    verific daca ma aflu in primul vagon al trenului si in caz afirmativ afisez mesajul de eroare si ies fin functie, in caz contrar sunt executate operatii similare cu cele de la functia INSERT_RIGHT
- MOVE_LEFT: muta mecanicul cu o pozitie la stanga
    in cazul in care legatura spre vagonul anterior duce spre santinela adresa mecanicului va deveni adresa ultimului vagon (stanga santinelei), in caz contrar se muta spre vagonul imediat din stanga
- MOVE_RIGHT: muta mecanicul cu o pozitie la dreapta
    in cazul in care mecanicul se afla in ultimul vagon (adresa urmatorului este santinela), se apeleaza functia INSERT_RIGHT si se adauga un nou vagon la tren, altfel mecanicul se muta in vagonul imediat din dreapta
- WRITE: inscriptioneaza vagonul cu alta valoare
    schimba informatia din vagonul curent cu valoarea data ca parametru
- CLEAR_CELL: elimina celula curenta
    se restabilesc legaturile intre vecinii vagonului care trebuie eliminat; se creaza o copie a adresei curente a mecanicului si se apeleaza MOVE_LEFT pentru a muta mecanicul la stanga; in final se elibereaza memoria celulei eliminate (prin intermediul copiei)
- CLEAR_ALL: se elimina toate vagoanele (se aduce trenul in starea initiala)
    in cazul in care in tren mai ramane numai un vagon, se schimba inscriptia acestuia cu '#'; cat timp mai exista celule in stanga mecanicului acestea sunt eliminate prin apelul recursiv, cand ajunge mecanicul sa fie in celula imediat din dreapta a santinelei, se elimina recursiv toate celulele ramase in drepta sa
- SEARCH: se cauta un sir de caractere in tren
    aloc un vector in care voi stoca elementele din tren; parcurg trenul spre dreapta incepand cu pozitia mecanicului tinand cont ca atunci cand ajung in dreptul santinelei nu se retine informatia din aceasta; in cazul in care sirul cautat nu se afla in tren afisez mesajul de eroare si dezaloc sirul cu caracterele din tren; in caz contrar calculez cu cate pozitii trebuie mutat mecanicul relativ la pozitia sa curenta si il deplasez tinand cont de santinela; in final dezaloc sirul de caractere din tren
- SEARCH_LEFT: se cauta un sir de caractere in partea de tren la st mecanicului
    similar cu functia SEARCH, construiesc vectorul cu elemente de la stanga mecanicului pana la santinela + cautarea parametrului in sir si mutarea mecanicului la stanga
- SEARCH_RIGHT: se cauta un sir de caractere in partea de tren din dreapta mecanicului
    ca la SEARCH_LEFT doar ca in dreapta mecanicului pana la santinela
- SHOW_CURRENT: afis caracterul vegonului in care e mecanicul
    afisez informatia din celula mecanicului
- SHOW: afis tot trenul
    parcurg celulele trenului incepand cu primul vagon si afisez informatiile din acestea, in cazul in care se ajunge la pozitia mecanicului se mai afiseaza barele verticale care marcheaza vagonul curent al mecanicului
- PUSHC: adauga o comanda la coada
    se aloca o celula tip coada; in cazul in care coada este goala atat inceputul cat si sfarsitul vor pointa spre celula nou alocata, iar valoarea varfului se va schimba la 1; in cazul in care varful este la inceputul cozii se adauga o celula la sfarsitul acesteia, altfel se adauga celula la inceputul structurii
- EXECUTE: returneaza numele comenzii care urmeaza a fi extrasa din coada
    daca varful este la inceput se returneaza comanda de la start, altfel se returneaza comanda de la final
- POPC: extrage comanda din coada
    in cazul in care inceputul este egal cu sfarsitul (este o singura comanda in coada) se elibereaza memoria alocata comenzii si parametrului tip sir de caractere si se reinitializeaza pointerii de inceput si final cu NULL dupa care se dezaloca celula; in cazul in care sunt mai multe elemente, daca varful este la inceput sau sfarsit, acesta se va muta la celula din dreapta, respectiv stanga
- SWITCH: schimba ordinea comenzilor
    schimb varful cozii
- FUNCTION_CALL: apeleaza functiile din coada cand se intalneste comanda EXECUTE la citire
    aflu comanda care trebuie extrasa din coada si apelez functia aferenta acesteia; la final extrag elemetul curent din coada