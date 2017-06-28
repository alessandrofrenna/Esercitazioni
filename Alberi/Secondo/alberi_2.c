#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

struct node {
    char string[MAX];
    struct node *left;
    struct node *right;
};

typedef struct node Tree;
typedef Tree *TreePtr;

void inserisciNodo (TreePtr *root, char *string);
void inOrder (const TreePtr root);
void preOrder (const TreePtr root);
void postOrder (const TreePtr root);
TreePtr treeFromString (char *string);

int main ()
{
    char string[MAX];
    char *token;
    char *delimiter = " ";
    puts("Stringa: ");
    fgets(string, MAX, stdin);
    TreePtr root = treeFromString(string);
    puts("Printing the tree in order:");
    inOrder(root);
    puts("");
    puts("Printing the tree in preorder:");
    preOrder(root);
    puts("");
    puts("Printing the tree in postorder:");
    postOrder(root);
    puts("");
}

void inserisciNodo (TreePtr *root, char *string)
{
    if(!*root){
        *root = malloc(sizeof(Tree));
        strcpy((*root)->string, string);
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else {
        if(strcmp)
        if(strcmp((*root)->string, string) > 0){
            inserisciNodo(&(*root)->left, string);
        } else if (strcmp((*root)->string, string) < 0) {
            inserisciNodo(&(*root)->right, string);
        } else {
            puts("No double entries allowed!");
        }
    }
}

void inOrder (const TreePtr root)
{
    if(!root){
        return;
    }
    inOrder(root->left);
    printf("%s ", root->string);
    inOrder(root->right);
}

void preOrder (const TreePtr root)
{
    if(!root){
        return;
    }
    printf("%s ", root->string);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder (const TreePtr root)
{
    if(!root){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%s ", root->string);
}

TreePtr treeFromString (char *string)
{
    TreePtr root = NULL;
    char *delimiter = " ";

    char *token = strtok(string, delimiter);

    while(token){
        int len = strlen(token);
        if(token[len-1] == '\n') {
            token[len-1] = '\0';
        }
        inserisciNodo(&root, token);
        token = strtok(NULL, delimiter);
    }

    return root;
}