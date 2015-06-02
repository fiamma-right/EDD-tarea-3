#include <stdio.h>
#include <stlib.h>

typedef struct tnode{
  Node right;
  Node left; 
  float val;
  int nombre;
}Node;


Node BuildTree(int *InOrder, int *PostOrden);
Node Treebuilding(int *InOrder, int instart, int inend,int PostOrder,int poststart,int  postend );

int main(){
  return 0;
}

Node BuildTree(float *InOrder,int *inorderName, float *PostOrder,int *postorderName, int size){
  int instart = 0;
  int inend = size-1;
  int poststart = 0;
  int postend = size -1;
  return Node Treebuilding(InOrder, inorderName, instart, inend, PostOrder, postorderName, poststart, postend);
}

Node Treebuilding(float *InOrder,int *inorderName, float instart, int inend,int PostOrder, int *postorderName, int poststart,int  postend , ){ 
  if (instart > inend|| poststart > postend)
    return NULL;
  
  
  float rootvalue = PostOrder[postend];
  int rootname = postorderName[postend];
  Node *root = (Node*)malloc(sizeof(Node)); // Falta hacer que agregue el nombre del liceo al arbol
  root->val    = rootvalue;
  root->nombre = rootname;
  int k =0;
 
  for (int i=0; i < inend; i++){
    if(inorderName[i] == rootname){
      k=i;
      break;
    }
  }
  
  root->left = Treebuilding (InOrder, instart, k-1, PostOrder, poststart, poststart+k-(instart+1));
  root->right= Treebuilding (InOrder, k+1, inend, PostOrder, poststart+k-instart, postend);
  
  return root;
}

Node *Cargar_arbol(char *nombre){
  FILE* fp; int size, *inorderName, *postorderName;
  float *inorder, *postorder;
  char aux[8];
  Node *Root;
  fp = fopen(nombre, "r");
  fscanf(fp, "%d", &size);
  inorder = (float*)malloc(sizeof(float)*size);
  inorderName = (int*)malloc(sizeof(int)*size);
  postorder = (float*)malloc(sizeof(float)*size);
  postorderName = (int*)malloc(sizeof(int)*size);
  for(int i=0; i<size; i++){
    fscanf(fp, "Liceo %d | %f", inorderName[i],  inorder[i]);
  }
  for(int i=0; i<size; i++){
    fscanf(fp, "Liceo %d | %f", postorderName[i],  postorder[i]);
  }
Root = BuildTree(inorder, inorderName, postorder, postorderName);
return root;
  
}

Node *Borrar_nodo(int nom, Node *root){
  while(root->nombre != nom){
    if(root->)
  }
}

