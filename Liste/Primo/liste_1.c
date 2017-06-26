#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Struttura autoreferenziale per la lista
struct node {
    int info;
    struct node *next;
};

//Alias per il nodo e la lista
typedef struct node Lista;
typedef Lista *ListaPointer;

//Prototipi della funzione
void inserisciInLista (ListaPointer * top, int dato);
void stampaLista (ListaPointer top);
void dropLista (ListaPointer *top);
int generaRandom (size_t max, size_t offset);

int main () 
{
    ListaPointer lista = NULL;

    srand(time(NULL));
    
    for(size_t i = 0; i < 10; i++) {
        inserisciInLista(&lista, generaRandom(100, 1));
    }

    puts("La lista è: ");
    stampaLista(lista);

    dropLista(&lista);
}

void inserisciInLista (ListaPointer * top, int dato)
{
    ListaPointer nuovo = NULL;

    nuovo = malloc(sizeof(Lista));


    if(!nuovo) {
        puts("Non è possibile allocare nuova memoria!");
        return;
    } 

    nuovo->info = dato;

    ListaPointer attuale = *top;
    ListaPointer precedente = NULL;

    while(attuale && dato > attuale->info) {
        precedente = attuale;
        attuale = attuale->next;
    }
    
    if(!precedente) {
        nuovo->next = *top;
        *top = nuovo;
    } else {
        nuovo->next = attuale;
        precedente->next = nuovo;
    }
}

void stampaLista (ListaPointer top) 
{
    if(!top) {
        printf("//");
        puts("");
        return;
    }

    printf("%d -> ", top->info);
    top = top->next;
    stampaLista(top);
}

void dropLista (ListaPointer *top) 
{
    if(!*top) {
        return;
    }
    ListaPointer temp = NULL;
    temp = *top;
    *top = (*top)->next;
    dropLista(&*top);
    free(temp);
}

int generaRandom (size_t max, size_t offset)
{
    return offset + rand() % max;
}