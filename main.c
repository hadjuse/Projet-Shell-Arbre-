#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "arbre_binaire.h"

#define MAX_LENGTH 1024

// Dans ce fichier C sont répertoriés tout les cas possible pour les options et arguments afin de gérer le tri
// Les codes sont quasi identiques les différences dépondrons du cas à traiter et du mode de tri utiliser
int main(int argc, char **argv)
{
    int colonne1;
    char colonne2[MAX_LENGTH];
    float colonne3;
    float colonne4;
    float colonne5;
    int nb_ligne = 0;
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
    printf("tri utilisé:%s\n %s", argv[2], argv[4]);
    char ligne[MAX_LENGTH];
    // Cas où le mode tri du script est un avl
    if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "1") == 0) // cas où l'option/argument est -t1
    {
        int c = 0;
        pArbre avl = NULL;
        pArbre pAvl;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        if (ligne[0] == 'I')
        {

            fgets(ligne, sizeof(ligne), fichier_a_trier); // saut de ligne
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            avl = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
            printf("%d", colonne1);
            printf("%d %s %f %f %f\n", avl->cols1, avl->cols2, avl->cols3, avl->cols4, avl->cols5);
        }
        else // cas où la première lettre de la première n'est pas égale à 1
        {
            fgets(ligne, sizeof(ligne), fichier_a_trier); // saut de ligne
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            avl = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }

        pAvl = avl;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            pAvl = insertionAVL(pAvl, colonne1, &avl->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }
        parcoursInfixe(pAvl, &c, nb_ligne);
        printf("\nNombre de noeuds: %d\n", c);
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "2") == 0) // cas option -t2
    {
        printf("option -t2\n");
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "3") == 0) // option -t3
    {
        printf("option -t3\n");
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[4], "1") == 0) // cas où l'option/argument est -p1
    {
        int c = 0;
        pArbre pAvl=NULL;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            pAvl = insertionAVL(pAvl, colonne1, &pAvl->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }
        parcoursInfixe(pAvl, &c, nb_ligne);
        printf("\nNombre de noeuds: %d\n", c);
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[4], "2") == 0) // cas -p2
    {
        printf("option p2\n");
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[4], "3") == 0) // cas -p3
    {
        printf("option p3\n");
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[5], "ok") == 0) // humidite
    {
        printf("option humidite");
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[6], "ok") == 0) // vent
    {
        printf("vent");
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[7], "ok") == 0) // altitude
    {
        printf("altitude");
    }
    //---------------------------------------------------------------------------------------------------------------------

    // cas où le tri est un abr
    
    if (strcmp(argv[2], "abr") == 0 && strcmp(argv[3], "1") == 0) // cas -t1 abr
    {
        int c = 0;
        pArbre pAbr = NULL;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            pAbr = insertionABR(pAbr, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }
        parcoursInfixe(pAbr, &c, nb_ligne);
        printf("\nNombre de noeuds: %d\n", c);
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[3], "2") == 0)
    {
        printf("abr t2");
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[3], "3") == 0)
    {
        printf("abr t3");
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[4], "1")==0)
    {
        pArbre abr = NULL;
        int c = 0;
        pArbre pAbr = NULL;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %f %f", &colonne1, colonne2, &colonne3, &colonne4, &colonne5);
            pAbr = insertionABR(pAbr, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3);
        }
        parcoursInfixe(abr, &c, nb_ligne);
        printf("\nNombre de noeuds: %d\n", c);
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[4], "2") == 0)
    {
        printf("abr p2");
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[4], "3") == 0)
    {
        printf("abr p3");
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[5], "ok") == 0) // humidite
    {
        printf("option humidite");
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[6], "ok") == 0) // vent
    {
        printf("vent abr");
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[7], "ok") == 0) // altitude
    {
        printf("altitude abr");
    }
    //---------------------------------------------------------------------------------------------------------------------
    // cas où le tri est un tab
    if (strcmp(argv[2], "tab") == 0 && strcmp(argv[3], "1") == 0)
    {
        printf("tab t1");
    }
    else if (strcmp(argv[2], "tab") == 0 && strcmp(argv[3], "2") == 0)
    {
        printf("t2 tab");
    }
    else if (strcmp(argv[2], "tab") == 0 && strcmp(argv[3], "3") == 0)
    {
        printf("t2 tab");
    }
    else if (strcmp(argv[2], "tab") == 0 && strcmp(argv[4], "1") == 0)
    {
        printf("tab p1");
    }
    else if (strcmp(argv[2], "tab") == 0 && strcmp(argv[4], "2") == 0)
    {
        printf("tab p2");
    }
    else if (strcmp(argv[2], "tab") == 0 && strcmp(argv[4], "3") == 0)
    {
        printf("tab p3");
    }
    else if (strcmp(argv[2], "tab") == 0 && strcmp(argv[5], "ok") == 0) // humidite
    {
        printf("option humidite tab");
    }
    else if (strcmp(argv[2], "tab") == 0 && strcmp(argv[6], "ok") == 0) // vent
    {
        printf("vent tab");
    }
    else if (strcmp(argv[2], "tab") == 0 && strcmp(argv[7], "ok") == 0) // altitude
    {
        printf("vent tab");
    }
    //---------------------------------------------------------------------------------------------------------------------
    fclose(fichier_a_trier);
    return 0;
}