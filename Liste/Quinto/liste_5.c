#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int info;
    struct node *next;
};
typedef struct node Lista;
typedef Lista *ListaPointer;

ListaPointer generaLista(size_t elementi);
int generaRandom(size_t offset, size_t max);
void stampaLista(ListaPointer top);
ListaPointer eliminaNoDealloca(ListaPointer top, int X);


int main()
{
    srand(time(NULL));
    printf("Quanti elementi vuoi inserire in lista? ");
    int num;
    fscanf(stdin, "%d", &num);
    ListaPointer lista = NULL;
    lista = generaLista(num);
    puts("\nLa lista è: ");
    stampaLista(lista);
    printf("\nQuanti elementi vuoi eliminare senza deallocare la lista? ");
    scanf("%d", &num);

    puts("\nLa nuova lista è: ");
    lista = eliminaNoDealloca(lista, num);
    stampaLista(lista);
}

int generaRandom(size_t offset, size_t max)
{
    return offset + rand() % max;
}

ListaPointer generaLista(size_t elementi)
{
    if(elementi == 0){
        return NULL;
    } 
    ListaPointer nuovo = malloc(sizeof(Lista));
    nuovo->info = generaRandom(1, 1000);
    nuovo->next = generaLista(--elementi);
    return nuovo;
}

void stampaLista(ListaPointer top) 
{
    if(!top){
        printf("\\\\");
        puts("");
        return;
    }

    printf("%d -> ", top->info);
    stampaLista(top = top->next);
}

ListaPointer eliminaNoDealloca(ListaPointer top, int X)
{
    if(X == 0){
        return top;
    }
    eliminaNoDealloca(top = top->next, --X);
}