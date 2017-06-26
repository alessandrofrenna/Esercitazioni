#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASCII_A 97
#define ASCII_Z 122
#define MAX 15

struct nodo {
    char info;
    struct nodo *next;
};

typedef struct nodo Lista;
typedef Lista *ListaPtr;

void inserisciInCoda (ListaPtr *top, char element);
void printLista (const ListaPtr top);

char randomChar ();
int randomInt (size_t offset, size_t max);
int lunghezzaLista (const ListaPtr top);
void populateArray (ListaPtr top, ListaPtr *vettore, int dim);
ListaPtr getPointer (ListaPtr top, int posizione);
int compatibile (ListaPtr *vettore, int dim, ListaPtr top);
void vettprintf(ListaPtr *vettore, int dim);

int main ()
{
    ListaPtr lista = NULL;
    srand(time(NULL));
    

    int number;
    printf("Minimo di elementi? ");
    scanf("%d", &number);
    getchar();
    
    ListaPtr vettore[number];

    int size = number + rand() % (MAX + 1 - number);

    for(size_t i = 0; i < size; i++) {
        char c = randomChar();
        inserisciInCoda(&lista, c);
    }

    puts("Stampo la lista: ");
    printLista(lista);

    printf("La lista ha %d elementi!\n\n", lunghezzaLista(lista));

    populateArray(lista, vettore, number);

    if(compatibile(vettore, number, lista)==1){
        vettprintf(vettore, number);
    } else {
        puts("Vettore e lista non sono compatibili!");
    }

}

void inserisciInCoda (ListaPtr *top, char element)
{
    ListaPtr coda = NULL;
    ListaPtr nuovo = NULL;

    nuovo = malloc(sizeof(Lista));
    if(!nuovo){
        return;
    }

    nuovo->info = element;

    if(!*top) {
        nuovo->next = *top;
        *top = nuovo;
    } else {
         coda = *top;
         while(coda->next){
             coda = coda->next;
         }
         coda->next = nuovo;
         nuovo->next = NULL;
    }

}

void printLista(const ListaPtr top)
{
    if(!top){
        printf("//\n");
        return;
    }
    printf("%c -> ", top->info);
    printLista(top->next);
}

char randomChar ()
{
    char chars[25] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
        'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'x', 'y', 'z'
    };
    int index = 0 + (rand() % 24);
    return chars[index];
}

int randomInt (size_t offset, size_t max)
{
    return offset + rand() % max;
}

int lunghezzaLista (const ListaPtr top)
{
    if(!top){
        return 0;
    }

    return 1 + lunghezzaLista(top->next);
}

void populateArray (ListaPtr top, ListaPtr *vettore, int dim)
{
    int length = lunghezzaLista(top);
    
    for(size_t i = 0; i < dim; i++){
        vettore[i] = getPointer(top, 0 + rand() % length);
    }
}

ListaPtr getPointer (ListaPtr top, int posizione)
{   
    if(!top){
        return NULL;
    }

    if(posizione == 0) {
        return top;
    }

    getPointer(top->next, --posizione);
}

int compatibile (ListaPtr *vettore, int dim, ListaPtr top)
{
    ListaPtr head = top;
    size_t i = 0;
    int compatibile = 0;

    while(head){
        if(vettore[i] == head) {
            compatibile++;
            
            if(i <= dim-1) {
                i++;
            } else {
                break;
            }
        }
        head = head->next;
    }

    if(compatibile == dim) {
        
        return 1;
    } else {
        return 0;
    }
    
}

void vettprintf(ListaPtr *vettore, int dim)
{
    puts("La parola che si forma è: ");
    for(size_t i = 0; i < dim; i++){
        printf("%c", vettore[i]->info);
    }
    puts("\n");

}