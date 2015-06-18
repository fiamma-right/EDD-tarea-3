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


struct btreenode *Treebuilding(float *, int *, int , int, float *, int *, int, int);
struct btreenode *cargar_arbol(char *);
struct btreenode *new_node(int, float);
void insert( struct btreenode **, int, float );
void delete( struct btreenode **, int );
void search( struct btreenode **, int, struct btreenode **, struct btreenode **, int * );
float buscar(struct btreenode **, int);
void guardar(struct btreenode *, char *);
int treesize(struct btreenode *);
void inordert(struct btreenode *, FILE *fp);
void postordert(struct btreenode *,FILE *fp);

int main(){
	FILE *fp, *fap;
	char cmd[257], par[257];
	int num; float val;
	struct btreenode *root = NULL;
	if ((fp = fopen("rutina.dat", "r")) == 0){
        	printf("Gomenne :c\nError al cargar el archivo rutina.dat\n");
        	return 1;
    	}
	fap = fopen("output.dat", "w"); /* No es necesario validar la apertura de este archivo, porque se crea */
	while(fscanf(fp, "%[^ \n]%*c", cmd)!= 0){
		if(strcmp("Cargar", cmd)==0){
			fscanf(fp, "%s\n", par);
			root = cargar_arbol(par);
			printf("hello world\n");
			if(root != NULL)
				fprintf(fap, "Onii-chan, Datos Cargados :3\n");
			else
				fprintf(fap, "Gomenne Onii-chan, no se pudieron cargar datos :C\n"); 
		}
		else if((strcmp("Agregar", cmd) == 0)){
			fscanf(fp, "Liceo %d|%f\n", &num , &val);
			insert(&root, num, val);
			fprintf(fap , "Omedetto, Onii-chan!!! Liceo %d Agregado\n", num);
		}
		else if((strcmp("Borrar", cmd)==0)){
			fscanf(fp, "Liceo %d\n", &num);
			delete( &root, num);
			fprintf(fap ,"Nani? Nande? Mazaka!! Liceo %d ha sido Eliminado!!!\n", num);
		}
		else if((strcmp("Puntaje", cmd)==0)){
			fscanf(fp, "Liceo %d\n", &num);
			val = buscar( &root, num); 
			fprintf(fap, "Puntaje Liceo %d : %f (Tryhard)\n", num, val);
		}
		else if((strcmp("Guardar", cmd)==0)){
			fscanf(fp, "%s", par);
			guardar(root, par);
			return 0;
		}
	}
	fclose(fap); fclose(fp); 
	return 0;
}

struct btreenode *new_node(int data, float val){
	struct btreenode* n = (struct btreenode*) malloc(sizeof(struct btreenode));
	n->data = data;
	n->val = val;
	n->rightchild = NULL;
	n->leftchild = NULL;
	return n;
}

struct btreenode *Treebuilding(float InOrder[],int inorderName[], int instart, int inend,float PostOrder[], int postorderName[], int poststart,int  postend){

	if (instart > inend || poststart > postend || poststart < 0 || instart < 0){
		return NULL;
		}
	int rootname = postorderName[postend];	
	struct btreenode* root = new_node(postorderName[postend],PostOrder[postend]); 
	int k=0;
	int i = instart;
	for (; i < inend; i++){
		if(inorderName[i] == rootname){
			k=i;
      			break;
		}
	}
	root->leftchild = Treebuilding(InOrder, inorderName, instart, k, PostOrder,postorderName, poststart, poststart+k-(instart+1));
	root->rightchild= Treebuilding(InOrder,inorderName, k+1, inend, PostOrder,postorderName, poststart+k-instart, postend-1);
  
  return root;
}

struct btreenode *cargar_arbol(char *nombre){
	FILE* file; int size, *inorderName, *postorderName;
	float *inorder, *postorder; int i;
	if ((file = fopen(nombre, "r")) == 0){
        	printf("THIS CAN NOT BE!!! ONII-CHAN!!! Error al cargar %s", nombre);
        	return NULL;
    }
	fscanf(file, "%d\n", &size);
	inorder = (float*)malloc(sizeof(float)*size);
	inorderName = (int*)malloc(sizeof(int)*size);
	postorder = (float*)malloc(sizeof(float)*size);
	postorderName = (int*)malloc(sizeof(int)*size);

	int instart = 0;
  	int inend = size-1;
  	int poststart = 0;
  	int postend = size -1;
  	
	for(i=0; i<size; i++){
		fscanf(file, "Liceo %d | %f\n", &postorderName[i],  &postorder[i]);
	}
	for(i=0; i<size ; i++){
		fscanf(file, "Liceo %d | %f\n", &inorderName[i],  &inorder[i]);
  	}
	fclose(file);

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
        printf ( "No se encontro nodo, pero por otro lado estos noodles estan deliciosos\n" ) ;
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

float buscar( struct btreenode **root, int num){
	struct btreenode *act;
	int found=FALSE;
	act = *root;
	float val;
	while(act != NULL){
		if( act-> data > num)
			act = act -> leftchild;
		else if (act -> data < num)
			act = act -> rightchild;
		else if(act-> data == num){
			found = TRUE;
			val = act->val;
			break;	
		}
	}
	if(found == FALSE)
		return -5000;
	return val;
}
int treesize(struct btreenode *node){
	if (node ==NULL)
		return 0;
	else
		return(treesize(node->leftchild) +1 + treesize(node->rightchild));
	
}
void inordert(struct btreenode *node, FILE *fp){
	if (node == NULL)
		return;
	inordert(node-> leftchild, fp);
	fprintf(fp,"Liceo %d | %f\n", node->data, node-> val);
	inordert(node->rightchild, fp);
}

void postordert(struct btreenode *node, FILE *fp){
	if (node == NULL)
		return;
	
	postordert(node->leftchild, fp);
	postordert(node-> rightchild, fp);
	fprintf(fp,"Liceo %d | %f\n", node->data, node-> val);	
	
}

void guardar(struct btreenode * root, char *nombre){
	FILE *fp;
	int size = 0;
	fp = fopen(nombre, "w");
	size = treesize(root);
	fprintf(fp, "%d\n", size);
	postordert(root, fp);
	inordert(root, fp);
	

}
