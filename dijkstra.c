#include <stdio.h>
#include <stdlib.h>

int matrix[100][100]= {0};
void path(FILE* outfile, int parent[], int startn, int endn)
{
    if(startn != endn)
    {
        path(outfile, parent, startn, parent[endn]);

    }
    fprintf(outfile, "%d ", endn);
}
void dijkstra (FILE* outfile, int startn, int endn)
{
    int weight[100][100], distance[100], visited[100], parent[100];
    int i,j,mindist,nextn;
    for (i=0; i<100; i++)
    {
        for (j=0; j<100; j++)
        {
            if( matrix [i][j] != 0)
                weight[i][j] = matrix[i][j];
            else
                weight[i][j]=9999;

        }
    }

    for (i=0; i<100; i++)
    {
        distance[i]=weight[startn][i];
        parent[i]=startn;
        visited[i]=0;
    }
    distance[startn]=0;
    visited[startn]=1;

    for(j=0; j<99; j++)
    {
        mindist=9999;
        for(i=0; i<100; i++)
        {
            if (distance[i]<mindist && visited[i]==0)
            {
                mindist=distance[i];
                nextn=i;
            }
        }
        visited[nextn]=1;

        for(i=0; i<100; i++)
        {
            if(visited[i]==0 && mindist+weight[nextn][i]<distance[i])
            {
                distance[i] = mindist+weight[nextn][i];
                parent[i]=nextn;
            }
        }
    }
if(distance[endn] ==9999)
    fprintf(outfile, "path from  %d to %d does not exist\n", startn, endn);
else
{
     fprintf(outfile, "distsance from  %d to %d is %d\n", startn, endn, distance [endn]);
     path(outfile,parent, startn, endn);
}

}











int main()
{
    FILE* infile = fopen("infile.txt","r"), * outfile = stdout;

    char line[20];
    int x,y,z;
    while(fgets (line, 19, infile) != NULL)
    {
        sscanf(line, "%d,%d=%d", &x, &y, &z);
        matrix[x][y]=z;

    }
    dijkstra(outfile, 1, 7);
    return 0;
}
