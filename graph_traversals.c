#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    int value;
    struct node* next;
}node_t;

typedef struct queue{
    node_t* first;
    node_t* last;

} queue_t;

int matrix[99][99]={0};

void read (FILE* infile)
{
    char line [999];
    fgets(line, 998, infile);
    fgets(line, 998, infile);
    int i=7;
    int x,y;
    while(line[i]!='\0')
    {
       sscanf(&line[i], "(%d%d)", &x, &y);
       matrix[x][y] = 1;
       i++;
       while (line[i] != '\0' && line [i] != '(')
            i++;

    }

}




int deq (queue_t* queue){
    if(queue->first == NULL)
        return 0;
    int value = queue -> first-> value;
    node_t* node = queue-> first;
    queue -> first = queue-> first -> next;
    free(node);
    return value;
}

void DOOM_THE_QUEUE(queue_t* queue) {
    while (queue->first != NULL)
        deq (queue);
    queue->first = queue -> last =NULL;
}

void enq (queue_t* queue, int value) {
    node_t * node = (node_t * ) malloc(sizeof(node_t));
    if (node == NULL) {
        DOOM_THE_QUEUE (queue);
        printf("Not enough memory for a new node");
        exit(EXIT_FAILURE);
    }
    node-> value = value;
    node -> next = NULL;
    if (queue -> first == NULL)
        queue -> first = node;
    else
        queue-> last -> next = node;
    queue-> last = node;
}

int visited[100]={0};

void bfs (FILE* outfile, int startbfs)

{
    queue_t Q = {NULL, NULL};

    enq(&Q, startbfs);
    visited[startbfs]=1;
    while ( Q. first != NULL)
    {
        int temp;
        temp = deq(&Q);
        fprintf(outfile, "%d ",temp  );
        for(int i= 0 ; i<99; i++)
        {
            if (matrix[temp][i] == 1 && visited[i]==0)
                {
                enq(&Q, i);
                visited[i]=1;
                }
        }
    }
fprintf(outfile, "\n");
DOOM_THE_QUEUE(&Q);


}

void dfs (FILE* outfile, int startdfs)

{
fprintf(outfile, "%d ", startdfs);
visited[startdfs]=1;
;
for(int i= 0 ; i<99; i++)
        {
            if (matrix[startdfs][i] == 1 && visited[i]==0)
                {
                dfs(outfile, i);

                }
        }

}







int main(int argc, char** argv)
{
    FILE* infile =fopen (argv[1],"r");
    FILE* outfile =fopen (argv[2],"w");
    read(infile);
    if(strcmp(argv[3] ,"depth")==0)
        dfs(outfile, 1);
    else
        bfs(outfile, 1);





    fclose(infile);
    fclose(outfile);
}
