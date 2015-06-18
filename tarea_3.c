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

/*****
*   int main
******
*   La función main ejecuta las rutinas principales del programa de acuerdo
    al orden de acceso de comandos entregados por el archivo de rutina.dat,
    en caso de no existir esta imprime un error y retorna 1 para notificar al
    programador de que existe un problema, en caso de que el archivo exista lo
    carga y crea el archivo output.dat donde registrará los progresos de las rutinas
    de acuerdo a lo que indica rutinas.dat llamando a las funciones auxiliares dentro del main.
******
*   Input:
*       None
*        .......
******
*   Returns:
*       int{
  0 si es exitoso
  1 si es fallido  
} 
*****/

int main(){
	FILE *fp, *fap;
	char cmd[257], par[257];
	int num; float val;
	struct btreenode *root;
	root = NULL;
	fp = fopen("rutina.dat", "r");
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

/*****
*
    struct btreenode* new_node()
******
*
    Función que a partir de los valores int y floats entregados
    reserva el espacio necesario a raíz del tamaño del tipo struct btreenode
    para luego asignar los valores entregados a la función a los parámetros del TDA
    definiendo así un nodo con sus valores preset determinados y los entregados
******
*
Input:
*
    int data : Numero de Liceo
    float val : Puntaje del Liceo
*
.......
******
*
Returns:
*
    struct btreenode*, Puntero que tiene asignado la locación en memoria del nodo recién creado.
*****/

struct btreenode* new_node(int data, float val){
	struct btreenode* n = (struct btreenode*) malloc(sizeof(struct btreenode));
	n->data = data;
	n->val = val;
	n->rightchild = NULL;
	n->leftchild = NULL;
	return n;
}

/*****
*
    struct btreenode* Treebuilding()
******
*
    La función construye un arbol con los datos almacenados
    en un arreglo de ints o floats (dependiendo de si es el cod. del liceo o el puntaje)
    para luego reconstruirlo utilizando un algoritmo de reconstrucción que hace el proceso
    inverso a ambos recorridos combinados, manteniendo así el orden original del arbol.
******
*
Input:
*
    float InOrder : Almacena los puntajes del recorrido in order
    int inorderName : Almacena los codigos de los liceos en in order
    int instart : Instancia en que inicia el in order
    int inend : Instancia en que termina el in order
    float PostOrder : Almacena los puntajes del recorrido en post orden
    int postorderName : Almacena los codigos de los liceos en post order
    int poststart : Instancia en que inicia el post orden
    int postend : Instancia en que termina el post orden
*
.......
******
*
Returns:
*
    struct btreenode*, La raíz del arbol recién creado.
*****/

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

/*****
*
    struct btreenode* cargar_arbol
******
*
    Recibe el nombre del archivo que ordena al arbol en forma in orden y post orden
    luego los almacena en arreglos para luego asignar las variables de iniciacion
    que se entregarán a la función anterior ya descrita, la cual será el retorno.
******
*
Input:
*
    char *nombre : Puntero con el string que es el nombre del archivo que contiene los recorridos del arbol
*
.......
******
*
Returns:
*
    struct btreenode*, Puntero a la raíz del arbol final reconstruido
*****/

struct btreenode* cargar_arbol(char *nombre){
	FILE* fp; int size, *inorderName, *postorderName;
	float *inorder, *postorder; int i;
	fp = fopen(nombre, "r");
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

/*****
*
    void delete
******
*
    Utilizando el algoritmo de deleción para un arbol binario
    elimina un nodo reemplazandolo por el menor de los mayores
    mas próximo (hoja)
******
*
Input:
*
    struct btreenode **root : Arbol que contiene la información
    int num : Código del liceo a eliminar
*
.......
******
*
Returns:
*
    No retorna.
*****/

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

/*****
*
    void insert
******
*
    De forma recursiva verifica si los valores a insertan en el ABB
    son menores o mayores para tratar de insertar en el nodo como hoja
    según corresponda.
******
*
Input:
*
    struct btreenode **sr : Recibe el nodo raíz del arbol
    int num : Recibe el Código del Liceo a ingresar
    float prom : Recibe el Puntaje del Liceo a ingresar
*
.......
******
*
Returns:
*
    No tiene
*****/

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

/*****
*
    void search
******
*
    Función auxiliar a delete que permite identificar cual nodo es el que se tiene
    que eliminar para luego poder ejecutar de forma mas comoda la función delete
******
*
Input:
*
    struct btreenode **root : Nodo raíz del arbol
    struct btreenode **par : Puntero auxiliar global del tipo struct btreenode
    struct btreenode **x : Puntero auxiliar global del tipo struct btreenode
    int num : Código del Liceo que se quiere buscar
    int *found : Boolean value
*
.......
******
*
Returns:
*
    None
*****/

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

/*****
*
    void buscar
******
*
    Función que busca si existe un liceo dentro del arbol
    para printearle al usuario si es así o no utilizando
    una busqueda sencilla en ABB
******
*
Input:
*
    struct btreenode **root : Nodo raíz del arbol
    int num : Código del Liceo a buscar
*
.......
******
*
Returns:
*
    None
*****/

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
