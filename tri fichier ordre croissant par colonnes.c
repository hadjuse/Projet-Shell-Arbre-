# include <stdio.h>
# include <stdlib.h>

# define COLONNES 15
# define LIGNES 1048576

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Nom du fichier: %s \n", argv[0]);
        return 1;
    }
}

FILE *file = fopen(argv[1], "r");
if(file == NULL)
{
    printf("Erreur d'ouverture du fichier!\n");
    return 1;
}

int data[COLONNES][LIGNES];
int ligne=0;
int colonne;
while(fscanf(file, "%d", &data[ligne][0])==1)
{
    for(colonne = 1; colonne<COLONNES; colonne ++)
    {
        fscanf(file, "%d", &data[ligne][colonne]);
    }
    ligne ++;
}

fclose(file);

int numlignes = ligne;
int numcolonnes = colonne;
int sortcol;
printf("Enter le numéro de la colonne à trier svp (1-%d): ", numcolonnes);
scanf("%d", &sortcol);
sortcol--;

int i,j;
for(i=0; i<numlignes; i++)
{
    for(j=i+1;j<numlignes;j++)
    {
        if(data[i][sortcol]>data[j][sortcol])
        {
            int tmp[COLONNES];
            memcpy(tmp, data[i],sizeof(tmp));
            memcpy(data[i],data[j],sizeof(tmp));
            memcpy(data[j],tmp,sizeof(tmp));
        }
    }
}

for(i=0; i<numlignes; i++)
{
    for(j=0;j<numcolonnes;j++)
    {
        printf("%d",data[i][j]);
    }
    printf("\n");
}

return 0;