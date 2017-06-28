#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct nodoAlbero {
    int info;
    struct nodoAlbero * left;
    struct nodoAlbero * right;
};

struct nodoLista {
    int info;
    struct nodoLista *next;
};

typedef struct nodoAlbero Tree;
typedef Tree *TPtr;

typedef struct nodoLista Lista;
typedef Lista *LPtr;


//Funzioni lista!
void inserisciInOrdine (LPtr *nodo, int elemento);
void printLista (const LPtr nodo);
int dimensioneLista(const LPtr nodo);

//Funzioni per array!
void arrayFromLista (const LPtr nodo, int *array, int *index);
void printArray (const int *array, int dim);
int eliminaDuplicati (int *array, int dim);

//Funzioni Alberi!
TPtr inalbera (const int *array, int start, int end);
void prettyTree (const TPtr root);
void removeNotInRange (TPtr *root, int *array, int num1, int num2, int dim);
void deleteFromTree (TPtr *root, int element);
TPtr findMinimo (const TPtr root);
void deleteMinimo (TPtr *root);
static int level = 0;

int main ()
{
    srand(time(NULL));
    LPtr lista = NULL;
    puts("Lista ordinata:");
    for(size_t i = 0; i < 10; i++){
        int value = i + rand() % 100;
        
        inserisciInOrdine(&lista, value);
    }

    printLista(lista);

    int array[dimensioneLista(lista)];
    int index = 0;
    arrayFromLista(lista, array, &index);
    index = eliminaDuplicati(array, index);
    puts("Creo l'albero dalla lista concatenata ordinata: ");
    TPtr albero = inalbera(array, 0, index - 1);
    prettyTree(albero);
    puts("Insert new tab to continue!");
    char c = getchar();
    if(c == '\n') {
        system("clear");
    } else {
        return 0;
    }

    puts("Elimino gli elementi fuori dall'intervallo 30-70: ");
    removeNotInRange(&albero, array, 30, 70, index);
    puts("Stampo l'albero: \n'");
    prettyTree(albero);
    
}

//Funzioni Lista
void inserisciInOrdine (LPtr *nodo, int elemento)
{
    LPtr nuovo = NULL;
    nuovo = malloc(sizeof(Lista));
    if(!nuovo){
        return;
    }

    nuovo->info = elemento;
    LPtr current = *nodo;
    LPtr prec    = NULL ;

    while(current && elemento >= current->info){
        prec = current;
        current = current->next;
    }

    if(!prec){
        nuovo->next = *nodo;
        *nodo = nuovo;
    } else {
        prec->next = nuovo;
        nuovo->next = current;
    }
}

void printLista (const LPtr nodo)
{
    if(!nodo){
        printf("//\n");
        return;
    }
    printf("%d -> ", nodo->info);
    printLista(nodo->next);
}

int dimensioneLista(const LPtr nodo)
{
    if(!nodo){
        return 0;
    }

    return 1 + dimensioneLista(nodo->next);
}


//Funzioni array
void arrayFromLista (const LPtr nodo, int *array, int *index)
{
    if(!nodo){
        return;
    }
    array[*index] = nodo->info;
    (*index)++;
    arrayFromLista (nodo->next, array, index);
}

void printArray (const int *array, int dim)
{
    for(size_t i = 0; i < dim; i++){
        printf("Array[%lu] = %d\n", i, array[i]);
    }
}

int eliminaDuplicati (int *array, int dim)
{
    int k = 1;
    for(size_t i = 1; i < dim; i++){
        if(array[i] != array[i-1]){
            array[k++] = array[i];
        }
    }
    return k;
}


//Funzioni alberi
TPtr inalbera (const int *array, int start, int end)
{
    if(start - end > 0) {
        return NULL;
    } else {
        int middle = ( start + end ) / 2;
        TPtr root = NULL;
        root = malloc(sizeof(Tree));
        root->info = array[middle];
        root->left = inalbera(array, start, middle - 1);
        root->right = inalbera(array, middle + 1, end);
        return root;
    }
}

void prettyTree (const TPtr root)
{
    if(!root){
        return;
    }

    level++;
    prettyTree(root->right);
    printf(">%*s%5d\n", level * 5, "", root->info);
    prettyTree(root->left);
    level--;
}

void removeNotInRange (TPtr *root, int *array, int num1, int num2, int dim)
{
    if(!root){
        return;
    }

    for(size_t i = 0; i < dim; i++) {
        if(array[i] < num1 || array[i] > num2) {
            deleteFromTree(root, array[i]);
        }
    }
}

void deleteFromTree (TPtr *root, int element)
{
    if(!*root){
        return;
    }

    if((*root)->info == element){
        if(!(*root)->right && !(*root)->left){
            free(*root);
            *root = NULL;
            return;
        } 

        TPtr temp = *root;

        if(!(*root)->left){
            (*root) = (*root)->right;
            free(temp);
            return;
        }

        if(!(*root)->right){
            (*root) = (*root)->left;
            free(temp);
            return;
        }

        TPtr min = findMinimo((*root)->right);
        int val = min->info;
        deleteFromTree(&(*root)->right, val);
        (*root)->info = val;
    } else if(element > (*root)->info) {
        deleteFromTree(&(*root)->right, element);
    } else {
        deleteFromTree(&(*root)->left, element);
    }

}

TPtr findMinimo (const TPtr root)
{
    if(!root){
        return NULL;
    }

    if(!root->left){
        return root;
    }

    return findMinimo(root->left);
}

void deleteMinimo (TPtr *root)
{
    if(!*root){
        return;
    }

    if(!(*root)->left){
        TPtr temp = *root;
        (*root) = (*root)->right;
        temp = NULL;
        free(temp);
    } else {
        deleteMinimo(&(*root)->left);
    }

}