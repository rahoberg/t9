//Rebecca Hoberg
//CSE 374 Winter 2013
//t9.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Node.h"
#include<ctype.h>
#define MAX_LINE 256

void build_array();
int* char_to_int(char* word);
Node build_trie(FILE* dict);
Node add_word(Node tree, char* word, int* code, int len);
void find_word(char* word, Node tree);
//void testadd();
int* conv_array;

int main(int argc, char** argv){
  if(argc<2){
    fprintf(stderr,"Insufficient arguments.\n");
    exit(1);
  }
  build_array();
  FILE* dict=fopen(argv[1],"r");
  if(dict==NULL){
    fprintf(stderr, "Filename is not valid.\n");
    exit(1);
  }
  Node tree=build_trie(dict);
  fclose(dict);
  FILE* f=fdopen(0,"r");
  char line[MAX_LINE];
  char* prevline=malloc(1);
  prevline[0]='\0';
  while(1){
    printf("Enter Key Sequence (or # for next word):\n");
    if(fgets(line,MAX_LINE,f)==NULL){
      free(prevline);
      freeTree(tree);
      free(conv_array);
      fclose(f);
      return 0;
    }
    //remove newline character
    line[strlen(line)-1]='\0';
    if(strcmp(line,"exit")==0){
      free(prevline);
      freeTree(tree);
      free(conv_array);
      fclose(f);
      return 0;
    }
    //if "#" is typed, add it onto the previous line and find that word
    if(strcmp(line, "#")==0){
      strcat(prevline,"#");
      find_word(prevline, tree);
    }
    else{
      find_word(line, tree);
      free(prevline);
      //copy line into prevline
      prevline=malloc(strlen(line)+2);
      strcpy(prevline,line);
    }
  }
  free(prevline);
  freeTree(tree);
  free(conv_array);
  fclose(f);
  return 0;
}

/*
char_to_int:
Takes a string, removes trailing newline character, and returns
 the corresponding integer array, whose
 length is the same as the word.
*/
int* char_to_int(char* word){
  int len=strlen(word);
  if(word[len-1]=='\n'){
    word[len-1]='\0';
    len--;
  }
  int* intarray=malloc(sizeof(int)*len);
  assert(intarray!=NULL);
  int i;
  for(i=0;i<len;i++){
    if(word[i]=='#'){
      intarray[i]=0;
    }
    else{
      intarray[i]=conv_array[toupper(word[i])];
    }
  }
  return intarray;
}

/*build_trie:
Builds the trie
*/
Node build_trie(FILE* dict){
  char line[MAX_LINE];
  Node tree=NULL;
  while(fgets(line, MAX_LINE, dict)!=NULL){
    int* code=char_to_int(line);
    int len=strlen(line);
    tree=add_word(tree, line, code, len);
    free(code);
  }
  return tree;
}

/* add_word:
Recursively adds the given word to the Node
*/
Node add_word(Node tree, char* word, int* code, int len){
  //if the tree is null, create one
  if(tree==NULL){
    tree=newNode(NULL);
    if(tree==NULL){
      fprintf(stderr,"malloc failed\n");
      exit(1);
    }
  }
  if(len==0){
    if(tree->word==NULL){
      tree->word=malloc(strlen(word)+1);
      strcpy(tree->word,word);
      return tree;
    }
    //if len ==0 but there is already a word there,
    // add the word to its index-0 child.
    else{
      Node child=(tree->nodes)[0];
      (tree->nodes)[0]=add_word(child, word, code, len);
      return tree;
    }
  }
  //else: if len>0
  int index=code[0];
  Node child=(tree->nodes)[index];
  (tree->nodes)[index]=add_word(child, word, code+1, len-1);
  return tree;
}

/*
find_word
Takes the user's input and prints the corresponding t9-onym
from the trie.
If there are no more t9-onyms, it prints a message
saying so.
*/
void find_word(char* word, Node tree){
  while(tree!=NULL && word[0]!='\0'){
    int index;
    if(word[0]=='#'){
      index=0;
    }
    else{
      index=(int)(word[0])-(int)'0';
    }
    if(index<0 || index>9){
      printf("Please enter a key sequence of integers or #.\n");
      return;
    }
    word++;
    tree=(tree->nodes)[index];
  }
  if(tree!=NULL && (tree->word)!=NULL){
    printf("%s\n",tree->word);
    return;
  }
  printf("There are no t9-onyms left to display.\n");
}

/*
build_array
Builds the conversion array
*/
void build_array(){
  int i;
  conv_array=(int*)malloc(sizeof(int)*((int)'Z'+1));
  for(i=(int)'A';i<(int)'D';i++){
    conv_array[i]=2;
  }
  for(i=(int)'D';i<(int)'G';i++){
    conv_array[i]=3;
  }
  for(i=(int)'G';i<(int)'J';i++){
    conv_array[i]=4;
  }
  for(i=(int)'J';i<(int)'M';i++){
    conv_array[i]=5;
  }
  for(i=(int)'M';i<(int)'P';i++){
    conv_array[i]=6;
  }
  for(i=(int)'P';i<(int)'T';i++){
    conv_array[i]=7;
  }
  for(i=(int)'T';i<(int)'W';i++){
    conv_array[i]=8;
  }
  for(i=(int)'W';i<(int)'Z'+1;i++){
    conv_array[i]=9;
  }
}

void testadd(){
  Node tree=NULL;
  int code[2];
  code[0]=2;
  code[1]=2;
  tree=add_word(tree,"ba",code,2);
  tree=add_word(tree,"ca",code, 2);
  printTree(tree);
}
