/*SINTEA Teodora - 314CB*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Tren { // lista circ 2 inlant cu santinela
    char info;
    struct Tren *st, *dr;
}TCelulaT, *TTren;

typedef struct Coada { // lista 2 inlant cu 2 pointeri
    char *cmd, *s, c;
    int vf; // are val 1 daca este capatul de unde se extrag/insereaza comenzi, in rest este 0
    struct Coada *st, *dr;
}TCelulaC, *TCoada;

TTren AllocCellT ();
TCoada AllocCellC (char *cmd, char *s, char c);
void INSERT_RIGHT (TTren *locomotiva, TTren *mecanic, char c);
void INSERT_LEFT (TTren *locomotiva, TTren *mecanic, char c);
void MOVE_LEFT (TTren locomotiva, TTren *mecanic);
void MOVE_RIGHT (TTren locomotiva, TTren *mecanic);
void WRITE (TTren *mecanic, char c);
void CLEAR_CELL (TTren locomotiva, TTren *mecanic);
void CLEAR_ALL (TTren *locomotiva, TTren *mecanic);
void InitT (TTren *tren, TTren *mecanic);
void SEARCH (TTren locomotiva, TTren *mecanic, char *s);
void SEARCH_LEFT (TTren locomotiva, TTren *mecanic, char *s);
void SEARCH_RIGHT (TTren locomotiva, TTren *mecanic, char *s);
void SHOW_CURRENT (TTren mecanic);
void SHOW (TTren locomotiva, TTren mecanic);
void PUSHC (TCoada *start, TCoada *fin, char *cmd, char *s, char c);
char *EXECUTE (TCoada *start, TCoada *fin);
void POPC (TCoada *start, TCoada *fin);
void SWITCH (TCoada start, TCoada fin);
void FUNCTION_CALL (TTren *locomotiva, TTren *mecanic, TCoada *start, TCoada *fin);