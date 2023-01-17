#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "arbre_binaire.h"

#define MAX_LENGTH 1024
// Dans ce fichier C sont répertoriés tout les cas possible pour les options et arguments afin de gérer le tri
// Les codes sont quasi identiques les différences dépondrons du cas à traiter et du mode de tri utiliser
/*En fonction de chaque cas et des différents arguments et options à traiter les étape sont toujours les mêmes:

    Pour les AVL et LES ABR on crée un premier noeud, avec la fonction creerArbre, grâce à la première ligne du fichier filtre.
    Puis pour les autres ligne on fait une insertion ABR/AVL. et après on fonction de l'odre croissant ou décroissant, on appelle
    soit la fonction parcoursINfixeCroissant ou décroissant pour mettre les données triés dans les fichiers triées.
*/
int main(int argc, char **argv)
{
    int colonne1;
    char colonne2[MAX_LENGTH]; // coordonnée
    float colonne3;            // temperature / pression par station
    char colonne4[MAX_LENGTH]; // date
    float colonne5;            // temp_min
    float colonne6;            // temp_max
    int nb_ligne = 0;
    //  Etape d'ouverture et de lecture du fichier mis en argument
    if (argc != 9)
    {
        fprintf(stderr, "Format : programme <nom du fichier> <mode de tri>");
        exit(EXIT_FAILURE);
    }
    FILE *fichier_a_trier = NULL;
    FILE *fichier_sortie = NULL;
    FILE *fichier_sortie_temp = NULL; // EXCLUSIVEMENT pour l'option -t3 où il va falloir trié 2 fois
    fichier_a_trier = fopen(argv[1], "r");
    fichier_sortie_temp = fopen("donnee_trie_temp.csv", "w");
    fichier_sortie = fopen(argv[8], "w");
    if (fichier_a_trier == NULL)
    {
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur = %d \n", errno);
        printf("Message d'erreur = %s \n", strerror(errno));
        exit(1);
    }
    char ligne[MAX_LENGTH];
    // Cas où le mode tri du script est un avl
    if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "1") == 0) // cas où l'option/argument est -t1
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s %f %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5, &colonne6);
        pArbre avl = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        pArbre pAvl = avl;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5, &colonne6);
            pAvl = insertionAVL(pAvl, colonne1, &pAvl->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        }
        parcoursInfixe_t1(pAvl, &c, nb_ligne, argv[3], fichier_sortie);
    }

    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "2") == 0) // cas option -t2
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
        pArbre avl_2 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        pArbre pAvl_2 = avl_2;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pAvl_2 = insertionAVL(pAvl_2, colonne1, &pAvl_2->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        }
        parcoursInfixe_t1(pAvl_2, &c, nb_ligne, argv[3], fichier_sortie);
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "3") == 0) // option -t3
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        //trie par ordre chronologique
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl_3 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "2");
        
        pArbre pAvl_3 =avl_3;
        
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            //printf("%f\n", colonne3);
            pAvl_3 = insertionAVL_t3(pAvl_3, colonne1, &pAvl_3->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "2");
        }
        parcoursInfixe_t3(pAvl_3, &c, nb_ligne, "2", fichier_sortie_temp);
        //----------------------------
        FILE *temp2=fopen("donnee_trie_temp.csv", "r");
        //trie par identifiant
        c = 0;
        fgets(ligne, sizeof(ligne), temp2);
        fscanf(temp2, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl_4 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "1");
        pArbre pAvl_4 = avl_4;
        while (fgets(ligne, sizeof(ligne), temp2) != NULL)
        {
            nb_ligne++;
            fscanf(temp2, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pAvl_4 = insertionAVL_t3(pAvl_4, colonne1, &pAvl_4->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "1");
        }
        parcoursInfixe_t3(pAvl_4, &c, nb_ligne, "1", fichier_sortie);
        fclose(temp2);
    }
    /*
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[4], "1") == 0) // cas où l'option/argument est -p1
    {
        int c = 0;
        pArbre pAvl = NULL;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pAvl = insertionAVL(pAvl, colonne1, &pAvl->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        }
        parcoursInfixe_t1(pAvl, &c, nb_ligne, argv[3], fichier_sortie);
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
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pAbr = insertionABR(pAbr, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3, argv[3]);
        }
        parcoursInfixe_t1(pAbr, &c, nb_ligne, argv[3], fichier_sortie);
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
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[4], "1") == 0)
    {
        pArbre abr = NULL;
        int c = 0;
        pArbre pAbr = NULL;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pAbr = insertionABR(pAbr, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne3, argv[4]);
        }
        parcoursInfixe_t1(abr, &c, nb_ligne, argv[3], fichier_sortie);
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
    }*/
    //---------------------------------------------------------------------------------------------------------------------
    fclose(fichier_a_trier);
    fclose(fichier_sortie_temp);
    fclose(fichier_sortie);
    return 0;
}