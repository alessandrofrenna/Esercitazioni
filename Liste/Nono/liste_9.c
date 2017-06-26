#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

struct nodo {
    int info;
    struct nodo *next;
};

int getElemento (ListaPointer top) 
{
    return top->info;
}

void setElemento (ListaPointer top, int elemento)
{
    (top)->info = elemento;
    return;
}

ListaPointer initLista ()
{
    return NULL;
}

void inserisciNodoTesta (ListaPointer *top, int elemento)
{
    ListaPointer nuovo = NULL;
    nuovo = malloc(sizeof(Lista));

    if(!nuovo){
        return;
    }

    setElemento(nuovo, elemento);
    nuovo->next = *top;
    *top = nuovo;
}

void inserisciNodoCoda (ListaPointer *top, int elemento)
{
    ListaPointer current = NULL;
    ListaPointer nuovo = NULL;
    nuovo = malloc(sizeof(Lista));

    if(!nuovo){
        return;
    }

    setElemento(nuovo, elemento);

    if(!*top){
        nuovo->next = (*top);
        (*top) = nuovo;
    } else {
        current = *top;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = nuovo;
        nuovo->next = NULL;
    }
}

void inserisciNodoOrdinato (ListaPointer *top, int elemento)
{
    ListaPointer current = NULL;
    ListaPointer previous = NULL;
    ListaPointer nuovo = NULL;

    nuovo = malloc(sizeof(nuovo));
    if(!nuovo) {
        return;
    }
    setElemento(nuovo, elemento);
    
    current = *top;
    previous = NULL;

    while(current && getElemento(current) < elemento){
        previous = current;
        current = current->next;
    }

    if(!previous){
        nuovo->next = *top;
        (*top) = nuovo;
    } else {
        previous->next = nuovo;
        nuovo->next = current;
    }
}

void printLista (ListaPointer top)
{
    if(!top){
        printf("//\n");
        return;
    }
    printf("%d -> ", getElemento(top));
    printLista(top->next);
}

int lunghezzaLista (const ListaPointer top)
{
    if(!top){
        return 0;
    }

    return 1 + lunghezzaLista(top->next);
}

ListaPointer searchLista (const ListaPointer top, int elemento)
{
    if(!top){
        return NULL;
    }

    if(getElemento(top) == elemento){
        return top;
    }

    return searchLista(top->next, elemento);
}

ListaPointer copyLista (ListaPointer top)
{
    ListaPointer nuovaLista;
    ListaPointer nuovoNodo = NULL;

    nuovoNodo = malloc(sizeof(Lista));
    
    setElemento(nuovoNodo, getElemento(top));
    nuovoNodo->next = NULL;
    
    nuovaLista = nuovoNodo;

    while(top = top->next){
        nuovoNodo->next = malloc(sizeof(Lista));
        nuovoNodo = nuovoNodo->next;
        setElemento(nuovoNodo, getElemento(top));
    }

    return nuovaLista;
}

void cencellaElemento (ListaPointer *top, int elemento)
{
    ListaPointer current = NULL;
    ListaPointer previous = NULL;
    if(getElemento(*top) == elemento) {
        ListaPointer temp = *top;
        (*top) = (*top)->next;
        free(temp);
    } else {
        current = *top;

        while(current && elemento != getElemento(current)){
            previous = current;
            current = current->next;
        }

        if(!current){
            puts("Elemento non trovato");
            return;
        }

        ListaPointer temp = current;
        current = current->next;
        previous->next = current;
        free(temp);
    }

}

void cancellaTutteOccorrenze (ListaPointer *top, int elemento)
{
    ListaPointer head = *top;
    ListaPointer previous = NULL;
    ListaPointer temp = NULL;
    
    if(getElemento(head) == elemento){
        temp = head;
        head = head->next;
        free(temp);
        (*top) = head;
    } else {
        head = head->next;
    }

    while(head){
        if(getElemento(head) == elemento){
            temp = head;
            head = head->next;
            free(temp);
            
            if(previous) {
                previous->next = head;
            }
        } else {
            previous = head;
            head = head->next;
        }
    }
}

void svuotaLista (ListaPointer top)
{
    if(!top){
        return;
    }
    ListaPointer temp = top;
    svuotaLista(top->next);
    free(temp);
}

ListaPointer mergeSort (ListaPointer *top)
{
    ListaPointer temp = *top;
    ListaPointer halfUno = temp;
    ListaPointer halfDue = temp->next;

    if(!temp || !temp->next) {
        return NULL;
    }

    while(halfDue && halfDue->next){
        halfDue = halfDue->next->next;
        temp = temp->next;
    }

    halfDue = temp->next;
    temp->next = NULL;

    mergeSort(&halfUno);
    mergeSort(&halfDue);

    return *top = concatena(halfUno, halfDue);

}

ListaPointer concatena (const ListaPointer listauno, const ListaPointer listadue)
{
    ListaPointer risultato, tempuno = listauno, tempdue = listadue;
    ListaPointer temprisultato = NULL;

    temprisultato = malloc(sizeof(Lista));

    if(!temprisultato){
        return NULL;
    }

    risultato = temprisultato;
    temprisultato->next = NULL;

    while(tempuno && tempdue){
        if(getElemento(tempuno) <= getElemento(tempdue)){
            setElemento(temprisultato, getElemento(tempuno));
            tempuno = tempuno->next;
        } else {
            setElemento(temprisultato, getElemento(tempdue));
            tempdue = tempdue->next;
        }
        temprisultato->next = malloc(sizeof(Lista));
        temprisultato = temprisultato->next;
        if(!temprisultato){
            svuotaLista(risultato);
            return NULL;
        }
        temprisultato->next = NULL;
    }

    if(!tempuno){
        setElemento(temprisultato, getElemento(tempdue));
        while(tempdue = tempdue->next){
            temprisultato->next = malloc(sizeof(Lista));
            temprisultato = temprisultato->next;
            if(!temprisultato){
                svuotaLista(risultato);
                return NULL;
            }
            setElemento(temprisultato, getElemento(tempdue));
            temprisultato->next = NULL;
        }
    } else {
        setElemento(temprisultato, getElemento(tempuno));
        while(tempuno = tempuno->next){
            temprisultato->next = malloc(sizeof(Lista));
            temprisultato = temprisultato->next;
            if(!temprisultato){
                svuotaLista(risultato);
                return NULL;
            }
            setElemento(temprisultato, getElemento(tempuno));
            temprisultato->next = NULL;
        }       
    }
    return risultato;
}

ListaPointer concatenaDue (ListaPointer listauno, ListaPointer listadue)
{
    Lista risultato;
    ListaPointer risPtr = &risultato;

    while(listauno && listadue){
        if(getElemento(listauno) <= getElemento(listadue)){
            risPtr->next = listauno;
            risPtr = listauno;
            listauno = listauno->next;
            
        } else {
            risPtr->next = listadue;
            risPtr = listadue;
            listadue = listadue->next;
        }
    }

    risPtr->next = !listauno ? listadue : listauno;
    return risultato.next;    
}