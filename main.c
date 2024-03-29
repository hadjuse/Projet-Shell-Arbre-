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
    FILE *fichier_sortie_temp_h = NULL;
    FILE *fichier_sortie_temp_pt3 = NULL;
    fichier_a_trier = fopen(argv[1], "r");
    fichier_sortie_temp = fopen("donnee_trie_temp.csv", "w");
    fichier_sortie_temp_h = fopen("donnee_trie_temp_h.csv", "w");
    fichier_sortie_temp_pt3 = fopen("donnee_trie_temp_pt3.csv", "a");
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
        fgets(ligne, MAX_LENGTH, fichier_a_trier);
        // trie par ordre chronologique
        fscanf(fichier_a_trier, "%f %s", &colonne3, colonne4);
        pArbre avl_7 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "3");
        pArbre pAvl_7 = avl_7;
        nb_ligne++;
        
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%s %f", colonne4, &colonne3);
            pAvl_7 = insertionAVL(pAvl_7, 1, &pAvl_7->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "3");           
        }
        parcoursInfixe_croissant_temp(pAvl_7, &c, nb_ligne, "3", fichier_sortie_temp_pt3);
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
        fgets(ligne, MAX_LENGTH, fichier_a_trier);
        // trie par ordre chronologique
        fscanf(fichier_a_trier, "%f %s", &colonne3, colonne4);
        pArbre avl_7 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "3");
        pArbre pAvl_7 = avl_7;
        nb_ligne++;
        
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%s %f", colonne4, &colonne3);
            pAvl_7 = insertionAVL(pAvl_7, 1, &pAvl_7->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "3");
                        
        }
        parcoursInfixe_croissant_temp(pAvl_7, &c, nb_ligne, "3", fichier_sortie_temp_pt3);
    }
    else if (strcmp(argv[2], "avl") == 0 && strcmp(argv[5], "h") == 0) // humidite
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre avl_10 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "1");
        pArbre pAvl_10 = avl_10;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f", &colonne1, colonne2, &colonne3);
            pAvl_10 = insertionAVL(pAvl_10, colonne1, &pAvl_10->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "1");
        }
        parcoursInfixe_croissant_temp(pAvl_10, &c, nb_ligne, argv[5], fichier_sortie_temp_h);
        fclose(fichier_sortie_temp_h);
        // trie par humidite
        c = 0;
        FILE *f = fopen("donnee_trie_temp_h.csv", "r");
        fgets(ligne, sizeof(ligne), f);
        fscanf(f, "%d %s %f", &colonne1, colonne2, &colonne3);
        pArbre avl_8 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[5]);
        pArbre pAvl_8 = avl_8;
        while (fgets(ligne, sizeof(ligne), fichier_sortie_temp_h) != NULL)
        {
            nb_ligne++;
            fscanf(f, "%d %s %f", &colonne1, colonne2, &colonne3);
            pAvl_8 = insertionAVL(pAvl_8, colonne3, &pAvl_8->hauteur, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[5]);
            // printf("Je suis dans l'arbre%f\n",pAvl_8->cols3);
        }
        parcoursInfixe_decroissant(pAvl_8, &c, nb_ligne, argv[5], fichier_sortie);
        fclose(f);
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
    }

    //---------------------------------------------------------------------------------------------------------------------
    // cas où le tri est un abr
    if (strcmp(argv[2], "abr") == 0 && strcmp(argv[3], "1") == 0) // cas -t1 abr
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre abr_1 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        pArbre pabr_1 = abr_1;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pabr_1 = insertionABR(pabr_1, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        }
        parcoursInfixe_croissant(pabr_1, &c, nb_ligne, argv[3], fichier_sortie);
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[3], "2") == 0) //
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre abr_2 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        pArbre pabr_2 = abr_2;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pabr_2 = insertionABR(pabr_2, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[3]);
        }
        parcoursInfixe_croissant(pabr_2, &c, nb_ligne, argv[3], fichier_sortie);
    }

    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[3], "3") == 0) // option -t3
    {
        int c = 0;
        fgets(ligne, MAX_LENGTH, fichier_a_trier);
        // trie par ordre chronologique
        fscanf(fichier_a_trier, "%f %s", &colonne3, colonne4);
        pArbre avl_7 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "3");
        pArbre pAvl_7 = avl_7;
        nb_ligne++;
        
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%s %f", colonne4, &colonne3);
            pAvl_7 = insertionABR(pAvl_7, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "3");
                        
        }
        parcoursInfixe_croissant_temp(pAvl_7, &c, nb_ligne, "3", fichier_sortie_temp_pt3);
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[4], "1") == 0) // option p1
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
        pArbre abr_1 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        pArbre pabr_1 = abr_1;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pabr_1 = insertionABR(pabr_1, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        }
        parcoursInfixe_croissant(pabr_1, &c, nb_ligne, argv[4], fichier_sortie);
    }

    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[4], "2") == 0) // p2
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
        pArbre abr_2 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        pArbre pabr_2 = abr_2;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s %f", &colonne1, colonne2, &colonne3, colonne4, &colonne5);
            pabr_2 = insertionABR(pabr_2, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[4]);
        }
        parcoursInfixe_croissant(pabr_2, &c, nb_ligne, argv[4], fichier_sortie);
    }

    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[4], "3") == 0) // p3
    {
        int c = 0;
        fgets(ligne, MAX_LENGTH, fichier_a_trier);
        // trie par ordre chronologique
        fscanf(fichier_a_trier, "%f %s", &colonne3, colonne4);
        pArbre avl_7 = creerArbre_t3(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "3");
        pArbre pAvl_7 = avl_7;
        nb_ligne++;
        
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%s %f", colonne4, &colonne3);
            pAvl_7 = insertionABR(pAvl_7, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "3");
                        
        }
        parcoursInfixe_croissant_temp(pAvl_7, &c, nb_ligne, "3", fichier_sortie_temp_pt3);
    }
    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[5], "h") == 0) // humidite
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre abr_10 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "1");
        pArbre pbr_10 = abr_10;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f", &colonne1, colonne2, &colonne3);
            pbr_10 = insertionABR(pbr_10, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "1");
        }
        parcoursInfixe_croissant_temp(pbr_10, &c, nb_ligne, argv[5], fichier_sortie_temp_h);
        fclose(fichier_sortie_temp_h);
        // trie par humidite
        c = 0;
        FILE *f = fopen("donnee_trie_temp_h.csv", "r");
        fgets(ligne, sizeof(ligne), f);
        fscanf(f, "%d %s %f", &colonne1, colonne2, &colonne3);
        pArbre abr_8 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "h");
        pArbre pabr_8 = abr_8;
        while (fgets(ligne, sizeof(ligne), fichier_sortie_temp_h) != NULL)
        {
            nb_ligne++;
            fscanf(f, "%d %s %f", &colonne1, colonne2, &colonne3);
            pabr_8 = insertionABR(pbr_10, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, "h");
        }
        parcoursInfixe_decroissant(pabr_8, &c, nb_ligne, argv[5], fichier_sortie);
        fclose(f);
    }

    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[6], "v") == 0) // vent
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %s %f %f", &colonne1, colonne2, colonne4, &colonne5, &colonne6);
        pArbre abr_4 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[6]);
        pArbre pabr_4 = abr_4;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %s %f %f", &colonne1, colonne2, colonne4, &colonne5, &colonne6);
            pabr_4 = insertionABR(pabr_4, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[6]);
        }
        parcoursInfixe_croissant(pabr_4, &c, nb_ligne, argv[6], fichier_sortie);
    }

    else if (strcmp(argv[2], "abr") == 0 && strcmp(argv[7], "a") == 0) // altitude
    {
        int c = 0;
        fgets(ligne, sizeof(ligne), fichier_a_trier);
        fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
        pArbre abr_4 = creerArbre(colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[7]);
        pArbre pabr_4 = abr_4;
        while (fgets(ligne, sizeof(ligne), fichier_a_trier) != NULL)
        {
            nb_ligne++;
            fscanf(fichier_a_trier, "%d %s %f %s", &colonne1, colonne2, &colonne3, colonne4);
            pabr_4 = insertionABR(pabr_4, colonne1, colonne1, colonne2, colonne3, colonne4, colonne5, colonne6, colonne3, argv[7]);
        }
        parcoursInfixe_decroissant(pabr_4, &c, nb_ligne, argv[7], fichier_sortie);
    }
    //---------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------------------------------
    fclose(fichier_a_trier);
    // fclose(fichier_sortie_temp);
    fclose(fichier_sortie);
    return 0;
}