#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *left;
    struct node *right;
};

typedef struct node Tree;
typedef Tree *TreePtr;

static int level = 0;

void nuovoNodo (TreePtr *root, int elemento);
void inOrdine (const TreePtr root);
void preOrdine (const TreePtr root);
void postOrdine (const TreePtr root);
TreePtr searchNode (const TreePtr root, int elemento);
TreePtr nodoMinimo (const TreePtr root);
TreePtr nodoMassimo (const TreePtr root);
void eliminaNodo (TreePtr *root, int elemento);
void eliminaMinimo (TreePtr *root);
int sommaValoriAlberi (TreePtr root);
int hightAlbero (const TreePtr root);
int numFoglie (const TreePtr root);
void inOrdineInverso (const TreePtr root);
int totGTK (const TreePtr root, int k);
void inOrdineArray (const TreePtr root, TreePtr *array, int *index);
int totBetween (const TreePtr root, int a, int b);
int numeroNodi (const TreePtr root);
void inOrdineLessM (const TreePtr root, int m); 
int isBST (const TreePtr root);
void checkIfOne (const TreePtr root);
void prettyAlbero (const TreePtr root);
TreePtr LCA (const TreePtr root, int n1, int n2);
TreePtr inOrderSuccessor (const TreePtr root, int val);

int main ()
{
    TreePtr albero = NULL;
    nuovoNodo(&albero, 10);
    nuovoNodo(&albero, 5);
    nuovoNodo(&albero, 15);
    nuovoNodo(&albero, 4);
    nuovoNodo(&albero, 7);
    nuovoNodo(&albero, 17);
    nuovoNodo(&albero, 14);
    nuovoNodo(&albero, 16);
    nuovoNodo(&albero, 18);
    

    puts("Stampo l'albero in ordine: ");
    inOrdine(albero);
    puts("");
    TreePtr minimo  = nodoMinimo(albero);
    TreePtr massimo = nodoMassimo(albero);

    if(minimo){
        printf("Nodo minimo trovato, ha valore: %d\n", minimo->info);
    } else {
        printf("Nodo minimo non trovato\n");
    }

    if(massimo){
        printf("Nodo massimo trovato, ha valore: %d\n", massimo->info);
    } else {
        printf("Nodo massimo non trovato\n");
    }

    printf("Numero di foglie dell'Albero: %d\n", numFoglie(albero));

    puts("Stampo albero in ordine inverso: ");
    inOrdineInverso(albero);
    puts("");

    printf("Numero di elementi maggiori di 10: %d\n", totGTK(albero, 10));

    printf("Numero di elementi compresi tra 10 e 20: %d \n", totBetween(albero, 10, 20));

    puts("Stampo i primi 3 elementi in ordine: ");
    inOrdineLessM(albero, 3);
    puts("");

    if(isBST(albero)){
        puts("E' un BST");
    } else {
        puts("Non è un BST");
    }

    puts("Albero carino: ");
    prettyAlbero(albero);

    checkIfOne(albero);

    TreePtr res = LCA(albero, 14, 18);

    if(res){
        printf("LCA = %d\n", res->info);
    } else {
        puts("LCA not found");
    }

    if(!inOrderSuccessor(albero, 10)){
        puts("IOS non trovato");
    } else {
        printf("In Order Successor: %d\n", inOrderSuccessor(albero, 10)->info);
    }
}

