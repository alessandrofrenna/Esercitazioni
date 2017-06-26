#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct nodo {
    int info;
    struct nodo *next;
};

typedef struct nodo Lista;
typedef Lista *ListaPointer;

//Funzioni per gestire la lista
int generaRandom (size_t offset, size_t massimo);
void inserisciNodo (ListaPointer *top, int elemento);
ListaPointer minimoPariRicorsivo (ListaPointer node, ListaPointer minimo);
ListaPointer minimoPariIterativo (ListaPointer top);
void stampaLista (ListaPointer top);
void dropLista (ListaPointer *top);


int main ()
{   
    ListaPointer lista = NULL;
    srand(time(NULL));
    int num = generaRandom(1, 15);
    for (size_t i = 0; i < num; i++) {
        inserisciNodo(&lista, generaRandom(1, 1000));
    }

    puts("La lista è:");
    stampaLista(lista);

    ListaPointer minimo = minimoPariRicorsivo(lista, NULL);
    if(minimo) {
        printf("\nIl primo numero pari minimo della lista è: %d\n\n", minimo->info);
    } else {
        puts("\nNumero pari minimo non trovato!");
    }
    dropLista(&lista);
}

int generaRandom (size_t offset, size_t massimo)
{
    return offset + rand() % massimo;
}

void inserisciNodo (ListaPointer *top, int elemento)
{
    ListaPointer nuovo = NULL;
    nuovo = malloc(sizeof(Lista));

    if(!nuovo){
        return;
    }

    nuovo->info = elemento;

    nuovo->next = (*top);
    (*top) = nuovo;
}

ListaPointer minimoPariRicorsivo (ListaPointer node, ListaPointer minimo)
{
    if(node == NULL){
        return minimo;
    }

    if(node->info%2 == 0 && ( (minimo == NULL) || (node->info < minimo->info))) {
        minimo = node;
    }
    
    minimoPariRicorsivo(node = node->next, minimo);
}

ListaPointer minimoPariIterativo (ListaPointer top)
{   
    ListaPointer minimo = top;

    while(top = top->next){

        if(top->info%2 == 0 && top->info < minimo->info){
            minimo = top;
        }
    }

    return minimo;
}

void stampaLista (ListaPointer top)
{
    if(!top) {
        printf("//\n");
        return;
    }

    printf("%d -> ", top->info);
    stampaLista(top = top->next);
}

void dropLista (ListaPointer *top)
{
    if(!*top){
        return;
    }

    ListaPointer temp = NULL;
    temp = *top;
    (*top) = (*top)->next;
    dropLista(&*top);
    free(temp);
}