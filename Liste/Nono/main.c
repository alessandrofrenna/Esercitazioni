#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "liste.h"

int generaRandom(size_t offset, size_t max);
ListaPointer randomLista(size_t maxElementi);

int main (int argc, char **argv)
{
    srand(time(NULL));
    ListaPointer listauno = randomLista(10);
    ListaPointer listadue = randomLista(10);
    
    puts("Lista uno: ");
    printLista(listauno);
    puts("");
    puts("Lista due: ");
    printLista(listadue);

    puts("Lista uno ordinata: ");
    mergeSort(&listauno);
    printLista(listauno);
    puts("");
    puts("Lista due ordinata: ");
    mergeSort(&listadue);
    printLista(listadue);

    printf("\nLa prima lista è lunga: %d\n\n", lunghezzaLista(listauno));
    printf("La seconda lista è lunga: %d\n\n", lunghezzaLista(listadue));

    ListaPointer concatenata = concatena(listauno, listadue);
    puts("Le due liste concatenate sono: ");
    printLista(concatenata);

    printf("\nLa lista concatenata è lunga: %d\n\n", lunghezzaLista(concatenata));

    svuotaLista(listauno);
    svuotaLista(listadue);
    svuotaLista(concatenata);
}

int generaRandom(size_t offset, size_t max) 
{
    return offset + rand() % max;
}

ListaPointer randomLista(size_t maxElementi)
{
    ListaPointer lista = initLista();
    size_t size = generaRandom(1, maxElementi);
    for(; size > 0; --size){
        int value = generaRandom(1, 100);
        inserisciNodoTesta(&lista, value);
    }   

    return lista;
}