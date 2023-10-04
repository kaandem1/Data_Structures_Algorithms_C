#include <stdio.h>
#include <stdlib.h>

int matrix[99][99]={0};

int node [99]= {0};
int nb_n_sub=0;

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
    fgets(line, 998, infile);
    i=9;
    while(line[i]!='\0')
    {
       sscanf(&line[i], "%d", &x);
       node[nb_n_sub]=x;
       nb_n_sub++;
       while (line[i] != '\0' && line[i] !=' ')
        i++;
       if (line[i] == ' ')
        i++;



    }


}

void print (FILE* outfile)
{
    fprintf(outfile, "V' arcs ");
    int i,j;
    for(i=0 ; i<nb_n_sub ; i++)
        for (j=0; j<nb_n_sub ; j++)
    if(matrix[node[i]][node[j]]!= 0)
        fprintf(outfile, "(%d %d) ", node[i] , node[j]);
}






int main(int argc, char** argv)
{
    FILE* infile =fopen (argv[1],"r");
    FILE* outfile =fopen (argv[2],"w");
    read(infile);
    print(outfile);





    fclose(infile);
    fclose(outfile);
}
