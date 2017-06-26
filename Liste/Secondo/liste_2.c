#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 3

//Struttura autoreferenziale 
struct node {
    int info;
    struct node *next;
};

//Alias
typedef struct node Lista;
typedef Lista *ListaPointer;

//Carichiamo sta volta la lista da un file

//Prototipi

//Inserimento in lista, non necessariamente ordinato.
//Inserisco in coda!
FILE * apriFile (char *nome, char *mode);
bool controllaFile (FILE *filePointer);
void inserisciInLista (ListaPointer *top, ListaPointer *tail, int dato);
ListaPointer creaListaDaFile (FILE *filePointer);
bool listaVuota (const ListaPointer const top);
int lunghezzaListaRicorsiva (ListaPointer top, int lunghezza);
int lunghezzaListaIterativa (ListaPointer top);
void stampaLista (ListaPointer top);
void dropLista (ListaPointer *top);

//Funzioni accessorie
static void fileNonTrovato ();
static void listaVuotaMessaggio ();

//Main
int main (int argc, char **argv) 
{
    if(argc != 2) {
        puts("Inserisci il nome del file da aprire!");
    }

    ListaPointer lista = NULL;

    char modo[SIZE];
    printf("Inserisci il modo in cui vuoi aprire il file: ");
    fgets(modo, SIZE, stdin);
    
    FILE *file = apriFile(argv[1], modo);
    
    if(controllaFile(file)) {
        lista = creaListaDaFile(file);
        fclose(file);
    }
    
    if(listaVuota(lista)) {
        listaVuotaMessaggio();
    } else {
        printf("\nLa lista è lunga: %d \n", lunghezzaListaRicorsiva(lista, 0));
        puts("");
        puts("La lista è: ");    
        stampaLista(lista);
    }

    dropLista (&lista);
}

FILE * apriFile (char *nome, char *mode)
{   
    FILE *file;
    file = fopen(nome, mode);
    if(!file) {
        return NULL;
    }
}

bool controllaFile (FILE *filePointer)
{
    return filePointer ? true : false;
}

void inserisciInLista (ListaPointer *top, ListaPointer *tail, int dato) 
{
    ListaPointer nuovo = NULL;

    nuovo = malloc(sizeof(Lista));

    if(!nuovo) {
        puts("Non posso allocare nuova memoria!");
        return;
    }

    nuovo->info = dato;

    if(!*top) {
        nuovo->next = *top;
        *top = nuovo;
    } else {
        (*tail)->next = nuovo;
    }

    *tail = nuovo;
}

ListaPointer creaListaDaFile (FILE *filePointer) 
{
    ListaPointer head = NULL, tail = NULL;
    int elemento;
    while(fscanf(filePointer, "%d", &elemento) > 0) {
        inserisciInLista(&head, &tail, elemento);
    }

    if(!head) {
        return NULL;
    }
    return head;
} 

bool listaVuota (const ListaPointer const top) 
{
    return !top ? true : false;
}

void stampaLista (ListaPointer top)
{
    if(!top){
        printf("//");
        puts("");
        return;
    }

    printf("%d -> ", top->info);
    stampaLista(top = top->next);
}

static void fileNonTrovato () 
{
    puts("File non trovato, non posso aprirlo!");
}

static void listaVuotaMessaggio ()
{
    puts("File vuoto, non è stato possibile inizializzare la lista! Lista vuota!");
}

int lunghezzaListaRicorsiva (ListaPointer top, int lunghezza)
{
    if(!top){
        return lunghezza;
    }

    lunghezzaListaRicorsiva(top = top->next, ++lunghezza);
}

int lunghezzaListaIterativa (ListaPointer top)
{
    size_t lunghezza = 0;

    while(top) {
        lunghezza++;
        top = top->next;
    }

    return lunghezza;
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