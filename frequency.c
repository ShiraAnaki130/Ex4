#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define NUM_LETTERS 26
typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct _node{
char letter;
long unsigned int count;
struct _node* children[NUM_LETTERS];
}node;
typedef struct _TRIE{
    node* root;
}TRIE;
// function which create a node with the given char.
node* addNode(char c){
    node* n=(node*)malloc(sizeof(node));
    n->letter=c;
    n->count=0;
    for(int i=0;i<NUM_LETTERS;i++){
        n->children[i]=NULL;
    }
    return n;
}
boolean isLeaf(node* n){
    if(n==NULL) return FALSE;
    for(int i=0;i<NUM_LETTERS;i++){
        if(n->children[i]!=NULL){return FALSE;}
    }
    return TRUE;
}
int insertion_trie(node* p){
    int index=0;
    int max=0;
    int count_char=0;
    char c=getc(stdin);
    node* temp=p;
    while(c!=EOF){
        if(c!='\t'&&c!=' '&&c!='\n'&&((c>=65&&c<=90)||(c>=97&&c<=122))){
            count_char++;
            if(c>=65&&c<=90){c=tolower(c);}
            index=(int)(c-'a');
            if(temp->children[index]==NULL){
                temp->children[index]=addNode(c);
                if(temp->children[index]==NULL){
                    printf("Eror in creating a node.\n");
                    return -1;
                }
            }
            temp=temp->children[index];
            c=getc(stdin);
            if(!((c>=65&&c<=90)||(c>=97&&c<=122))){
                while(c!='\t'&&c!=' '&&c!='\n'&&c!=EOF&&(!((c>=65&&c<=90)||(c>=97&&c<=122)))){c=getc(stdin);}
            }
            if(c=='\t'||c==' '||c=='\n'||c==EOF){
                if(count_char>max){max=count_char;}
                count_char=0;
                temp->count=temp->count+1;
            }
        }
        else{
            temp=p;
            c=getc(stdin);
        }
    }
    return max;
}
void print_up(node* root,char* word, int index){
    if(isLeaf(root)){
        if(root->letter!='A'){
            *(word+index)='\0';
            printf("%s %ld\n", word, root->count);
        }
        return;
    }
    for(int i=0; i<NUM_LETTERS;i++){
        if(root->children[i]!=NULL){
            if(root->count!=0){
                *(word+index)='\0';
                printf("%s %ld\n", word, root->count);
            }
            *(word+index)=root->children[i]->letter;
            print_up(root->children[i], word, index+1);
        }
    }
}
void print_down(node* root,char* word, int index){
    if(isLeaf(root)){
        if(root->letter!='A'){
            *(word+index)='\0';
            printf("%s %ld\n", word, root->count);
        }
        return;
    }
    for(int i=NUM_LETTERS-1; i>=0;i--){
        if(root->children[i]!=NULL){
            *(word+index)=root->children[i]->letter;
            print_down(root->children[i], word, index+1);
            if(root->count!=0){
                *(word+index)='\0';
                printf("%s %ld\n", word, root->count);
            }
        }
    }
}
node* free_tree(node* root){
    for(int i=0;i<NUM_LETTERS;i++){
        if(root->children[i]!=NULL){
            root->children[i]=free_tree(root->children[i]);
        }  
    }
    free(root);
    return NULL;
}
int main(int argc, char *argv[]){
    TRIE* trie=(TRIE*)malloc(sizeof(TRIE));
    if(trie==NULL){
        printf("Eror in creating the TRIE.\n");
        return 0;
    }
    trie->root=addNode('A');
    node* root=trie->root;
    int max=insertion_trie(root);
    if(max==-1){
        root=free_tree(root);
    }
    else{
        max++;
        char* word=(char*)malloc(sizeof(char)*max);
        if(argc==1){
            print_up(root,word,0);
        }
        else if(argc==2){
            print_down(root,word,0);
        }
        root=free_tree(root);
        free(word);
        word=NULL;
    }
    free(trie);
    trie=NULL;
    return 0;
}
