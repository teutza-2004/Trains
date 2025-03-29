/*SINTEA Teodora - 314CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main () {
    freopen("tema1.in", "r", stdin);
    freopen("tema1.out", "w", stdout);

    TTren locomotiva = NULL, mecanic = NULL;
    TCoada start = NULL, fin = NULL;
    InitT(&locomotiva, &mecanic);

    int n = 0; // nr de comenzi citite
    char *cmd = (char*)calloc(100, sizeof(char)); // vector care citeste comanda
    if (!cmd) {
        return 0;
    }
    char *s = (char*)calloc(100, sizeof(char)); // vector care citeste parametru de tip sir de caractere al comenzii
    if (!s) {
        return 0;
    }
    char c; // variabila care citeste parametrul de tip caracter al comenzii

    scanf("%d", &n);
    int i = 0;
    for (i = 0; i < n; i++) {
        scanf("%s ", cmd);
        if (strcmp(cmd, "WRITE") == 0 ||
            strcmp(cmd, "INSERT_LEFT") == 0 ||
            strcmp(cmd, "INSERT_RIGHT") == 0) {
            scanf("%c", &c);
            PUSHC(&start, &fin, cmd, " ", c);
        } else if (strcmp(cmd, "SEARCH") == 0 ||
                   strcmp(cmd, "SEARCH_LEFT") == 0 ||
                   strcmp(cmd, "SEARCH_RIGHT") == 0) {
            scanf("%s", s);
            PUSHC(&start, &fin, cmd, s, '\0');
        } else if (strcmp(cmd, "SHOW_CURRENT") == 0) {
            SHOW_CURRENT(mecanic);
        } else if (strcmp(cmd, "SHOW") == 0) {
            SHOW(locomotiva, mecanic);
        } else if (strcmp(cmd, "SWITCH") == 0) {
            SWITCH(start, fin);
        } else if (strcmp(cmd, "EXECUTE") == 0) {
            FUNCTION_CALL(&locomotiva, &mecanic, &start, &fin);
        } else {
            PUSHC(&start, &fin, cmd, " ", '\0');
        }
    }

    free(cmd);
    free(s);
    TTren aux = locomotiva->dr;
    for (aux = locomotiva->dr; aux != locomotiva;) {
        TTren del = aux;
        aux = aux->dr;
        free(del);
    }
    free(locomotiva);
    while (start) {
        POPC(&start, &fin);
    }
    return 0;
}