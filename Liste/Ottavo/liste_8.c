#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int info;
    struct nodo *next;
};

typedef struct nodo Lista;
typedef Lista *ListaPointer;

void inserisciNodoTesta (ListaPointer *top, int elemento);
void printLista (const ListaPointer top);
void svuotaLista (ListaPointer *top);

void eliminaPari (ListaPointer *top);
void eliminaDispari (ListaPointer *top);

int main ()
{
    ListaPointer lista = NULL;

    for(size_t i = 1; i <= 10; i++){
        inserisciNodoTesta(&lista, (int) i);
    }

    puts("Lista: ");
    printLista(lista);

    puts("\nElimino i nodi dispari dalla lista: ");
    eliminaDispari(&lista);
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

void printLista (const ListaPointer top)
{
    if(!top) {
        printf("// \n");
        return;
    }

    printf("%d -> ", top->info);
    printLista(top->next);
}

void svuotaLista (ListaPointer *top)
{
    if(!*top){
        return;
    }
    
    ListaPointer temp = *top;
    *top = (*top)->next;
    free(temp);
    svuotaLista(&*top);
}

void eliminaPari (ListaPointer *top)
{
    ListaPointer head = *top;

    while(head){
        ListaPointer temp = head->next;
        head->next = temp->next;
        free(temp);
        head = head->next;
    }
}

void eliminaDispari (ListaPointer *top)
{
    ListaPointer head = *top;
    ListaPointer temp = NULL;
    
    if(!head){
        return;
    }

    temp = head;
    head = head->next;
    free(temp);
    *top = head;

    while(head && head->next) {
        temp = head->next;
        head->next = temp->next;
        head = head->next;
        free(temp);
    }
}