void nuovoNodo (TreePtr *root, int elemento)
{
    if(!*root){
        *root = malloc(sizeof(TreePtr));
        (*root)->info = elemento;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else if((*root)->info > elemento) {
        nuovoNodo(&(*root)->left, elemento);
    } else if((*root)->info < elemento){
        nuovoNodo(&(*root)->right, elemento);
    } else {
        printf("Elemento %d duplicato, non lo inserisco!\n", elemento);
    }
}

void inOrdine (const TreePtr root)
{
    if(!root){
        return;
    }

    inOrdine(root->left);
    printf("%d ", root->info);
    inOrdine(root->right);
}

void preOrdine (const TreePtr root)
{
    if(!root){
        return;
    }

    printf("%d ", root->info);
    inOrdine(root->left);
    inOrdine(root->right);
}

void postOrdine (const TreePtr root)
{
    if(!root){
        return;
    }

    inOrdine(root->left);
    inOrdine(root->right);
    printf("%d ", root->info);
}

TreePtr searchNode (const TreePtr root, int elemento)
{
    if(!root){
        return NULL;
    }

    if(root->info == elemento){
        return root;
    } 

    if(root->info > elemento) {
        return searchNode(root->left, elemento);
    }

    return searchNode(root->right, elemento);
}


TreePtr nodoMinimo (const TreePtr root)
{  
    if(!root){
        return NULL;
    }

    if(!root->left){
        return root;
    } 

    return nodoMinimo(root->left);
}

TreePtr nodoMassimo (const TreePtr root)
{
    if(!root){
        return NULL;
    }

    if(!root->right){
        return root;
    }

    return nodoMassimo(root->right);
}

void eliminaNodo (TreePtr *root, int elemento)
{
    if(!*root){
        return;
    }

    TreePtr temp = NULL;

    if((*root)->info == elemento) {
        if(!(*root)->left && !(*root)->right){
            *root = NULL;
            free(*root);
        } else if(!(*root)->left){
            temp = *root;
            *root = (*root)->right;
            free(temp);
        } else if(!(*root)->right){
            temp = *root;
            *root = (*root)->left;
            free(temp);
        } else {
            TreePtr minimo = nodoMinimo((*root)->right);
            int value = minimo->info;
            eliminaMinimo(&(*root)->right);
            (*root)->info = value;
        }
    } else if((*root)->info > elemento) {
        eliminaNodo(&(*root)->left, elemento);
    } else {
        eliminaNodo(&(*root)->right, elemento);
    }
}

void eliminaMinimo (TreePtr *root)
{
    if(!*root) {
        return;
    }
    TreePtr temp = NULL;
    if(!(*root)->left){
         temp = *root;
        *root = (*root)->right;
        free(temp);
    } else {
        eliminaMinimo(&(*root)->left);
    }
}

int sommaValoriAlberi (TreePtr root)
{
    if(!root){
        return 0;
    }

    return root->info + sommaValoriAlberi(root->left) + sommaValoriAlberi(root->right);
}

int hightAlbero (const TreePtr root)
{
    if(!root){
        return 0;
    }

    int sx = hightAlbero(root->left);
    int dx = hightAlbero(root->right);

    return sx >= dx ? sx + 1 : dx + 1;
}

int numFoglie (const TreePtr root)
{
    if(!root){
        return 0;
    }

    if(!root->left && !root->right){
        return 1;
    }

    int foglie = numFoglie(root->left) + numFoglie(root->right);
    return foglie;
}

void inOrdineInverso (const TreePtr root)
{
    if(!root){
        return;
    }

    inOrdineInverso(root->right);
    printf("%d ", root->info);
    inOrdineInverso(root->left);

}

int totGTK (const TreePtr root, int k)
{
    if(!root){
        return 0;
    }
    if(root->info <= k) {
        return totGTK(root->right, k);
    } else {
        return 1 + totGTK(root->left, k) + totGTK(root->right, k);
    }

}

void inOrdineArray (const TreePtr root, TreePtr *array, int *index)
{
    if(!root){
        return;
    }

    inOrdineArray(root->left, array, index);
    array[*index] = root;
    (*index)++;
    inOrdineArray(root->right, array, index);
}

int numeroNodi (const TreePtr root)
{
    if(!root){
        return 0;
    }

    return 1 + numeroNodi(root->left) + numeroNodi(root->right);
}

int totBetween (const TreePtr root, int a, int b)
{
    int dim = numeroNodi(root);
    int index = 0;
    TreePtr array[dim];
    inOrdineArray(root, array, &index);
    int totale = 0;
    for (size_t i = 0; i < dim; i++){
        if(array[i]->info >= a && array[i]->info <= b){
            totale++;
        }
    }
    return totale;
}

void inOrdineLessM (const TreePtr root, int m) 
{
    int dim = numeroNodi(root);
    TreePtr array[dim];
    int index = 0;
    inOrdineArray(root, array, &index);
    for(size_t i = 0; i < m; i++){
        printf("%d ", array[i]->info);
    }
    puts("");
}

int isBST (const TreePtr root)
{
    TreePtr array[numeroNodi(root)];
    int index = 0;
    inOrdineArray(root, array, &index);

    //Controllo se l'array è in ordine con l'insertion sort??
    for(size_t i = 1; i < numeroNodi(root); i++) {
        int current = array[i]->info;
        for(size_t j = i; j > 0 && array[j-1]->info > current ; j--){
            return 0;
        }
    }
    return 1;
}

void checkIfOne (const TreePtr root)
{
    if(!root){
        puts("Albero vuoto!");
        return;
    }

    if(root->left && root->right){
        puts("Ogni nodo dell'albero non ha un solo figlio!");
        return;
    }

    if(root->right && !root->left) {
        checkIfOne(root->right);
    } else if(root->left && !root->right){
        checkIfOne(root->left);
    } else {
        puts("Ogni nodo ha un solo figlio!");
    }
}

void prettyAlbero (const TreePtr root)
{
    if(!root){
        return;
    }
    level++;
    prettyAlbero(root->right);
    printf(" %*s%5d\n", level*5, "", root->info);
    prettyAlbero(root->left);
    level--;
}

TreePtr LCA (const TreePtr root, int n1, int n2)
{
    /*
        E' l'antenato condiviso di n1 ed n2 
        locato lontano dalla radice.
        E' il nodo piu' piccolo che ha come
        discendenti sia n1 che n2.
    */
    if(!root){
        return NULL;
    }

    if(root->info >= n1 && root->info <= n2){
        return root;
    }

    if(root->info > n1 && root->info > n2){
        return LCA(root->left, n1, n2);
    }
    if(root->info < n1 && root->info < n2) {
        return LCA(root->right, n1, n2);
    }
}

TreePtr inOrderSuccessor (const TreePtr root, int val)
{
    //E' il nodo che viene dopo a quello dato
    //nella scansione in ordine di un albero.
    TreePtr array[numeroNodi(root)];
    int index = 0;
    inOrdineArray(root, array, &index);

    for(size_t i = 0; i < numeroNodi(root); i++){
        if(array[i]->info == val){
            return array[i+1];
        }
    }
    return NULL;
}