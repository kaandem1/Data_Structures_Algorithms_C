#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int money,time;
}pair;

typedef struct node {
    pair value;
    struct node* next;
}node_t;

typedef struct queue{
    node_t* first;
    node_t* last;

} queue_t;

pair pop (queue_t* queue){
    if(queue->first == NULL)
        return (pair){0,0};
    pair value = queue -> first-> value;
    node_t* node = queue-> first;
    queue -> first = queue-> first -> next;
    free(node);
    return value;
}

void DOOM_THE_QUEUE(queue_t* queue) {
    while (queue->first != NULL)
        pop (queue);
    queue->first = queue -> last =NULL;
}
void push (queue_t* queue, pair value) {
    node_t * node = (node_t * ) malloc(sizeof(node_t));
    if (node == NULL) {
        DOOM_THE_QUEUE (queue);
        printf("Not enough memory for a new node");
        exit(EXIT_FAILURE);
    }
    if (node != NULL)
    node-> value = value;
    node -> next = NULL;
    if (queue -> first == NULL)
        queue -> first = node;
    else
        queue-> last -> next = node;
    queue-> last = node;
}

pair peek (queue_t* queue){
    if(queue->first == NULL)
        return (pair){0,0};
    return queue -> first-> value;
}
int main(int argc, char** argv){
    if (argc < 3)
        return 0;
    FILE* input_file=fopen(argv[1], "r");
    FILE* output_file=fopen(argv[2], "w");
    queue_t queue = { .first = NULL , .last = NULL };
    char string [100];
    fgets (string, 99,input_file);
    int nb_times =0;

    for (int i=0; i<strlen(string); i++)
        if (string[i] ==' ')
            nb_times++;

    int* array= (int*)malloc(nb_times* sizeof(int));
    nb_times=0;
    char* p =string;

    while(p[0] !='\0'){
        array[nb_times++]=atoi(p);

        while (p[0] >= '0' && p[0] <= '9')
                p++;
        p++;

    }
    int money, time;
    while (fscanf (input_file, "%99s %d %d", string, &money, &time) != EOF)
        push(&queue,(pair){money,time});
    money = time = 0;
    int i=0;

    while (i< nb_times){
        if (array[i] >= time+ peek (&queue).time && queue.first != NULL){
            pair value = pop (&queue);
            time += value.time;
            money += value.money;
        }
        else fprintf(output_file, "After %d seconds: %d\n", array[i++], money);

    }
    DOOM_THE_QUEUE(&queue);
    free(array);
    fclose(input_file);
    fclose(output_file);
}
