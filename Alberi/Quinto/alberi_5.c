#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int info;
    struct nodo *left;
    struct nodo *right;
};

typedef struct nodo Tree;
typedef Tree *TPtr;

void insertNodo (TPtr *root, int elemento);
int sommaNodi (const TPtr root);
void prettyTree (const TPtr root);
void changeTreeBySum (TPtr root, int *sum);
static int level = 0;

int main ()
{
    int array[15] = {50, 23, 25, 12, 15, 78, 54, 79, 1, 24, 98, 121, 12, 91, 56};
    TPtr albero = NULL;
    for(int i = 0; i < 15; i++){
        insertNodo(&albero, array[i]);
    }

    int somma = sommaNodi(albero);
    printf("La somma di tutti gli elementi contenuti nei nodi dell'albero è: %d\n\n", somma);

    puts("\n\nStampo l'albero: \n\n");
    prettyTree(albero);

    puts("Sto per fare una magia. Vuoi vederla? Y/N");
    if(getchar() == 'Y'){
        system("clear");
    }else {
        puts("Peccato...");
        return 0;
    }

    puts("Ecco la magia!\n\n");

    puts("L'albero prima era: \n\n");
    prettyTree(albero);
    somma = 0;
    changeTreeBySum(albero, &somma);
    puts("\n\nL'albero ora è: \n\n");
    prettyTree(albero);

}

void insertNodo (TPtr *root, int elemento)
{
    if(!*root){
        *root = malloc(sizeof(Tree));
        (*root)->info = elemento;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else if((*root)->info > elemento) {
        insertNodo(&(*root)->left, elemento);
    } else if((*root)->info < elemento) {
        insertNodo(&(*root)->right, elemento);
    } else {
        puts("Duplicato. Non inseriamo i duplicati noi!\n");
    }

}

int sommaNodi (const TPtr root)
{
    if(!root){
        return 0;
    }

    return root->info + sommaNodi(root->left) + sommaNodi(root->right);
}

void prettyTree (const TPtr root)
{
    if(!root){
        return;
    }
    level++;
    prettyTree (root->right);
    printf(">%*s%5d\n", level*5, "", root->info);
    prettyTree (root->left);
    level--;
}

void changeTreeBySum (TPtr root, int *sum)
{   
    if(!root){
        return;
    }
    //Ricorsione a destra.
    changeTreeBySum(root->right, sum);
    
    //Aggiorno accumulatore con somma elementi 
    //Più grandi di quello del nodo.
    *sum += root->info;

    //Aggiorno il campo del nodo levando
    //il valore precedente dalla somma.
    root->info = *sum - root->info;

    //Ricosrsione a sinistra.
    changeTreeBySum(root->left, sum);

}