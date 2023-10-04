#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    struct node* next;
}
node_t;

void DOOM_THE_LIST(node_t* node) {
    if (node== NULL)
        return;
    DOOM_THE_LIST(node -> next);
    free(node);
}

void Add_first(node_t** head, int hvalue) {
    node_t * list_head = (node_t * ) malloc(sizeof(node_t));
    if (list_head == NULL) {
        DOOM_THE_LIST( * head);
        printf("Not enough memory for a new node");
        exit(EXIT_FAILURE);
    }
    list_head -> value = hvalue;
    list_head -> next =*head;
    * head = list_head;
}

void Add_last(node_t** head, int tvalue) {
    node_t* list_tail = (node_t*) malloc(sizeof(node_t));
    if (list_tail == NULL) {
        DOOM_THE_LIST( * head);
        printf("Not enough memory for a new node");
        exit(EXIT_FAILURE);
    }
    list_tail -> value = tvalue;
    list_tail -> next = NULL;
    if ( * head == NULL) {
        * head = list_tail;
        return;
    }
    node_t * node = * head;
    while (node -> next != NULL)
        node = node -> next;

    node -> next = list_tail;
}
void Delete_first(node_t ** head) {
    if ( * head == NULL)
        return;
    node_t * list_head = ( * head) -> next;
    free( * head);
    * head = list_head;
}
void Delete_last(node_t** head) {
    if ( * head == NULL)
        return;
    if ((*head)->next==NULL) {
        free(*head);

        *head=NULL;
        return;

    }
    node_t* node=* head;
    while (node->next->next)
        node=node->next;
    free(node->next);
    node->next=NULL;
}
void d_element(node_t ** head, int value_x) {
    node_t* nde;
    while (*head!=NULL)
        if ((*head)->value==value_x) {
            nde = (*head)->next;
            free(*head);
            *head=nde;
        }
    else break;
    if (*head==NULL)
        return;
    nde = *head;
    while (nde->next!=NULL) {
        if (nde -> next -> value == value_x) {
            node_t * a = nde -> next -> next;
            free(nde -> next);
            nde -> next = a;
        }

        nde = nde -> next;
    }

}
void print_all(FILE * file, node_t * head) {
    if (head == NULL)
        return;
    node_t * node = head;
    while (node != NULL) {
        fprintf(file, "%d ", node -> value);
        node = node -> next;
    }
    fprintf(file, "\n");
}
void print_f_x(FILE* file, node_t* head, int x) {
    node_t * node = head;
    int i;
    for (i = 0; i < x && node != NULL; i++) {

        fprintf(file, "%d ", node -> value);
        node = node -> next;
    }
    fprintf(file, "\n");
}
void print_l_x(FILE* file, node_t* head, int x) {
    if (head == NULL)
        return;
    node_t* node = head;
    int cnt = 0;
    while (node != NULL) {
        cnt++;
        node = node -> next;
    }
    node=head;
    while (cnt > x) {
        cnt--;
        node=node -> next;
    }
    while (node!=NULL) {
        fprintf(file, "%d ", node -> value);
        node = node -> next;
    }
    fprintf(file, "\n");
}
int main()
{
    FILE* input_file=fopen("input.dat","r");
    FILE* output_file=fopen("output.dat","w");
    node_t* head=NULL;
    char instruction[30];
    int x;
    while(fscanf(input_file, "%29s",instruction)!=EOF)
    {
        if(strcmp(instruction,"PRINT_L")==0)
        {
            fscanf(input_file,"%d",&x);
            print_l_x(output_file,head,x);
        }
        else if(strcmp(instruction,"PRINT_F")==0)
        {
            fscanf(input_file,"%d",&x);
            print_f_x(output_file,head,x);
        }
        else if(strcmp(instruction,"PRINT_ALL")==0)
        {
            print_all(output_file,head);
        }
        else if(strcmp(instruction,"DE")==0)
        {
            fscanf(input_file,"%d",&x);
            d_element(&head,x);
        }
        else if(strcmp(instruction,"DOOM_THE_LIST")==0)
        {
            DOOM_THE_LIST(head);
            head=NULL;
        }
        else if(strcmp(instruction,"DL")==0)
        {
            Delete_last(&head);
        }
        else if(strcmp(instruction,"DF")==0)
        {
            Delete_first(&head);
        }
        else if(strcmp(instruction,"AL")==0)
        {
            fscanf(input_file,"%d",&x);
            Add_last(&head,x);
        }
        else if(strcmp(instruction,"AF")==0)
        {
            fscanf(input_file,"%d",&x);
            Add_first(&head,x);
        }

    }
DOOM_THE_LIST(head);
fclose(input_file);
fclose(output_file);
    return 0;
}
