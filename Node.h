//Header File for Node.c
#ifndef NODE_H
#define NODE_H

struct Node_s{
  struct Node_s* nodes[10];
  char* word;
};
typedef struct Node_s* Node;

Node newNode(char* word);
void printTree(Node myNode);
void freeTree(Node myNode);

#endif
