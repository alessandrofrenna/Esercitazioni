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
ListaPointer ordinaLista(ListaPointer *top);
ListaPointer mergeLists(ListaPointer top1, ListaPointer top2);


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

    puts("\nLa nuova lista ordinata è: ");
    lista = ordinaLista(&lista);
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
    top = top->next,
    stampaLista(top);
}

ListaPointer ordinaLista(ListaPointer *top)
{
    ListaPointer temp = *top;
    ListaPointer half1 = temp;
    ListaPointer half2 = temp->next;
    

    if(!temp || !temp->next) {
        return NULL;
    }

    while(half2 && half2->next) {
        temp = temp->next;
        half2 = half2->next->next;
    }

    half2 = temp->next;
    temp->next = NULL;
    ordinaLista(&half1);
    ordinaLista(&half2);
    return *top = mergeLists(half1, half2);
}

ListaPointer mergeLists(ListaPointer top1, ListaPointer top2)
{
    Lista risultato;
    ListaPointer temp = &risultato;

    while(top1 && top2) {
        if(top1->info <= top2->info) {
            temp->next = top1;
            temp = top1;
            top1 = top1->next;
        } else {
            temp->next = top2;
            temp = top2;
            top2 = top2->next;
        }
    }

    temp->next = (top1 == NULL) ? top2 : top1;
    return risultato.next;
}