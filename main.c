#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "arbre_binaire.h"

#define MAX_LENGTH 1024
// Dans ce fichier C sont répertoriés tout les cas possible pour les options et arguments afin de gérer le tri et les traitements de valeurs
// Les codes sont quasi identiques les différences dépondrons du cas à traiter et du mode de tri utiliser
/*En fonction de chaque cas et des différents arguments et options à traiter les étape sont toujours les mêmes:

    Pour les AVL et LES ABR on créee un premier noeud, avec la fonction creerArbre, grâce à la première ligne du fichier filtré mis en argument.
    Puis pour les autres ligne on fait une insertion ABR/AVL. et après on fonction de l'odre croissant ou décroissant, on appelle
    soit la fonction parcoursINfixeCroissant/Decroissant pour mettre les données triés dans les fichiers triées.
*/
int main(int argc, char **argv)
{
    int colonne1;              // ID station
    char colonne2[MAX_LENGTH]; // coordonnée
    float colonne3;            // temperature / pression par station
    char colonne4[MAX_LENGTH]; // date
    float colonne5;            // temp_min / direction moyenne et autre et autre variable possible
    float colonne6;            // temp_max / vitesse moyenne et autre variable possible
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
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        pArbre pAvl = avl;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pAvl = insertionAVL(pAvl, colonne1, &pAvl->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        }
        parcoursInfixe_croissant(pAvl, &c, nb_ligne, argv[3], fichier_sortie);
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
        parcoursInfixe_croissant(pAvl_2, &c, nb_ligne, argv[3], fichier_sortie);
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[3], "3") == 0) // option -t3
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        // trie par ordre chronologique
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl_3 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "2");

        pArbre pAvl_3 = avl_3;

        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pAvl_3 = insertionAVL_t3(pAvl_3, colonne1, &pAvl_3->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "2");
        }
        parcoursInfixe_t3(pAvl_3, &c, nb_ligne, "2", fichier_sortie_temp);
        //----------------------------
        FILE *temp2 = fopen("donnee_trie_temp.csv", "r");
        // trie par identifiant
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

    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[4], "1") == 0) // cas où l'option/argument est -p1
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s %f %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5, &colonne6);
        pArbre avl_5 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        pArbre pAvl_5 = avl_5;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5, &colonne6);
            pAvl_5 = insertionAVL(pAvl_5, colonne1, &pAvl_5->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        }
        parcoursInfixe_croissant(pAvl_5, &c, nb_ligne, argv[4], fichier_sortie);
        printf("nombre de noeud %d \n", c);
    }
    // Je rappelle c'est vraiment des copiés coller de l'option t1
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[4], "2") == 0) // cas -p2
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
        pArbre avl_6 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        pArbre pAvl_6 = avl_6;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pAvl_6 = insertionAVL(pAvl_6, colonne1, &pAvl_6->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        }
        parcoursInfixe_croissant(pAvl_6, &c, nb_ligne, argv[4], fichier_sortie);
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[4], "3") == 0) // cas -p3
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        // trie par ordre chronologique
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl_7 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "2");

        pArbre pAvl_7 = avl_7;

        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pAvl_7 = insertionAVL_t3(pAvl_7, colonne1, &pAvl_7->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "2");
        }
        parcoursInfixe_t3(pAvl_7, &c, nb_ligne, "2", fichier_sortie_temp);
        //----------------------------
        FILE *temp2 = fopen("donnee_trie_temp.csv", "r");
        // trie par identifiant
        c = 0;
        fgets(ligne, sizeof(ligne), temp2);
        fscanf(temp2, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl_8 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "1");
        pArbre pAvl_8 = avl_8;
        while (fgets(ligne, sizeof(ligne), temp2) != NULL)
        {
            nb_ligne++;
            fscanf(temp2, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pAvl_8 = insertionAVL_t3(pAvl_8, colonne1, &pAvl_8->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "1");
        }
        parcoursInfixe_t3(pAvl_8, &c, nb_ligne, "1", fichier_sortie);
        fclose(temp2);
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[5], "h") == 0) // humidite
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl_10 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[5]);
        pArbre pAvl_10 = avl_10;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pAvl_10 = insertionAVL(pAvl_10, colonne3, &pAvl_10->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[5]);
        }
        parcoursInfixe_decroissant(pAvl_10, &c, nb_ligne, argv[5], fichier_sortie);
        strcpy(argv[5], "non");
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[6], "v") == 0) // vent
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %s %f %f", &colonne1, colonne2, colonne4, &colonne5, &colonne6);
        pArbre avl_11 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[6]);
        pArbre pAvl_11 = avl_11;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pAvl_11 = insertionAVL(pAvl_11, colonne1, &pAvl_11->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[6]);
        }
        parcoursInfixe_croissant(pAvl_11, &c, nb_ligne, argv[6], fichier_sortie);
        strcpy(argv[6], "non"); 
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[7], "a") == 0) // altitude
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl_12 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[7]);
        pArbre pAvl_12 = avl_12;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pAvl_12 = insertionAVL(pAvl_12, colonne3, &pAvl_12->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[7]);
        }
        parcoursInfixe_decroissant(pAvl_12, &c, nb_ligne, argv[7], fichier_sortie);
        strcpy(argv[7], "non"); 
        
    }
    /*
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
        parcoursInfixe_croissant(pAbr, &c, nb_ligne, argv[3], fichier_sortie);
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
        parcoursInfixe_croissant(abr, &c, nb_ligne, argv[3], fichier_sortie);
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