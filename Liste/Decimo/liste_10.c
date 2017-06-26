#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int info;
    struct node *next;
};

typedef struct node Lista;
typedef Lista *ListaPointer;

void inserisciNodo (ListaPointer *top, int elemento);
void printLista (ListaPointer top);
void generaVettore(int *vettore, int dim);
int randomNum(size_t offset, size_t max);
void printArray(int *vettore, int dim);
ListaPointer toro (int *vettore, int dim);

int main ()
{
    ListaPointer lista = NULL;
    srand(time(NULL));
    
    int num;
    printf("Quanti elementi per il vettore? ");
    scanf("%d", &num);
    int vettore[num];
    generaVettore(vettore, num);
    printArray(vettore, num);

    puts("La lista dei multipli di 11 è: ");
    printLista(toro(vettore, num));
}

void inserisciNodo (ListaPointer *end, int elemento) 
{
    ListaPointer current = NULL;
    ListaPointer nuovo = NULL;
    nuovo = malloc(sizeof(Lista));

    if(!nuovo){
        return;
    }

    nuovo->info = elemento;

    if(!*end){
        nuovo->next = nuovo;
        (*end) = nuovo;
    } else {
        nuovo->next = (*end)->next;
        (*end)->next = nuovo;
        *end = nuovo;
    }
}

void printLista (ListaPointer end)
{
    if(!end) {
        puts("Lista vuota!");
        return;
    }
    ListaPointer testa = end->next;
    printf("%d -> ", testa->info);
    testa = testa->next;    
    while(testa != end->next) {
        printf("%d -> ", testa->info);
        testa = testa->next;
    }
    printf("//\n");
    puts("");
}

void generaVettore(int *vettore, int dim)
{
    for (size_t i = 0; i < dim; i++){
        vettore[i] = randomNum(-100, 100);
    }
}

int randomNum(size_t offset, size_t max)
{
    return offset + rand() % max;
}

void printArray(int *vettore, int dim)
{
    puts("\n");
    for(size_t i = 0; i < dim; i++) {
        printf("Array[%lu] = %d \n", i, vettore[i]);
    }
    puts("\n");
}

ListaPointer toro (int *vettore, int dim)
{
    ListaPointer lista = NULL;

    for(size_t i = 0; i < dim; i++){
        if(vettore[i] % 11 == 0 ){
            inserisciNodo(&lista, vettore[i]);
        }
    }

    return lista;
}