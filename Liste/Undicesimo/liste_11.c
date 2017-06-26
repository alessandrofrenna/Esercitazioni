#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

struct nodo {
    int info;
    struct nodo *next;
};

typedef struct nodo Lista;
typedef Lista *ListaPointer;

void inserisciNodoTesta (ListaPointer *top, int elemento);
void reverseList (ListaPointer *top);
void printLista(const ListaPointer top);
ListaPointer generaLista(int numero);
int randomNum(size_t offset, size_t max); 

int main ()
{
    srand(time(NULL));
    ListaPointer lista = NULL;
    printf("Quanti elementi deve avere la lista? ");
    int num;
    scanf("%d", &num);
    getchar();
    system("clear");
    puts("Lista generata: ");
    lista = generaLista(num);
    printLista(lista);

    puts("\nFaccio il reverse della lista: ");
    reverseList(&lista);
    puts("\nNuova lista capovolta: ");
    printLista(lista);
}

void inserisciNodoTesta (ListaPointer *top, int elemento)
{
    ListaPointer nuovo = NULL;
    nuovo = malloc(sizeof(Lista));
    if(!nuovo){
        return;
    }
    nuovo->info = elemento;
    nuovo->next = *top;
    *top = nuovo;
}

void reverseList (ListaPointer *top)
{
    ListaPointer tempHead = *top;
    ListaPointer prec = NULL, current = NULL;
    if(!*top){
        puts("Non posso fare il reverse, lista vuota!");
        return;
    }

    while(tempHead){
        current = tempHead;
        tempHead = tempHead->next;
        current->next = prec;
        prec = current;
    }
    *top = prec;
}

void printLista(const ListaPointer top)
{
    if(!top){
        printf("//\n\n");
        return;
    }

    printf("%d -> ", top->info);
    printLista(top->next);
}

ListaPointer generaLista(int numero)
{
    ListaPointer lista = NULL;
    for(size_t i = 0; i < numero; i++){
        inserisciNodoTesta(&lista, randomNum(1, MAX));
    }    
    return lista;
}

int randomNum(size_t offset, size_t max) 
{
    return offset + rand() % max;
}