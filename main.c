#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "arbre_binaire.h"

#define MAX_LENGTH 1024

int main(int argc, char **argv)
{
    int colonne1;
    char colonne2[MAX_LENGTH];
    float colonne3;
    float colonne4;
    float colonne5;
    int nb_ligne = 0;
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
    char ligne[MAX_LENGTH];
    // Cas où le mode tri du script est un avl
    if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "1") == 0)//cas où l'option/argument est -t1
    {
        printf("Nom du fichier à traiter:%s\n\n", argv[1]);
        int c = 0;
        pArbre avl = NULL;
        pArbre pAvl;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        if (ligne[0] == 'I')
        {

            fgets(ligne, sizeof(ligne), fichier_a_trier); // saut de ligne
            nb_ligne++;
            fscanf(fichier_a_trier,"%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            avl = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
            printf("%d", colonne1);
            printf("%d %s %f %f %f\n", avl->cols1, avl->cols2, avl->cols3, avl->cols4, avl->cols5);
        }

        else // cas où la première lettre de la première n'est pas égale à 1
        {
            fgets(ligne, sizeof(ligne), fichier_a_trier); // saut de ligne
            nb_ligne++;
            fscanf(fichier_a_trier,"%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            avl = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }
        
        pAvl = avl;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier,"%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            pAvl = insertionAVL(pAvl, colonne1, &avl->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }
        parcoursInfixe(pAvl, &c, nb_ligne);
        printf("\nNombre de noeuds: %d\n", c);
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[4], "1") == 0)//cas où l'option/argument est -p1
    {
        printf("Nom du fichier à traiter:%s\n\n", argv[1]);
        int c = 0;
        pArbre avl = NULL;
        pArbre pAvl;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        if (ligne[0] == 'I')
        {
            fgets(ligne, sizeof(ligne), fichier_a_trier); // saut de ligne
            nb_ligne++;
            fscanf(fichier_a_trier,"%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            avl = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
            printf("%d", colonne1);
            printf("%d %s %f %f %f\n", avl->cols1, avl->cols2, avl->cols3, avl->cols4, avl->cols5);
        }

        else // cas où la première lettre de la première n'est pas égale à 1
        {
            fgets(ligne, sizeof(ligne), fichier_a_trier); // saut de ligne
            nb_ligne++;
            fscanf(fichier_a_trier,"%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            avl = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }
        
        pAvl = avl;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier,"%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            pAvl = insertionAVL(pAvl, colonne1, &avl->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }
        parcoursInfixe(pAvl, &c, nb_ligne);
        printf("\nNombre de noeuds: %d\n", c);
    }
    fclose(fichier_a_trier);
    //---------------------------------------------------------------------------------------------------------------------
    return 0;
}