#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo {
    int info;
    struct nodo *left;
    struct nodo *right;
};

typedef struct nodo Tree;
typedef Tree *TPtr;
static int level = 0;

void insertNode (TPtr *root, int elemento);
void inOrder (const TPtr root);
void preOrder (const TPtr root);
void postOrder (const TPtr root);
void prettyTree (const TPtr root);
TPtr fromOrderedArray (int *array, int start, int end);
bool BSTsareEqual (const TPtr first, const TPtr second);
void TreeToOrderedArray (const TPtr root, int *array, int *index);
int * merge (const int *array1, const int *array2, int start1, int end1, int start2, int end2);
int removeDuplicates(int *array, int dim);
void printArray(int *array, int dim);
bool isBST (const TPtr root);
int numNodes (const TPtr root);

int main ()
{
    int arrayOrd[9] = {3, 7, 10, 11, 12, 15, 21, 22, 25};
    int arrayOrdDue[9] = {30, 35, 46, 66, 78, 81, 85, 91, 93};
    int dim = sizeof(arrayOrd)/sizeof(arrayOrd[0]);
    int dimDue = sizeof(arrayOrdDue)/sizeof(arrayOrdDue[0]);
    
    TPtr albero = NULL;
    albero = fromOrderedArray(arrayOrd, 0, dim-1);
    TPtr alberoDue = NULL;
    alberoDue = fromOrderedArray(arrayOrdDue, 0, dimDue-1);
    
    int array[dim];
    int index = 0;
    TreeToOrderedArray (albero, array, &index);

    int arrayDue[dim];
    int indexDue = 0;
    TreeToOrderedArray (alberoDue, arrayDue, &indexDue);

    int *merged = merge(arrayDue, array, 0, dimDue, 0, dim);
    int k = removeDuplicates(merged, dim + dimDue);
    
    puts("Nuovo albero da i due fusi: ");
    TPtr result = fromOrderedArray(merged, 0, k-1);
    prettyTree(result);
    isBST(result) ? puts("Il nuovo albero è BST!") : puts("Il nuovo albero non è BST");
}

void insertNode (TPtr *root, int elemento)
{
    if(!*root){
        *root = malloc(sizeof(Tree));
        (*root)->info  = elemento;
        (*root)->left  = NULL;
        (*root)->right = NULL;
    } else if((*root)->info < elemento){
        insertNode(&(*root)->right, elemento);
    } else if((*root)->info > elemento) {
        insertNode(&(*root)->left, elemento);
    } else {
        puts("Valore duplicato. Pertanto non è stato inserito!");
    }
}

void inOrder (const TPtr root)
{
    if(!root){
        return;
    }
    inOrder(root->left);
    printf("%d ", root->info);
    inOrder(root->right);
}

void preOrder (const TPtr root)
{
    if(!root){
        return;
    }
    printf("%d ", root->info);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder (const TPtr root)
{
    if(!root){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->info);
}

void prettyTree (const TPtr root)
{
    if(!root){
        return;
    }
    level++;
    prettyTree (root->right);
    printf(" %*s%5d\n", level*5, "", root->info);
    prettyTree (root->left);
    level--;
}

TPtr fromOrderedArray (int *array, int start, int end)
{
    TPtr root = NULL;
    root = malloc(sizeof(Tree));
    int middle = (start + end) / 2;
    if(start - end >  0){
        return NULL;
    } else {
        root->info  = array[middle];
        
        root->left  = fromOrderedArray(array, start, middle - 1);
        root->right = fromOrderedArray(array, middle + 1, end);
        return root;
    }
}

bool BSTsareEqual (const TPtr first, const TPtr second){
    if(!first && !second){
        return true;
    } else if (first->info == second->info) {
        BSTsareEqual(first->left, second->left);
        BSTsareEqual(first->right, second->right);
    } else {
        return 0;
    }
}

void TreeToOrderedArray (const TPtr root, int *array, int *index)
{
    if(!root){
        return;
    }
    TreeToOrderedArray (root->left,  array, index);
    array[*index] = root->info;
    (*index)++;
    TreeToOrderedArray (root->right, array, index);
}

int * merge (const int *array1, const int *array2, int start1, int end1, int start2, int end2)
{   
    int left  = start1;
    int right = start2; 
    int index = 0;
    int *temp = (int*)malloc((end1 + end2) * sizeof(int));

    while(left < end1 && right < end2){
        if(array1[left] <= array2[right]){  
            temp[index++] = array1[left++];
        } else {
            temp[index++] = array2[right++];
        }
    }

    if(left == end1){
        while(right < end2){
            temp[index++] = array2[right++];
        }
    } else {
        while(left < end1){
            temp[index++] = array1[left++];
        }
    }
    return temp;
}

int removeDuplicates(int *array, int dim)
{
    int k = 1;

    //Rimuovo duplicati dall'array
    for (int i = 1; i < dim; i++){
        if(array[i] != array[i-1]){
            array[k++] = array[i];
        }
    }
    return k;
}

void printArray(int *array, int dim)
{
    for(size_t i = 0; i < dim; i++){
        printf("array[%lu] = %d ", i, array[i]);
        if(i != 0 && i % 4 == 0){
            puts("");
        }
    }
    puts("");
}

int numNodes (const TPtr root)
{
    if(!root){
        return 0;
    }

    return 1 + numNodes(root->left) + numNodes(root->right);
}

bool isBST (const TPtr root)
{
    if(!root){
        return false;
    }
    int test[numNodes(root)];
    int index = 0;
    TreeToOrderedArray(root, test, &index);
    for(size_t i = 0; i < index; i++){
        if(test[i] >= test[i+1]){
            return false;
        }
    }
    return true;
}