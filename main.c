#include "arbre_binaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <regex.h>
#include <string.h>
#define MAX_LENGTH 1024
int main(int argc, char **argv)
{
    char colonne1[MAX_LENGTH];
    char colonne2[MAX_LENGTH];
    char colonne3[MAX_LENGTH];
    char colonne4[MAX_LENGTH];
    char colonne5[MAX_LENGTH];
    // int column;
    //  Etape d'ouverture et de lecture du fichier mis en argument
    if (argc != 8)
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
    // Cas où le mode tri du script est un avl
    if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "1") == 0)
    {
        char *token;
        int c = 0;
        pArbre avl;
        pArbre pAvl;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        if (ligne[0] == 'I')
        {
            
            fgets(ligne, sizeof(ligne), fichier_a_trier);
            token = strtok(ligne, ";"); // colonne 1
            strcpy(colonne1, token);
            token = strtok(NULL, ";"); // colonne 2
            strcpy(colonne2, token);
            token = strtok(NULL, ";"); // colonne 3
            strcpy(colonne3, token);
            token = strtok(NULL, ";"); // colonne 4
            strcpy(colonne4, token);
            token = strtok(NULL, ";"); // colonne 5
            strcpy(colonne5, token);
            avl = creerArbre(atoi(token), colonne1, colonne2, colonne3, colonne4, colonne5);
            // printf("%s %s %s %s %s\n", avl->cols1, avl->cols2, avl->cols3, avl->cols4, avl->cols5);
        }

        pAvl = avl;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            char colonne1[MAX_LENGTH];
            char colonne2[MAX_LENGTH];
            char colonne3[MAX_LENGTH];
            char colonne4[MAX_LENGTH];
            char colonne5[MAX_LENGTH];
            token = strtok(ligne, ";"); // colonne 1
            strcpy(colonne1, token);
            token = strtok(NULL, ";"); // colonne 2
            strcpy(colonne2, token);
            token = strtok(NULL, ";"); // colonne 3
            strcpy(colonne3, token);
            token = strtok(NULL, ";"); // colonne 4
            strcpy(colonne4, token);
            token = strtok(NULL, ";"); // colonne 5
            strcpy(colonne5, token);
            int val = atoi(token);
            pAvl = insertionAVL(avl, val, &avl->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5);
            // printf("%s %s %s %s %s\n", avl->cols1,avl->cols2,avl->cols3,avl->cols4,avl->cols5);
        }
        parcoursInfixe(avl, &c);
        printf("\nNombre de noeuds: %d", c);
    }

    fclose(fichier_a_trier);

    return 0;
}