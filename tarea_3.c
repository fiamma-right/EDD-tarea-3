#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct btreenode{
  	struct btreenode *rightchild;
  	struct btreenode *leftchild; 
  	float val;
  	int data;
}Node;


struct btreenode BuildTree( float *,int *, float *, int *, int);
struct btreenode Treebuilding(float *, int *, int , int, float *, int *, int, int);
void insert( struct btreenode **, int );
void delete( struct btreenode **, int );
void search( struct btreenode **, int, struct btreenode **, struct btreenode **, int * );

int main(){
	FILE* fp;
	char name[100], cmd[30], aux[10];
	while(
	  
	return 0;
}

struct btreenode BuildTree(float *InOrder,int *inorderName, float *PostOrder,int *postorderName, int size){
  	int instart = 0;
  	int inend = size-1;
  	int poststart = 0;
  	int postend = size -1;
  	return Treebuilding(InOrder, inorderName, instart, inend, PostOrder, postorderName, poststart, postend);
}

struct btreenode Treebuilding(float *InOrder,int *inorderName, int instart, int inend,float *PostOrder, int *postorderName, int poststart,int  postend){
	int i; 
	if (instart > inend|| poststart > postend)
		return ;
	float rootvalue = PostOrder[postend];
	int rootname = postorderName[postend];
	struct btreenode *root = (struct btreenode*)malloc(sizeof(struct btreenode)); 
	root->val    = rootvalue;
	root->data = rootname;
	int k =0;
 
	for (i=0; i < inend; i++){
		if(inorderName[i] == rootname){
		k=i;
      		break;
    }
  }

	*root->leftchild = Treebuilding (InOrder, inorderName, instart, k-1, PostOrder,postorderName, poststart, poststart+k-(instart+1));
	*root->rightchild= Treebuilding (InOrder,inorderName, k+1, inend, PostOrder,postorderName, poststart+k-instart, postend);
  
  return *root;
}

struct btreenode *Cargar_arbol(char *nombre){
	FILE* fp; int size, *inorderName, *postorderName;
	float *inorder, *postorder; int i;
	struct btreenode *root;
	fp = fopen(nombre, "r");
	fscanf(fp, "%d", &size);
	inorder = (float*)malloc(sizeof(float)*size);
	inorderName = (int*)malloc(sizeof(int)*size);
	postorder = (float*)malloc(sizeof(float)*size);
	postorderName = (int*)malloc(sizeof(int)*size);
	for(i=0; i<size; i++){
		fscanf(fp, "Liceo %d | %f", &inorderName[i],  &inorder[i]);
	}
	for(i=0; i<size; i++){
		fscanf(fp, "Liceo %d | %f", &postorderName[i],  &postorder[i]);
  	}
	*root = BuildTree(inorder, inorderName, postorder, postorderName, size);
return root;
  
}

void delete ( struct btreenode **root, int num )
{
    int found ;
    struct btreenode *parent, *x, *xsucc ;

    /* if tree is empty */
if ( *root == NULL ){
        printf ( "\nTree is empty" ) ;
        return ;
    }

    parent = x = NULL ;

    /* call to search function to find the node to be deleted */

    search ( root, num, &parent, &x, &found ) ;

    /* if the node to deleted is not found */
if ( found == FALSE ){
        printf ( "\nData to be deleted, not found" ) ;
        return ;
    }

    /* if the node to be deleted has two children */
if ( x -> leftchild != NULL && x -> rightchild != NULL ){
        parent = x ;
        xsucc = x -> rightchild;

        while ( xsucc -> leftchild != NULL ){
            parent = xsucc ;
            xsucc = xsucc -> leftchild ;
        }

        x -> data = xsucc -> data ;
        x = xsucc ;
    }

    /* if the node to be deleted has no child */
if ( x -> leftchild == NULL && x -> rightchild == NULL ){
        if ( parent -> rightchild == x )
            parent -> rightchild = NULL ;
        else
            parent -> leftchild = NULL ;

        free ( x ) ;
        return ;
    }

    /* if the node to be deleted has only rightchild */
if ( x -> leftchild == NULL && x -> rightchild != NULL ){
        if ( parent -> leftchild == x )
            parent -> leftchild = x -> rightchild ;
        else
            parent -> rightchild = x -> rightchild ;

        free ( x ) ;
        return ;
    }

    /* if the node to be deleted has only left child */
if ( x -> leftchild != NULL && x -> rightchild == NULL ){
        if ( parent -> leftchild == x )
            parent -> leftchild = x -> leftchild ;
        else
            parent -> rightchild = x -> leftchild ;

        free ( x ) ;
        return ;
    }
}

void insert ( struct btreenode **sr, int num )
{
    if ( *sr == NULL )
    {
        *sr = malloc ( sizeof ( struct btreenode ) ) ;

        ( *sr ) -> leftchild = NULL ;
        ( *sr ) -> data = num ;
        ( *sr ) -> rightchild = NULL ;
    }
    else/* search the node to which new node will be attached */

    {
        /* if new data is less, traverse to left */
if ( num < ( *sr ) -> data )
            insert ( &( ( *sr ) -> leftchild ), num ) ;
        else/* else traverse to right */

            insert ( &( ( *sr ) -> rightchild ), num ) ;
    }
}

void search ( struct btreenode **root, int num, struct btreenode **par, struct
        btreenode **x, int *found )
{
    struct btreenode *q ;

    q = *root ;
    *found = FALSE ;
    *par = NULL ;

    while ( q != NULL )
    {
        /* if the node to be deleted is found */
if ( q -> data == num )
        {
            *found = TRUE ;
            *x = q ;
            return ;
        }

        *par = q ;

        if ( q -> data > num )
            q = q -> leftchild ;
        else
            q = q -> rightchild ;
    }
}
