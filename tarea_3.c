#include <stdio.h>
#include <stlib.h>

typedef struct tnode{
  Node right;
  struct next; // arreglar struct
  float val;
  char nombre[8];
}Node;


Node BuildTree(int *InOrder, int *PostOrden);
Node Treebuilding(int *InOrder, int instart, int inend,int PostOrder,int poststart,int  postend );

int main(){
  return 0;
}

Node BuildTree(int *InOrder, int *PostOrder, int size){
  int instart = 0;
  int inend = size-1;
  int poststart = 0;
  int postend = size -1;
  return Node Treebuilding(InOrder, instart, inend, PostOrder, poststart, postend);
}

Node Treebuilding(int *InOrder, int instart, int inend,int PostOrder,int poststart,int  postend , ){ 
  if (instart > inend|| poststart > postend)
    return NULL;
  
  
  int rootvalue = PostOrder[postend];
  Node *root = (Node*)malloc(sizeof(Node)); // Falta hacer que agregue el nombre del liceo al arbol
  root.val    = rootvalue;
  root.nombre =  ;
  int k =0;
 
  for (int i=0; i < inend; i++){
    if(InOrder[i] == rootvalue){
      k=i;
      break;
    }
  }
  
  root.left = Treebuilding (InOrder, instart, k-1, PostOrder, poststart, poststart+k-(instart+1));
  root.right= Treebuilding (InOrder, k+1, inend, PostOrder, poststart+k-instart, postend);
  
  return root;
}

Node Cargar_arbol(char *nombre){
  FILE* fp; int size;
  fp = fopen(nombre, "r");
  fscanf(fp, "%d", &size);
  for(int i=0; i<size; i++){
    
  }
}

