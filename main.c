#include "arbre_binaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <regex.h>
#include <string.h>
int main(int argc, char **argv)
{
    
    //Etape d'ouverture et de lecture du fichier mis en argument
    if (argc != 3)
    {
        fprintf(stderr, "Format : programme <nom du fichier> <mode de tri>");
        exit(EXIT_FAILURE);
    }
    FILE *fichier_a_trier = NULL;
    fichier_a_trier = fopen(argv[1], "r");
    if (fichier_a_trier == NULL)
    {
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur = %d \n", errno);
        printf("Message d'erreur = %s \n", strerror(errno));
        exit(1);
    }
    char ligne[1024];
    
    const char delim[2] = ";";
    //Cas où le mode tri du script est un avl
    if (strcmp(argv[2], "avl") == 0){
        char *token;
        int c=0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        int premiere_valeur = atoi(ligne); 
        pArbre avl = creerArbre(premiere_valeur);
        pArbre pAvl= avl;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier))
        {
            token = strtok(ligne, delim);
            token = strtok(NULL, delim);
            int val = atoi(token);
            //printf("%d \n", val);
            pAvl = insertionAVL(pAvl,val,&pAvl->hauteur);
        }
        parcoursInfixe(avl,&c);
        printf("\nNombre de noeuds: %d", c);
    }
    fclose(fichier_a_trier);
    
    return 0;
}