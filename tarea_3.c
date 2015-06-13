#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct btreenode{
  	struct btreenode *rightchild;
  	struct btreenode *leftchild; 
  	float val;
  	int data;
}Node;


struct btreenode* Treebuilding(float *, int *, int , int, float *, int *, int, int);
struct btreenode* cargar_arbol(char *);
struct btreenode* new_node(int, float);
void insert( struct btreenode **, int, float );
void delete( struct btreenode **, int );
void search( struct btreenode **, int, struct btreenode **, struct btreenode **, int * );
void buscar(struct btreenode **, int);

int main(){
	FILE *fp, *fap;
	char cmd[257], par[257];
	int num; float val;
	struct btreenode *root;
	root = NULL;
	if ((fp = fopen("rutina.dat", "r")) == 0){
        	printf("Error al cargar el archivo rutina.dat\n");
        	return 1;
    	}
	fap =fopen("output.dat", "w");
	while(fscanf(fp, "%[^ \n]", cmd)!= 0){
		if(strcmp("Cargar", cmd)==0){
			fscanf(fp, "%s", par);
			root = cargar_arbol(par);
			if(root != NULL)	
				fprintf(fap, "Datos Cargados\n");
			else
				fprintf(fap, "No se pudo cargar datos\n"); 
		}
		else if(strcmp("Agregar", cmd)){
			fscanf(fp, "Liceo %d|%f", &num, &val);
			insert(&root, num, val);
		}
		else if(strcmp("Borrar", cmd)){
			fscanf(fp, "Liceo %d", &num);
			delete( &root, num);
		}
		else if(strcmp("Puntaje", cmd)){
			fscanf(fp, "Liceo %d", &num);
			buscar( &root, num); 
		}
		else if(strcmp("Guardar", cmd)){
			fscanf(fp, "%s", par);
			return 0;
		}
	}
	  
	return 0;
}

struct btreenode* new_node(int data, float val){
	struct btreenode* n = (struct btreenode*) malloc(sizeof(struct btreenode));
	n->data = data;
	n->val = val;
	n->rightchild = NULL;
	n->leftchild = NULL;
	return n;
}

struct btreenode* Treebuilding(float InOrder[],int inorderName[], int instart, int inend,float PostOrder[], int postorderName[], int poststart,int  postend){
	int i;
	if (instart > inend|| poststart > postend){
		return NULL;
		}
	int rootname = postorderName[postend];	
	struct btreenode* root = new_node(postorderName[postend],PostOrder[postend]); 
	int k =0;
 
	for (i=0; i < inend; i++){
		if(inorderName[i] == rootname){
			k=i;
      		break;
    }
  }

	root->leftchild = Treebuilding (InOrder, inorderName, instart, k-1, PostOrder,postorderName, poststart, poststart+k-(instart+1));
	root->rightchild= Treebuilding (InOrder,inorderName, k+1, inend, PostOrder,postorderName, poststart+k-instart, postend);
  
  return root;
}

struct btreenode* cargar_arbol(char *nombre){
	FILE* fp; int size, *inorderName, *postorderName;
	float *inorder, *postorder; int i;
	if ((fp = fopen(nombre, "r")) == 0){
        	printf("Error al cargar %c", nombre);
        	return NULL;
    }
	fscanf(fp, "%d", &size);
	inorder = (float*)malloc(sizeof(float)*size);
	inorderName = (int*)malloc(sizeof(int)*size);
	postorder = (float*)malloc(sizeof(float)*size);
	postorderName = (int*)malloc(sizeof(int)*size);
	
	int instart = 0;
  	int inend = size-1;
  	int poststart = 0;
  	int postend = size -1;
  	
	for(i=0; i<size; i++){
		fscanf(fp, "Liceo %d | %f", &inorderName[i],  &inorder[i]);
	}
	for(i=0; i<size ; i++){
		fscanf(fp, "Liceo %d | %f", &postorderName[i],  &postorder[i]);
  	}
return Treebuilding(inorder, inorderName, instart, inend, postorder, postorderName, poststart, postend);
  
}

void delete ( struct btreenode **root, int num )
{
    int found ;
    struct btreenode *parent, *x, *xsucc ;

    /* si el arbol esta vacio */
if ( *root == NULL ){
        printf ( "\narbol vacio" ) ;
        return ;
    }

    parent = x = NULL ;

    /* usa la funcion search para encontrar el nodo a eliminar*/

    search ( root, num, &parent, &x, &found ) ;

    /* si no encuentra el nodo */
if ( found == FALSE ){
        printf ( "No se encontro nodo\n" ) ;
        return ;
    }

    /* si el nodo tiene 2 hijos */
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

    /* si el nodo no tiene hijos */
if ( x -> leftchild == NULL && x -> rightchild == NULL ){
        if ( parent -> rightchild == x )
            parent -> rightchild = NULL ;
        else
            parent -> leftchild = NULL ;

        free ( x ) ;
        return ;
    }

    /* si el nodo tiene solo hijo en la derecha */
if ( x -> leftchild == NULL && x -> rightchild != NULL ){
        if ( parent -> leftchild == x )
            parent -> leftchild = x -> rightchild ;
        else
            parent -> rightchild = x -> rightchild ;

        free ( x ) ;
        return ;
    }

    /* si el nodo tiene solo hijo en la izquierda */
if ( x -> leftchild != NULL && x -> rightchild == NULL ){
        if ( parent -> leftchild == x )
            parent -> leftchild = x -> leftchild ;
        else
            parent -> rightchild = x -> leftchild ;

        free ( x ) ;
        return ;
    }
}

void insert ( struct btreenode **sr, int num, float prom )
{
    if ( *sr == NULL ){
        *sr = malloc ( sizeof ( struct btreenode ) ) ;

        ( *sr ) -> leftchild = NULL ;
        ( *sr ) -> data = num ;
        ( *sr ) -> val = prom ; 
        ( *sr ) -> rightchild = NULL ;
    }
    else{
        if ( num < ( *sr ) -> data )
        	insert ( &( ( *sr ) -> leftchild ), num, prom );
        else
            insert ( &( ( *sr ) -> rightchild ), num, prom ) ;
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

void buscar( struct btreenode **root, int num){
	struct btreenode *act;
	int found=FALSE;
	act = *root;
	while(act != NULL){
		if( act-> data > num)
			act = act -> leftchild;
		else if (act -> data < num)
			act = act -> rightchild;
		else if(act-> data == num){
			found = TRUE;
			printf("Liceo %d: %f", act->data, act->val);		
		}
	if(found == FALSE)
		printf("Error: no existe Liceo %d", num);
	}
	return;
}

}
