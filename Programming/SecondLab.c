#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 


struct node{
    int data;
    struct node *next;
};
typedef struct node strnode;




void *addNode(int dat,strnode **head){
    strnode *new_node = (strnode*)(malloc(sizeof(strnode)));
    new_node->data = dat;
    new_node->next = NULL;

    if (*head == NULL) 
    {
    *head = new_node;
    }
    else
    {


        struct node *last = *head;
        while (last->next != NULL) {
            last = last->next;
            
        }
        last->next = new_node;
    }
}


void printer(struct node *head){
    strnode *current = head;
    while (current != 0){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
int main(){
    struct node *head = NULL;
    int input,repeats;
    scanf("%d",&input);
    while(input!=0){
        addNode(input,&head);
        scanf("%d",&input);
    }
    printer(head);
}