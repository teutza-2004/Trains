/*SINTEA Teodora - 314CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

TTren AllocCellT () {
    TTren aux = (TTren)calloc(1, sizeof(TCelulaT));
    if (!aux) {
        return NULL;
    }
    aux->dr = aux->st = aux;
    aux->info = '#';
    return aux;
}

TCoada AllocCellC (char *cmd, char *s, char c) {
    TCoada aux = (TCoada)calloc(1, sizeof(TCelulaC));
    if (!aux) {
        return NULL;
    }
    aux->dr = aux->st = NULL;

    aux->cmd = (char*)calloc(100, sizeof(char));
    if (!aux->cmd) {
        return NULL;
    }
    strcpy(aux->cmd, cmd);

    aux->s = (char*)calloc(100, sizeof(char));
    if (!aux->s) {
        return NULL;
    }
    strcpy(aux->s, s);

    aux->c = c;
    aux->vf = 0;
    return aux;
}

void InitT (TTren *locomotiva, TTren *mecanic) {
    TTren aux = AllocCellT();
    aux->info = '\0';
    *locomotiva = aux;

    aux = AllocCellT();
    aux->dr = *locomotiva;
    aux->st = *locomotiva;
    (*locomotiva)->dr = aux;
    (*locomotiva)->st = aux;
    *mecanic = (*locomotiva)->dr;
}

void INSERT_RIGHT (TTren *locomotiva, TTren *mecanic, char c) {
    TTren aux = AllocCellT();
    if (!aux) {
        return;
    }
    aux->info = c;
    aux->dr = (*mecanic)->dr;
    (*mecanic)->dr->st = aux;
    aux->st = *mecanic;
    (*mecanic)->dr = aux;
    *mecanic = aux; // mutare mecanic in celula creata
}

void INSERT_LEFT (TTren *locomotiva, TTren *mecanic, char c) {
    if ((*mecanic)->st == *locomotiva) { // verific daca este primul vagon
        printf("ERROR\n");
        return;
    }

    TTren aux = AllocCellT();
    if (!aux) {
        return;
    }
    aux->info = c;
    aux->st = (*mecanic)->st;
    (*mecanic)->st->dr = aux;
    (*mecanic)->st = aux;
    aux->dr = *mecanic;
    *mecanic = aux; // mutare mecanic in celula creata
}

void MOVE_LEFT (TTren locomotiva, TTren *mecanic) {
    if ((*mecanic)->st == locomotiva) { // sar peste santinela daca ma aflu in ultimul vagon
        *mecanic = locomotiva->st;
        return;
    }
    *mecanic = (*mecanic)->st;
}

void MOVE_RIGHT (TTren locomotiva, TTren *mecanic) {
    if ((*mecanic)->dr == locomotiva) {
        INSERT_RIGHT(&locomotiva, mecanic, '#');
        return;
    }
    *mecanic = (*mecanic)->dr;
}

void WRITE (TTren *mecanic, char c) {
    (*mecanic)->info = c;
}

void CLEAR_CELL (TTren locomotiva, TTren *mecanic) {
    (*mecanic)->st->dr = (*mecanic)->dr;
    (*mecanic)->dr->st = (*mecanic)->st;
    TTren aux = *mecanic;
    MOVE_LEFT(locomotiva, mecanic);
    free(aux);
}

void CLEAR_ALL (TTren *locomotiva, TTren *mecanic) {
    if ((*locomotiva)->dr == *mecanic && (*locomotiva)->st == *mecanic) {
        WRITE(mecanic, '#');
        return;
    }
    if ((*locomotiva)->dr == *mecanic) {
        TTren aux = (*mecanic)->dr;
        CLEAR_CELL(*locomotiva, mecanic);
        CLEAR_ALL(locomotiva, &aux);
        return;
    }
    TTren aux = (*mecanic)->st;
    CLEAR_CELL(*locomotiva, mecanic);
    CLEAR_ALL(locomotiva, &aux);
}

void SEARCH (TTren locomotiva, TTren *mecanic, char *s) {
    char *src = (char*)calloc(100, sizeof(char)); // un vector in care stochez elem din tren
    if (!src) {
        exit(0);
    }

    int i = 0; // indicele celulei curente din parcurgerea trenului
    TTren aux = *mecanic; // pointerul cu care parcurg trenul
    *src = aux->info;
    i++;
    aux = aux->dr;
    while (aux != *mecanic) {
        if (aux != locomotiva) { // pentru a putea sari peste santinela
            *(src+i) = aux->info;
            i++;
        }
        aux = aux->dr;
    }

    if (strstr(src, s) == NULL) { // s nu se afla in tren
        printf("ERROR\n");
        free(src);
        return;
    }

    i = strstr(src, s) - src; // cu cate pozitii se deplaseaza mecanicul in tren
    while (i) {
        *mecanic = (*mecanic)->dr;
        if (*mecanic != locomotiva) {
            i--;
        }
    }
    free(src);
}

void SEARCH_LEFT (TTren locomotiva, TTren *mecanic, char *s) {
    char *src = (char*)calloc(100, sizeof(char));
    if (!src) {
        exit(0);
    }
    int i = 0;
    TTren aux = *mecanic;
    *(src+i) = aux->info;
    i++;
    aux = aux->st;
    while (aux != locomotiva) {
        *(src+i) = aux->info;
        i++;
        aux = aux->st;
    }

    if (strstr(src, s) == NULL) {
        printf("ERROR\n");
        free(src);
        return;
    }

    i = strstr(src, s) - src + strlen(s) - 1; // cu cate pozitii se deplaseaza mecanicul in tren
    while (i) {
        if (*mecanic != locomotiva) {
            i--;
        }
        *mecanic = (*mecanic)->st;
    }
    free(src);
}

void SEARCH_RIGHT (TTren locomotiva, TTren *mecanic, char *s) {
    char *src = (char*)calloc(100, sizeof(char));
    if (!src) {
        exit(0);
    }
    int i = 0;
    TTren aux = *mecanic;
    *src = aux->info;
    i++;
    aux = aux->dr;
    while (aux != locomotiva) {
        *(src+i) = aux->info;
        i++;
        aux = aux->dr;
    }

    if (strstr(src, s) == NULL) {
        printf("ERROR\n");
        free(src);
        return;
    }

    i = strstr(src, s) - src + strlen(s) - 1; // cu cate pozitii se deplaseaza mecanicul in tren
    while (i) {
        if (*mecanic != locomotiva) {
            i--;
        }
        *mecanic = (*mecanic)->dr;
    }
    free(src);
}

void SHOW_CURRENT (TTren mecanic) {
    printf("%c\n", mecanic->info);
}

void SHOW (TTren locomotiva, TTren mecanic) {
    TTren aux = locomotiva->dr;
    for (aux = locomotiva->dr; aux != locomotiva; aux = aux->dr) {
        if (aux == mecanic) {
            printf("|%c|", aux->info);
            continue;
        }
        printf("%c", aux->info);
    }
    printf("\n");
}

void PUSHC (TCoada *start, TCoada *fin, char *cmd, char *s, char c) {
    TCoada aux = AllocCellC(cmd, s, c);
    if (!aux) {
        return;
    }
    if (!(*start)) {
        aux->vf = 1;
        *start = *fin = aux;
        return;
    }
    if ((*start)->vf) {
        aux->st = *fin;
        (*fin)->dr = aux;
        *fin = (*fin)->dr;
        return;
    }
    aux->dr = *start;
    (*start)->st = aux;
    *start = aux;
}

char *EXECUTE (TCoada *start, TCoada *fin) {
    if ((*start)->vf) {
        return (*start)->cmd;
    }
    return (*fin)->cmd;
}

void POPC (TCoada *start, TCoada *fin) {
    if (*start == *fin) { // o singura comanda in coada
        TCoada aux = *start;
        free((*start)->cmd);
        free((*start)->s);
        *start = *fin = NULL;
        free(aux);
        return;
    }
    if ((*start)->vf) {
        free((*start)->cmd);
        free((*start)->s);
        TCoada aux = *start;
        *start = (*start)->dr;
        (*start)->vf = 1; // mut varful
        free(aux);
        return;
    }
    free((*fin)->cmd);
    free((*fin)->s);
    TCoada aux = *fin;
    *fin = (*fin)->st;
    (*fin)->vf = 1; // mut varful
    free(aux);
}

void SWITCH (TCoada start, TCoada fin) {
    int aux = start->vf; 
    start->vf = fin->vf;
    fin->vf = aux;
}

void FUNCTION_CALL (TTren *locomotiva, TTren *mecanic, TCoada *start, TCoada *fin) {
    char *cmd = EXECUTE(start, fin);
    if (strcmp(cmd, "MOVE_LEFT") == 0) {
        MOVE_LEFT(*locomotiva, mecanic);
    } else if (strcmp(cmd, "MOVE_RIGHT") == 0){
        MOVE_RIGHT(*locomotiva, mecanic);
    } else if (strcmp(cmd, "WRITE") == 0) {
        if ((*start)->vf) {
            WRITE(mecanic, (*start)->c);
        } else {
            WRITE(mecanic, (*fin)->c);
        }
    } else if (strcmp(cmd, "CLEAR_CELL") == 0) {
        CLEAR_CELL(*locomotiva, mecanic);
    } else if (strcmp(cmd, "CLEAR_ALL") == 0) {
        CLEAR_ALL(locomotiva, mecanic);
        *mecanic = (*locomotiva)->dr;
    } else if (strcmp(cmd, "INSERT_LEFT") == 0) {
        if ((*start)->vf) {
            INSERT_LEFT(locomotiva, mecanic, (*start)->c);
        } else {
            INSERT_LEFT(locomotiva, mecanic, (*fin)->c);
        }
    } else if (strcmp(cmd, "INSERT_RIGHT") == 0) {
        if ((*start)->vf) {
            INSERT_RIGHT(locomotiva, mecanic, (*start)->c);
        } else {
            INSERT_RIGHT(locomotiva, mecanic, (*fin)->c);
        }
    } else if (strcmp(cmd, "SEARCH") == 0) {
        if ((*start)->vf) {
            SEARCH(*locomotiva, mecanic, (*start)->s);
        } else {
            SEARCH(*locomotiva, mecanic, (*fin)->s);
        }
    } else if (strcmp(cmd, "SEARCH_LEFT") == 0) {
        if ((*start)->vf) {
            SEARCH_LEFT(*locomotiva, mecanic, (*start)->s);
        } else {
            SEARCH_LEFT(*locomotiva, mecanic, (*fin)->s);
        }
    } else if (strcmp(cmd, "SEARCH_RIGHT") == 0) {
        if ((*start)->vf) {
            SEARCH_RIGHT(*locomotiva, mecanic, (*start)->s);
        } else {
            SEARCH_RIGHT(*locomotiva, mecanic, (*fin)->s);
        }
    }
    
    POPC(start, fin);
}
