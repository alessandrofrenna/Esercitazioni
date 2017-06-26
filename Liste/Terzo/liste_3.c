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
ListaPointer primoPariRicorsivo (ListaPointer top);
ListaPointer primoPariIterativo (ListaPointer top);
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

    ListaPointer primo = primoPariIterativo(lista);
    if(primo) {
        printf("\nIl primo numero pari della lista è: %d\n\n", primo->info);
    } else {
        puts("\nNumero primo non trovato!");
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

ListaPointer primoPariRicorsivo (ListaPointer top)
{
    if(!top){
        return NULL;
    }

    if(top->info%2 == 0){
        return top;
    } 

    primoPariRicorsivo(top = top->next);
}

ListaPointer primoPariIterativo (ListaPointer top)
{
    while(top){
        if(top->info%2 == 0){
            return top;
        } else {
            top = top->next;
        }
    }

    return NULL;
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