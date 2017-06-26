#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct nodo {
    int info;
    struct nodo *next;
};

typedef struct nodo Lista;
typedef Lista * ListaPtr;

//Protitipi
void insertInOrder(ListaPtr *head, int dato);
void stampaLista(ListaPtr head);
int generaRandom(size_t offset, size_t max);
ListaPtr generaRandomLista(size_t max, size_t max_value);
ListaPtr mergeListe(ListaPtr l1, ListaPtr l2);
void emptyLista (ListaPtr *head);
int isEmpty(ListaPtr head);

int main ()
{
    srand(time(NULL));
    ListaPtr prima   = generaRandomLista(10, 100);
    ListaPtr seconda = generaRandomLista(10, 100);

    puts("\nLa prima lista è:");
    stampaLista(prima);

    puts("\nLa seconda lista è:");
    stampaLista(seconda);

    ListaPtr terza = mergeListe(prima, seconda);
    
    puts("\nLa lista ottenuta per fusione è:");
    stampaLista(terza);

    puts("Libero le liste: ");
    emptyLista (&prima);
    emptyLista (&seconda);
    emptyLista (&terza);
    puts(isEmpty(prima) ? "La prima è vuota" : "Errore eliminazione!" );
    puts(isEmpty(seconda) ? "La seconda è vuota" : "Errore eliminazione!" );
    puts(isEmpty(seconda) ? "La terza è vuota" : "Errore eliminazione!" );
}

void insertInOrder(ListaPtr *head, int dato)
{
    ListaPtr nuovo = NULL;
    nuovo = malloc(sizeof(Lista));
    if(!nuovo) {
        puts("Non posso allocare la memoria!");
        return;
    }
    
    nuovo->info = dato;
    
    ListaPtr current = *head;
    ListaPtr prev = NULL;

    while(current && current->info < dato) {
        prev = current;
        current = current->next;
    }

    if(prev == NULL){
        nuovo->next = *head;
        *head = nuovo;
    } else {
        prev->next = nuovo;
        nuovo->next = current;
    }
}

void stampaLista(ListaPtr head)
{
    if(!head){
        printf("//\n\n");
        return;
    }
    printf("%d -> ", head->info);
    stampaLista(head = head->next);
}

int generaRandom(size_t offset, size_t max)
{
    return offset + rand() % max;
}

ListaPtr generaRandomLista(size_t max, size_t max_value)
{
    size_t offset = 1;
    ListaPtr lista = NULL;
    size_t elementi = generaRandom(offset, max);
    for(; elementi; elementi--){
        insertInOrder(&lista, generaRandom(offset, max_value));
    }
    return lista;
}

ListaPtr mergeListe(ListaPtr l1, ListaPtr l2)
{
    ListaPtr result, cl1 = l1, cl2 = l2;
    ListaPtr temp;

    temp = malloc(sizeof(Lista));
    
    if(!temp){
        return NULL;
    }

    result = temp;
    temp->next = NULL;
    
    while(cl1 && cl2){
        if(cl1->info <= cl2->info){
            temp->info = cl1->info;
            cl1 = cl1->next;
        } else {
            temp->info = cl2->info;
            cl2 = cl2->next;
        }      
        temp->next = malloc(sizeof(Lista));
        if(!temp->next){
            emptyLista(&result);
            return NULL;
        }
        temp = temp->next;
        temp->next = NULL;
    }
    
    if(!cl1){
        temp->info = cl2->info;
        while(cl2 = cl2->next) {
            temp->next = malloc(sizeof(Lista));
            if(!temp->next){
                emptyLista(&result);
                return NULL;
            }
            temp = temp->next;
            temp->next = NULL;
            temp->info = cl2->info;
        }
    } else {
        temp->info = cl1->info;
        while(cl1 = cl1->next) {
            temp->next = malloc(sizeof(Lista));
            if(!temp->next){
                emptyLista(&result);
                return NULL;
            }
            temp = temp->next;
            temp->next = NULL;
            temp->info = cl1->info;
        }        
    }
    return result;
}

void emptyLista (ListaPtr *head)
{
    if(!*head){
        return;
    }
    ListaPtr temp = *head;
    *head = (*head)->next;
    emptyLista(&(*head));
    free(temp);
}

int isEmpty(ListaPtr head)
{
    return head == NULL;
}