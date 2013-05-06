//Rebecca Hoberg
//CSE 374 Winter 2013
//Node.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Node.h"

/*struct Node_s{
  struct Node_s* nodes[10];
  char* word;
};
typedef struct Node_s* Node;
*/

/*newNode:
Returns a Node with the given word and a nodelist of NULL nodes
*/
Node newNode(char* word){
  Node myNode=(Node)malloc(sizeof(struct Node_s));
  myNode->word=word;
  int i;
  for(i=0; i<10; i++){
    (myNode->nodes)[i]=NULL;
  }
  return myNode;
}

/*freeTree
frees the Node and all of its children.
*/
void freeTree(Node myNode){
  if(myNode==NULL){
    return;
  }
  int i;
  for(i=0;i<10;i++){
    freeTree((myNode->nodes)[i]);
  }
  free(myNode);
}

void printTree(Node myNode){
  if(myNode==NULL){
    printf("NULL\n");
    return;
  }
  printf("Word: %s\n", myNode->word);
  printf("Node list:\n");
  int i;
  for(i=0;i<10;i++){
    printf("i= %d ",i);
    printTree((myNode->nodes)[i]);
  }
}

