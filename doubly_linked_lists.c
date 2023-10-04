#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type {
    int value;
    struct node_type* next;
    struct node_type* prev;
}node_t;

#define HEAD sentinel->next
#define TAIL sentinel->prev

void d_first(node_t* sentinel){
    if(HEAD == NULL)
        return;
    node_t* node= HEAD;
    HEAD=node->next;
    if(HEAD !=NULL){
        HEAD->prev= NULL;
    }
    if (node == TAIL){
        TAIL=NULL;
    }
    free(node);
}

void d_last (node_t* sentinel){
    if (TAIL == NULL)
        return;
    node_t* node= TAIL;
    TAIL=node->prev;
    if(TAIL !=NULL)
        TAIL ->next = NULL;

    if (node == HEAD)
        HEAD=NULL;

    free(node);
}


void DOOM_THE_LIST(node_t* sentinel) {
    while (HEAD != NULL)
        d_first(sentinel);
    HEAD=TAIL=NULL;
}


void Add_first(node_t* sentinel, int hvalue) {
    node_t * list_head = (node_t * ) malloc(sizeof(node_t));
    if (list_head == NULL) {
        DOOM_THE_LIST(sentinel);
        printf("Not enough memory for a new node");
        exit(EXIT_FAILURE);
    }

    list_head -> value = hvalue;
    list_head -> next = HEAD;
    list_head -> prev = NULL;
    if (HEAD != NULL)
        HEAD -> prev= list_head;
    HEAD = list_head;
    if (TAIL == NULL)
        TAIL = list_head;
}

void Add_last(node_t* sentinel, int tvalue) {
    node_t * list_tail = (node_t * ) malloc(sizeof(node_t));
    if (list_tail == NULL) {
        DOOM_THE_LIST(sentinel);
        printf("Not enough memory for a new node");
        exit(EXIT_FAILURE);
    }

    list_tail -> value = tvalue;
    list_tail -> prev = TAIL;
    list_tail->next = NULL;
    if (TAIL != NULL)
        TAIL -> next= list_tail;
    TAIL = list_tail;
    if (HEAD == NULL)
        HEAD = list_tail;
}

void d_element(node_t* sentinel, int value_x)
{
    node_t* nde;
    while(HEAD != NULL)
        if (HEAD->value==value_x)
            d_first(sentinel);
        else break;

    nde=HEAD;
    while(nde !=NULL)
    {
        if(nde->value==value_x)
        {
            node_t* a=nde->next->next;
            a->prev=nde->prev;
            nde->prev-> next=a;
            free(nde->next);

        }

        nde=nde->next;
    }


}
void print_all(FILE* file, const node_t sentinel)
{
    if(sentinel.next == NULL)
        return;

    fprintf(file,"%d", sentinel.next->value);

    node_t* node=sentinel.next->next;
    while (node!=NULL)
    {
        fprintf(file," %d", node->value);
        node=node->next;
    }
    fprintf(file, "\n");
}
void print_f_x(FILE* file, const node_t sentinel, int x)
{
    if(sentinel.next == NULL)
        return;

    node_t* node=sentinel.next->next;
    int i;

    fprintf(file,"%d", sentinel.next-> value);

    for(i=1; i<x && node!=NULL ;i++)
    {

        fprintf(file," %d", node->value);
        node=node->next;
    }
    fprintf(file, "\n");
}
void print_l_x(FILE* file, node_t sentinel, int x)
{
    node_t* node=sentinel.prev;

    int cnt=1;

    while(node -> prev !=NULL && cnt < x)
    {
        cnt++;
        node=node->prev;
    }

    fprintf(file,"%d", node->value);
    node=node->next;

    while (node!=NULL)
    {
        fprintf(file," %d", node->value);
        node=node->next;
    }
    fprintf(file, "\n");
}













int main(int argc, char** argv)
{
    if (argc < 3 )
        return 0;
    FILE* input_file=fopen(argv[1],"r");
    FILE* output_file=fopen(argv[2],"w");
    node_t sentinel={.next=NULL,.prev=NULL};
    char instruction[30];
    int x;
    while(fscanf(input_file, "%29s",instruction)!=EOF)
    {
        if(strcmp(instruction,"PRINT_L")==0)
        {
            fscanf(input_file,"%d",&x);
            print_l_x(output_file,sentinel,x);
        }
        else if(strcmp(instruction,"PRINT_F")==0)
        {
            fscanf(input_file,"%d",&x);
            print_f_x(output_file,sentinel,x);
        }
        else if(strcmp(instruction,"PRINT_ALL")==0)
        {
            print_all(output_file,sentinel);
        }
        else if(strcmp(instruction,"DE")==0)
        {
            fscanf(input_file,"%d",&x);
            d_element(&sentinel,x);
        }
        else if(strcmp(instruction,"DOOM_THE_LIST")==0)
        {
            DOOM_THE_LIST(&sentinel);
        }
        else if(strcmp(instruction,"DL")==0)
        {
            d_last(&sentinel);
        }
        else if(strcmp(instruction,"DF")==0)
        {
            d_first(&sentinel);
        }
        else if(strcmp(instruction,"AL")==0)
        {
            fscanf(input_file,"%d",&x);
            Add_last(&sentinel,x);
        }
        else if(strcmp(instruction,"AF")==0)
        {
            fscanf(input_file,"%d",&x);
            Add_first(&sentinel,x);
        }
    }
    DOOM_THE_LIST(&sentinel);
    fclose (input_file);
    fclose (output_file);
    return 0;
}
